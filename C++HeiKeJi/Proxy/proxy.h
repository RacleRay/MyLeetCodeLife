/*************************************************************************
    > File Name: proxy.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _PROXY_H
#define _PROXY_H

#include <memory>

struct CC {
  struct Impl;
  std::unique_ptr<Impl> impl;

  CC();
  ~CC();

  void func();
};

#endif
