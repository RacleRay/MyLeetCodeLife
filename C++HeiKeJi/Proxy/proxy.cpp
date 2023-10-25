/*************************************************************************
    > File Name: proxy.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "proxy.h"

struct CC::Impl {
    int  a, b, c;
    void func() { a += 1; }
};

CC::CC() : impl(std::make_unique<Impl>()) {}
CC::~CC() = default;
void CC::func() { impl->func(); }
