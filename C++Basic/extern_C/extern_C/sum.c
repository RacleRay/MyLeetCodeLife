#include "sum.h"

// C文件导入对应的自身head文件，相当于提前统一定义所有函数。防止在使用某函数时，其定义在后面，而没有被识别

// _sum
int sum(int a, int b) {
	return a + b;
}

int minus(int a, int b) {
	return a - b;
}
