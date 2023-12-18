#include <iostream>

#include "ucontext.h"
#include "unistd.h"

void foo() { printf("this is child context.\n"); }

int main() {
  char stack[1024 * 1024];

  ucontext_t child, main;

  getcontext(&child);

  child.uc_stack.ss_sp = stack;
  child.uc_stack.ss_size = sizeof(stack);
  child.uc_stack.ss_flags = 0;
  child.uc_link = &main;
  makecontext(&child, foo, 0);

  swapcontext(&main, &child);

  printf("this is main context.\n");

  return 0;
}