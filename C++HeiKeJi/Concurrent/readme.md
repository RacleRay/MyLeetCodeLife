所有需要微性能测试的程序，先下载编译 Google Benchmark
$ export GBEN_LIB=/home/xxx/benchmark/build/src/
$ clang++ -g -O3 -mavx2 -Wall -pedantic -I$GBEN_INC -lpthread -latomic -lrt -lm intrusive_shared_pointer.cpp $GBEN_LIB/libbenchmark.a -o benchmark

定义的类和测试函数写在一起，主要是为了让测试的上下文环境更稳定一些，防止编译器对多文件编译链接时优化行为的不同带来的不确定影响。
