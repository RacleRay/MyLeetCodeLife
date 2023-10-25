/*************************************************************************
    > File Name: enable_if.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <iostream>

template <class T, std::enable_if_t<!std::is_integral_v<T>, int> = 0>
void func(T const &t) {
  std::cout << t << std::endl;
}

template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
void func(T const &t) {
  std::cout << "is integral: " << t << std::endl;
}

int main(int argc, char *argv[]) {
  func(3);
  func('a');
  func(3.1f);
  return 0;
}
