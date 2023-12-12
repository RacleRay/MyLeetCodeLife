#include <mutex>
#include <optional>
#include <queue>
#include <shared_mutex>
#include <string.h>
#include <unistd.h>

#include "spinlock.h"

#include "benchmark/benchmark.h"


/**
 * @brief 
 先下载编译 Google Benchmark
 $ export GBEN_LIB=/home/xxx/benchmark/build/src/
 $ clang++ -g -O3 -mavx2 -Wall -pedantic -I$GBEN_INC -lpthread -lrt -lm intrusive_shared_pointer.cpp $GBEN_LIB/libbenchmark.a -o benchmark

 定义的类和测试函数写在一起，主要是为了让测试的上下文环境更稳定一些，防止编译器对多文件编译链接时优化行为的不同带来的不确定影响。
 */


template <typename T> void reset(T &q) { T().swap(q); }

// long sequence
struct LS {
  long x[1024];
  LS(char i) {
    for (size_t k = 0; k < 1024; ++k)
      x[k] = i;
  }
};

template <typename T> class st_queue {
  std::queue<T> s_;

public:
  void push(const T &v) { s_.push(v); }
  std::optional<T> pop() {
    if (s_.empty()) {
      return std::optional<T>(std::nullopt);
    } else {
      std::optional<T> res(std::move(s_.front()));
      s_.pop();
      return res;
    }
  }
  std::optional<T> front() const {
    if (s_.empty()) {
      return std::optional<T>(std::nullopt);
    } else {
      std::optional<T> res(s_.front());
      return res;
    }
  }
  void reset() { ::reset(s_); }
};

template <typename T> class mt_queue {
  std::queue<T> s_;
  mutable spinlock l_;

public:
  void push(const T &v) {
    std::lock_guard g(l_);
    s_.push(v);
  }
  std::optional<T> pop() {
    std::lock_guard g(l_);
    if (s_.empty()) {
      return std::optional<T>(std::nullopt);
    } else {
      std::optional<T> res(std::move(s_.front()));
      s_.pop();
      return res;
    }
  }
  std::optional<T> front() const {
    std::lock_guard g(l_);
    if (s_.empty()) {
      return std::optional<T>(std::nullopt);
    } else {
      std::optional<T> res(s_.front());
      return res;
    }
  }
  void reset() { ::reset(s_); }
};

template <typename T> class mt_queue1 {
  std::queue<T> s_;
  mutable std::mutex l_;

public:
  void push(const T &v) {
    std::lock_guard g(l_);
    s_.push(v);
  }
  std::optional<T> pop() {
    std::lock_guard g(l_);
    if (s_.empty()) {
      return std::optional<T>(std::nullopt);
    } else {
      std::optional<T> res(std::move(s_.front()));
      s_.pop();
      return res;
    }
  }
  std::optional<T> front() const {
    std::lock_guard g(l_);
    if (s_.empty()) {
      return std::optional<T>(std::nullopt);
    } else {
      std::optional<T> res(s_.front());
      return res;
    }
  }
  void reset() { ::reset(s_); }
};

void BM_queue0(benchmark::State &state) {
  st_queue<int> q0;
  const size_t N = state.range(0);
  for (auto _ : state) {
    for (size_t i = 0; i < N; ++i)
      q0.push(i);
    for (size_t i = 0; i < N; ++i)
      benchmark::DoNotOptimize(q0.pop());
  }
  state.SetItemsProcessed(state.iterations() * N);
}

mt_queue<int> q;
mt_queue<LS> lq;

void BM_queue(benchmark::State &state) {
  if (state.thread_index() == 0)
    q.reset();
  const size_t N = state.range(0);
  for (auto _ : state) {
    for (size_t i = 0; i < N; ++i)
      q.push(i);
    for (size_t i = 0; i < N; ++i)
      benchmark::DoNotOptimize(q.pop());
  }
  state.SetItemsProcessed(state.iterations() * N);
}

mt_queue1<int> q1;

void BM_queue1(benchmark::State &state) {
  if (state.thread_index() == 0)
    q1.reset();
  const size_t N = state.range(0);
  for (auto _ : state) {
    for (size_t i = 0; i < N; ++i)
      q1.push(i);
    for (size_t i = 0; i < N; ++i)
      benchmark::DoNotOptimize(q1.pop());
  }
  state.SetItemsProcessed(state.iterations() * N);
}

void BM_queue_prod_cons(benchmark::State &state) {
  if ((state.threads() & 1) == 1)
    state.SkipWithError("Need even number of threads()!");
  if (state.thread_index() == 0)
    q.reset();
  const bool producer = state.thread_index() & 1;
  const size_t N = state.range(0);
  for (auto _ : state) {
    if (producer) {
      for (size_t i = 0; i < N; ++i)
        q.push(i);
    } else {
      for (size_t i = 0; i < N; ++i)
        benchmark::DoNotOptimize(q.pop());
    }
  }
  state.SetItemsProcessed(state.iterations() * N);
}

void BM_lqueue_prod_cons(benchmark::State &state) {
  if ((state.threads() & 1) == 1)
    state.SkipWithError("Need even number of threads()!");
  if (state.thread_index() == 0)
    lq.reset();
  const bool producer = state.thread_index() & 1;
  const size_t N = state.range(0);
  for (auto _ : state) {
    if (producer) {
      for (size_t i = 0; i < N; ++i)
        lq.push(i);
    } else {
      for (size_t i = 0; i < N; ++i)
        benchmark::DoNotOptimize(lq.pop());
    }
  }
  state.SetItemsProcessed(state.iterations() * N);
}

static const long numcpu = sysconf(_SC_NPROCESSORS_CONF);

#define ARGS ->Arg(1)->ThreadRange(1, numcpu)->UseRealTime()

// BENCHMARK(BM_queue0) ARGS;
// BENCHMARK(BM_queue) ARGS;
// BENCHMARK(BM_queue1) ARGS;
BENCHMARK(BM_queue_prod_cons) ARGS;
BENCHMARK(BM_lqueue_prod_cons) ARGS;

BENCHMARK_MAIN();