#include "../header.h"


struct Node {
    string s;
    int idx;
    Node* pre, *next;

    explicit Node(string s, int idx = 0)
        : s(s), idx(idx), pre(nullptr), next(nullptr) {}; 
};


struct elem {
    Node *forword{nullptr};
    Node *backword{nullptr};
};


class AllOne {
    vector<elem> buckets;
    unordered_map<string, Node*> map;
    Node *head, *tail;

public:
    AllOne() : buckets(50005) {
        head = new Node("");
        tail = new Node("");
        buckets[0] = elem{head, nullptr};
        buckets.back() = elem{nullptr, tail};
        head->next = tail;
        tail->pre = head;
    }
    
    void inc(string key) {
        if (map.count(key)) {
            // 已存在
            Node *cur = map[key];
            erase(cur);
            cur->idx++;

            insert(cur, buckets[cur->idx - 1].forword);

            // 在forward链路上
            // if (buckets[cur->idx - 1].forword) {
            //     insert(cur, buckets[cur->idx - 1].forword);
            // } else {
            // insert(cur, cur->pre);
            // }

        } else {
            // new node
            Node *cur = new Node(key);
            cur->idx++;
            map[key] = cur;
            insert(cur, head);
        }
    }
    
    void dec(string key) {
        Node* cur = map[key];
        erase(cur);
        if (cur->idx == 1) {
            map.extract(key);
        } else {
            cur->idx--;
            insert(cur, buckets[cur->idx].forword->pre);
        }
    }
    
    string getMaxKey() {
        return tail->pre->s;
    }
    
    string getMinKey() {
        return head->next->s;
    }

private:
    void insert(Node *cur, Node *prev) {
        cur->next = prev->next;
        cur->pre = prev;

        cur->next->pre = cur;
        cur->pre->next = cur;

        auto& [forward, backward] = buckets[cur->idx];
        if (!forward && !backward) {
            forward = backward = cur;
        } else {
            // 这是不可能的，或者是错误的值插入
            return;
        }     
    }

    void erase(Node *cur) {
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;

        auto& [forward, backward] = buckets[cur->idx];
        if (forward == cur && backward == cur) {
            forward = backward = nullptr;
        } else {
            // 这是不可能的，或者是错误的值插入
            return;
        }
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */