// void *f(int n) {
//   void *hdl = CORO_BEGIN(malloc);
//   for (int i = n;; ++i) {
//     CORO_SUSPEND(hdl);
//     print(i);
//     CORO_SUSPEND(hdl);
//     print(-i);
//   }
//   CORO_END(hdl, free);
// }

// int main() {
//   void *coro = f(1);
//   for (int i = 0; i < 4; ++i) {
//     CORO_RESUME(coro);
//   }
//   CORO_DESTROY(coro);
// }

// struct f.frame {
//   // 只有 i 跨越了协程的调用，而 n 在协程 SUSPEND 处理之前已经没用了
//   int i;
// };

// =============================================================================

// struct f.frame {
//   int suspend_index;
//   int i;
// };

// void *f(int n) {
//   void *hdl = CORO_BEGIN(malloc);
//   f.frame *frame = (f.frame *)hdl;
//   for (frame->i = n;; ++frame->i) {
//     frame->suspend_index = 0;
//   r0:
//     CORO_SUSPEND(hdl);
//     print(frame->i);
//     frame->suspend_index = 1;
//   r1:
//     CORO_SUSPEND(hdl);
//     print(-frame->i);
//   }
//   CORO_END(hdl, free);
// }

// ============================================================================

// // coroutine start function
// void *f(int n) {
//   void *hdl = CORO_BEGIN(malloc);
//   …
//   return hdl;
// }

// void* f(int *n) {
//     void* hdl = CORO_BEGIN(malloc);
//     f.frame* frame = (f.frame*)hdl;
//     frame->ResumeFn = &f.resume;
//     frame->DestroyFn = &f.destroy;
//     frame->i = n;
//     frame->suspend_index = 0;
//     return coro_hdl;
// }

// // coroutine resume function
// void f.resume(f.frame *frame) {
//   switch (frame->suspend_index) {
//     …
//   }
// }

// // coroutine destroy function
// void f.destroy(f.frame *frame) {
//   switch (frame->suspend_index) {
//     …
//   }
//   free(frame);
// }

// struct f.frame {
//     FnPtr ResumeFn;
//     FnPtr DestroyFn;
//     int suspend_index;
//     int i;
// };

// void f.resume(f.frame *frame) {
//   switch (frame->suspend_index) {
//   case 0:
//     goto r0;
//   default:
//     goto r1;
//   }
//   for (frame->i = n;; ++frame->i) {
//     frame->suspend_index = 0;
//   r0:
//     CORO_SUSPEND(hdl);
//     print(frame->i);
//     frame->suspend_index = 1;
//   r1:
//     CORO_SUSPEND(hdl);
//     print(-frame->i);
//   }
//   CORO_END(hdl, free);
// }

#define CORO_SUSPEND()                                                         \
  switch (__builtin_coro_suspend()) {                                          \
  case -1:                                                                     \
    goto coro_Suspend;                                                         \
  case 1:                                                                      \
    goto coro_Cleanup;                                                         \
  default:                                                                     \
    break;                                                                     \
  }

#define CORO_END(hdl, FreeFunc)                                                \
  coro_Cleanup : {                                                             \
    void *coro_mem = __builtin_coro_free(hdl);                                 \
    if (coro_mem)                                                              \
      FreeFunc(coro_mem);                                                      \
  }                                                                            \
  coro_Suspend:                                                                \
  __builtin_coro_end();                                                        \
  return coro_hdl;