#ifndef __NGINXPOOL__H__
#define __NGINXPOOL__H__

#include <cstdint>
#include <cstdlib>
#include <memory.h>


using u_char = unsigned char;
using ngx_uint_t = unsigned int;

struct ngx_pool_s;

// 清理函数（回调函数）指针
typedef void (*ngx_pool_cleanup_pt)(void *data);
struct ngx_pool_cleanup_s {
  ngx_pool_cleanup_pt handler; // 定义了一个函数指针，保存清理操作的回调函数
  void *data;                  // 回调函数的参数
  ngx_pool_cleanup_s *next; // 所有的cleanup清理操作，都被串在一条链表上
};

/*
大块内存的头部信息
*/
struct ngx_pool_large_s {
  ngx_pool_large_s *next; // 所有的大块内存分配也是被串在一条链表上
  void *alloc;            // 保存分配出去的大块内存的起始地址
};

/*
分配小块内存的内存池的头部信息
*/
struct ngx_pool_data_t {
  u_char *last;      // 小块内存池可用内存的起始地址
  u_char *end;       // 小块内存池可用内存的末尾地址
  ngx_pool_s *next;  // 所有小块内存池都被串在一条链表上
  ngx_uint_t failed; // 记录了当前小块内存池分配内存失败的次数
};

/*
nginx内存池的头部信息
*/
struct ngx_pool_s {
  ngx_pool_data_t d;   // 存储的是当前小块内存池的使用情况
  size_t max;          // 存储的是小块内存和大块内存的临界值
  ngx_pool_s *current; // 指向第一个可用小块内存池的地址
  ngx_pool_large_s *large;     // 指向大块内存（链表）的入口地址
  ngx_pool_cleanup_s *cleanup; // 指向所有清理操作回调函数的入口
};

// 把数值d调整到临近的a的倍数
#define ngx_align(d, a) (((d) + (a - 1)) & ~(a - 1))
// 小块内存分配的字节对齐时的单位
#define NGX_ALIGNMENT sizeof(unsigned long) /* platform word */
// 把指针p调整到a的临近的倍数
#define ngx_align_ptr(p, a)                                                    \
  (u_char *)(((uintptr_t)(p) + ((uintptr_t)a - 1)) & ~((uintptr_t)a - 1))
// buf缓冲区清0
#define ngx_memzero(buf, n) (void)memset(buf, 0, n)

// 默认一个物理页面的大小4K
const int ngx_pagesize = 4096;
// nginx小块内存可分配的最大空间
const int NGX_MAX_ALLOC_FROM_POOL = ngx_pagesize - 1;
// 定义常量，表示一个默认的nginx内存池开辟的大小
const int NGX_DEFAULT_POOL_SIZE = 16 * 1024; // 16K
// 内存池大小按照16字节进行对齐
const int NGX_POOL_ALIGNMENT = 16;
// nginx小块内存池最小的size调整成NGX_POOL_ALIGNMENT的临近的倍数
const int NGX_MIN_POOL_SIZE = ngx_align(
    (sizeof(ngx_pool_s) + 2 * sizeof(ngx_pool_large_s)), NGX_POOL_ALIGNMENT);

//=================================================================================
//
class NgxMemoryPool {
public:
  // 创建指定size大小的内存池，但是小块内存池不超过1个页面的大小
  void *ngx_create_pool(size_t size) {
    ngx_pool_s *p;

    p = (ngx_pool_s *)malloc(size);
    if (p == nullptr) {
      return nullptr;
    }

    p->d.last = (u_char *)p + sizeof(ngx_pool_s);
    p->d.end = (u_char *)p + size;
    p->d.next = nullptr;
    p->d.failed = 0;

    size = size - sizeof(ngx_pool_s);
    p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    p->current = p;
    p->large = nullptr;
    p->cleanup = nullptr;

    pool = p;
    return p;
  }

  // 考虑内存字节对齐，从内存池申请size大小的内存
  void *ngx_palloc(size_t size) {
    if (size <= pool->max) {
      return ngx_palloc_small(size, 1);
    }

    return ngx_palloc_large(size);
  }

  // 不考虑内存字节对齐
  void *ngx_pnalloc(size_t size) {
    if (size <= pool->max) {
      return ngx_palloc_small(size, 0);
    }

    return ngx_palloc_large(size);
  }

