//#pragma once
//和ifdef，define,endif的目的是一致的，只是针对该文件全部内容

#ifndef __SUM_H
#define __SUM_H
// 使用文件名，唯一命名宏定义。
// 宏定义用于防止重复导入

// 以下只对C++程序中的导入，加上额外extern "C"
// C++文件，会默认有宏定义#define __cplusplus
// C程序不会加入extern "C"
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	int sum(int a, int b);
	int minus(int a, int b);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !__SUM_H
