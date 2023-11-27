#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class threadsafe_hashtable {
private:
  // 桶类型
  class bucket_type {
    friend class threadsafe_lookup_table;

  private:
    typedef std::pair<Key, Value> bucket_value;
    // 由链表存储元素构
    typedef std::list<bucket_value> bucket_data;
    // 链表的迭代器
    typedef typename bucket_data::iterator bucket_iterator;

    // 链表数据
    bucket_data data;
    // 共享锁
    mutable std::shared_mutex mutex;

    // 查找操作，在list中找到匹配的key值，然后返回迭代器
    bucket_iterator find_entry_for(const Key &key) {
      return std::find_if(
          data.begin(), data.end(),
          [&](bucket_value const &item) { return item.first == key; });
    }

  public:
    // 查找key值，找到返回对应的value，未找到则返回默认值
    Value value_for(Key const &key, Value const &default_value) {
      // 读共享锁
      std::shared_lock<std::shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      return (found_entry == data.end()) ? default_value : found_entry->second;
    }

    // 添加key和value，找到则更新，没找到则添加
    void add_or_update_mapping(Key const &key, Value const &value) {
      // 写独占锁
      std::unique_lock<std::shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      if (found_entry == data.end()) {
        data.push_back(bucket_value(key, value));
      } else {
        found_entry->second = value;
      }
    }

    // 删除对应的key
    void remove_mapping(Key const &key) {
      // 写独占锁
      std::unique_lock<std::shared_mutex> lock(mutex);
      bucket_iterator const found_entry = find_entry_for(key);
      if (found_entry != data.end()) {
        data.erase(found_entry);
      }
    }
  };

  std::vector<std::unique_ptr<bucket_type>> buckets;

  Hash hashfunc;

  bucket_type &get_bucket(Key const &key) const {
    std::size_t const bucket_index = hashfunc(key) % buckets.size();
    return *buckets[bucket_index];
  }

public:
  threadsafe_hashtable(size_t num_buckets = 19, Hash const &hashfunc = Hash())
      : buckets(num_buckets), hashfunc(hashfunc) {
    for (size_t i = 0; i < num_buckets; ++i) {
      buckets[i].reset(new bucket_type);
    }
  }

  threadsafe_hashtable(threadsafe_hashtable const &other) = delete;

  threadsafe_hashtable &
  operator=(threadsafe_hashtable const &other) = delete;

  Value value_for(Key const &key, Value const &default_value = Value()) {
    return get_bucket(key).value_for(key, default_value);
  }

  void add_or_update_mapping(Key const &key, Value const &value) {
    get_bucket(key).add_or_update_mapping(key, value);
  }

  void remove_mapping(Key const &key) { get_bucket(key).remove_mapping(key); }

  std::map<Key, Value> get_map() {
    std::vector<std::unique_lock<std::shared_mutex>> locks;
    for (size_t i = 0; i < buckets.size(); ++i) {
        locks.push_back(std::unique_lock<std::shared_mutex>(buckets[i]->mutex));
    }

    std::map<Key, Value> result;
    for (size_t i = 0; i < buckets.size(); ++i) {
        typename bucket_type::bucket_iterator it = buckets[i]->data.begin();
        for (; it != buckets[i]->data.end(); ++it) {
            result.insert(*it);
        }
    }

    return result;
  }
};