  // 调用ngx_palloc且初始化为0
  void *ngx_pcalloc(size_t size) {
    void *p;

    p = ngx_palloc(size);
    if (p) {
      ngx_memzero(p, size);
    }

    return p;
  }
  // 释放大块内存
  void ngx_pfree(void *p) {
    ngx_pool_large_s *l;

    for (l = pool->large; l; l = l->next) {
      if (p == l->alloc) {
        free(l->alloc);
        l->alloc = nullptr;

        return;
      }
    }
  }

  // 内存重置
  void ngx_reset_pool() {
    ngx_pool_s *p;
    ngx_pool_large_s *l;

    for (l = pool->large; l; l = l->next) {
      if (l->alloc) {
        free(l->alloc);
      }
    }

    // 处理第一个小块内存池
    p = pool;
    p->d.last = (u_char *)p + sizeof(ngx_pool_s);
    p->d.failed = 0;

    // 第二块内存池开始循环到最后一个内存池
    for (p = p->d.next; p; p = p->d.next) {
      p->d.last = (u_char *)p + sizeof(ngx_pool_data_t);
      p->d.failed = 0;
    }

    pool->current = pool;
    pool->large = nullptr;
  }

  // 内存池的销毁
  void ngx_destroy_pool() {
    ngx_pool_s *p, *n;
    ngx_pool_large_s *l;
    ngx_pool_cleanup_s *c;

    for (c = pool->cleanup; c; c = c->next) {
      if (c->handler) {
        c->handler(c->data);
      }
    }

    for (l = pool->large; l; l = l->next) {
      if (l->alloc) {
        free(l->alloc);
      }
    }

    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
      free(p);

      if (n == nullptr) {
        break;
      }
    }
  }

  // 添加清理回调函数
  ngx_pool_cleanup_s *ngx_pool_cleanup_add(size_t size) {
    ngx_pool_cleanup_s *c;

    c = (ngx_pool_cleanup_s *)ngx_palloc(sizeof(ngx_pool_cleanup_s));
    if (c == nullptr) {
      return nullptr;
    }

    if (size) {
      c->data = ngx_palloc(size);
      if (c->data == nullptr) {
        return nullptr;
      }

    } else {
      c->data = nullptr;
    }

    c->handler = nullptr;
    c->next = pool->cleanup;

    pool->cleanup = c;

    return c;
  }

private:
  ngx_pool_s *pool; // 指向nginx内存池的入口指针
  
  // 小块内存分配
  void *ngx_palloc_small(size_t size, ngx_uint_t align) {
    u_char *m;
    ngx_pool_s *p;

    p = pool->current;

    do {
      m = p->d.last;

      if (align) {
        m = ngx_align_ptr(m, NGX_ALIGNMENT);
      }

      if ((size_t)(p->d.end - m) >= size) {
        p->d.last = m + size;

        return m;
      }

      p = p->d.next;

    } while (p);

    return ngx_palloc_block(size);
  }

  // 大块内存分配
  void *ngx_palloc_large(size_t size) {
    void *p;
    ngx_uint_t n;
    ngx_pool_large_s *large;

    p = (void *)malloc(size);
    if (p == nullptr) {
      return nullptr;
    }

    n = 0;

    for (large = pool->large; large; large = large->next) {
      if (large->alloc == nullptr) {
        large->alloc = p;
        return p;
      }

      if (n++ > 3) {
        break;
      }
    }

    large = (ngx_pool_large_s *)ngx_palloc_small(sizeof(ngx_pool_large_s), 1);
    if (large == nullptr) {
      free(p);
      return nullptr;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
  }

  // 分配新的小块内存池
  void *ngx_palloc_block(size_t size) {
    u_char *m;
    size_t psize;
    ngx_pool_s *p, *newpool;

    psize = (size_t)(pool->d.end - (u_char *)pool);

    m = (u_char *)malloc(psize);
    if (m == nullptr) {
      return nullptr;
    }

    newpool = (ngx_pool_s *)m;

    newpool->d.end = m + psize;
    newpool->d.next = nullptr;
    newpool->d.failed = 0;

    m += sizeof(ngx_pool_data_t);
    m = ngx_align_ptr(m, NGX_ALIGNMENT);
    newpool->d.last = m + size;

    for (p = pool->current; p->d.next; p = p->d.next) {
      if (p->d.failed++ > 4) {
        pool->current = p->d.next;
      }
    }

    p->d.next = newpool;

    return m;
  }
};

#endif //!__NGINXPOOL__H__