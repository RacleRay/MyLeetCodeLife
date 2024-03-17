#include <cassert>
#include <iostream>
#include <time.h>
#include <vector>


#include "MemoryPool.h"
#include "StackAlloc.hpp"
#include "SGIPool.hpp"
#include "NginxPool.hpp"


#define ELEMS 1000000
#define REPS 50


//=================================================================================
// test Nginx Memory Pool
typedef struct Data Data_t;

struct Data
{
    char* ptr;
    FILE* pfile;
};

void clear_char(void* p1)
{
    char* p = (char*)p1;
    printf("free ptr memory!\n");
    free(p);
}

void clear_file(void* pf1)
{
    FILE* pf = (FILE*)pf1;
    printf("close file!\n");
    fclose(pf);
}

int test_nginx_pool()
{
    // NgxMemoryPool* pool = new NgxMemoryPool();
    NgxMemoryPool pool;

    void *pool_ptr = pool.ngx_create_pool(1024);
    if (pool_ptr == nullptr) {
        printf("ngx_create_pool failed!\n");
        return -1;
    }

    // 小块内存
    void *p1 = pool.ngx_palloc(128);
    if (p1 == nullptr) {
        printf("ngx_palloc 128 failed!\n");
        return -1;
    }

    // 大块内存
    Data_t *p2 = (Data_t*)pool.ngx_palloc(1024 * 1024);
    if (p2 == nullptr) {
        printf("ngx_palloc 1024 * 1024 failed!\n");
        return -1;
    }

    p2->ptr = (char*)malloc(512);
    strcpy(p2->ptr, "hello world");
    p2->pfile = fopen("data.txt", "w");

    // 自定义内存清理
    ngx_pool_cleanup_s* clr1 = pool.ngx_pool_cleanup_add(sizeof(char*));
    clr1->handler = clear_char;
    clr1->data = p2->ptr;

    ngx_pool_cleanup_s* clr2 = pool.ngx_pool_cleanup_add(sizeof(FILE*));
    clr2->handler = clear_file;
    clr2->data = p2->pfile;

    // 内存清理，释放大内存块，释放小块内存
    pool.ngx_destroy_pool();

    return 0;
}


int main() {
  clock_t start;

  std::cout << "Provided to compare the default allocator, MemoryPool, SGI memory pool.\n\n";

  /* Use the default allocator */
  StackAlloc< int, std::allocator<int> > stackDefault;
  start = clock();
  for (int j = 0; j < REPS; j++) {
    assert(stackDefault.empty());
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackDefault.push(i);
      stackDefault.push(i);
      stackDefault.push(i);
      stackDefault.push(i);
    }
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackDefault.pop();
      stackDefault.pop();
      stackDefault.pop();
      stackDefault.pop();
    }
  }
  std::cout << "Default Allocator Time: ";
  std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

  /* Use MemoryPool */
  StackAlloc< int, MPL::MemoryPool<int> > stackPool;
  start = clock();
  for (int j = 0; j < REPS; j++) {
    assert(stackPool.empty());
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackPool.push(i);
      stackPool.push(i);
      stackPool.push(i);
      stackPool.push(i);
    }
    // std::cout << ">>> [max_size] test :" << stackPool.get_pool_size() << "\n\n";
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackPool.pop();
      stackPool.pop();
      stackPool.pop();
      stackPool.pop();
    }
  }
  std::cout << "MemoryPool Allocator Time: ";
  std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

  // SGIallocator : 效果基本就是和 std::allocator 一样
  StackAlloc< int, SGIallocator<int> > stackSGIPool;
  start = clock();
  for (int j = 0; j < REPS; j++) {
    assert(stackSGIPool.empty());
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackSGIPool.push(i);
      stackSGIPool.push(i);
      stackSGIPool.push(i);
      stackSGIPool.push(i);
    }
    // std::cout << ">>> [max_size] test :" << stackSGIPool.get_pool_size() << "\n\n";
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackSGIPool.pop();
      stackSGIPool.pop();
      stackSGIPool.pop();
      stackSGIPool.pop();
    }
  }
  std::cout << "SGI Memory Pool Allocator Time: ";
  std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

  std::cout << "Run NGINX Memory Pool test: \n";
  int ret = test_nginx_pool();
  if (ret < 0) { std::cout << "NGINX Memory Pool test failed.\n"; }
  std::cout << "NGINX Memory Pool test passed.\n\n";

  std::cout << "========================================================\n";
  std::cout << "Here is a secret: the best way of implementing a stack"
               " is a dynamic array.\n";

  /* Compare MemoryPool to std::vector */
  std::vector<int> stackVector;
  start = clock();
  for (int j = 0; j < REPS; j++) {
    assert(stackVector.empty());
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackVector.push_back(i);
      stackVector.push_back(i);
      stackVector.push_back(i);
      stackVector.push_back(i);
    }
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackVector.pop_back();
      stackVector.pop_back();
      stackVector.pop_back();
      stackVector.pop_back();
    }
  }
  std::cout << "Vector Time: ";
  std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

  std::cout << "The vector implementation will probably be faster.\n\n";
  std::cout << "========================================================\n";
  std::cout
      << "MemoryPool still has a lot of uses though. Any type of tree"
         " and when you have multiple linked lists are some examples (they"
         " can all share the same memory pool).\n";

  return 0;
}