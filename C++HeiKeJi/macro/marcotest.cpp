#include <cstdio>
#include <string>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


/**
 * @brief 根据平台，定义不同的选项
 *   !!(x)  转换为 bool 类型并保持真假值
 *
 */
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define LIKELY(x)
#define UNLIKELY(x)
#elif defined(__GNUC__) || defined(__clang__)
#define NOINLINE __attribute__((noinline))
#define LIKELY(x) (__builtin_expect(!!(x), 1))
#define UNLIKELY(x) (__builtin_expect(!!(x), 0))
#else
#define NOINLINE
#define LIKELY(x)
#define UNLIKELY(x)
#endif


// #if __cplusplus >= 202002L
// template <class T>
// requires (std::is_signed_v<T>)
// #else
// template <class T, std::enable_if_t<std::is_signed_v<T>, int> = 0>
// #endif


#ifdef _WIN32
#define PATHSEP "\\"
#else
#define PATHSEP "/"
#endif


/**
 * @brief ## 字符串值拼接，#取字面量的字符串
 *
 */
NOINLINE std::string opengl_errno_name(int err) {
    switch (err) {
#define PER_GL_ERROR(x) case GL_##x: return #x;
    PER_GL_ERROR(NO_ERROR)
    PER_GL_ERROR(INVALID_ENUM)
    PER_GL_ERROR(INVALID_VALUE)
    PER_GL_ERROR(INVALID_OPERATION)
    PER_GL_ERROR(STACK_OVERFLOW)
    PER_GL_ERROR(STACK_UNDERFLOW)
    PER_GL_ERROR(OUT_OF_MEMORY)
    }
    return "unknown error: " + std::to_string(err);
}

NOINLINE void check_gl_error(const char *filename, int lineno, const char *expr) {
    int err = glGetError();
    if (UNLIKELY(err != 0)) {
        std::cerr << filename << ":" << lineno << ": " << expr << " failed: " << opengl_errno_name(err) << '\n';
        std::terminate();
    }
}

/**
 * @brief NDEBUG : CMake 编译时，release选项会定义这个宏，debug模式不会定义这个宏
 *    防止重复表达式重复求值
 *    typeof(x) __x = (x);  // gnu C
 *    decltype(x) __x = (x);   // C++
 */
#ifdef NDEBUG
#define ASSERT_GT(x, y)
#else
#define ASSERT_GT(x, y) do { \
    auto __x = (x); \
    auto __y = (y); \
    if (!(__x > __y)) { \
        std::cerr << "Assert failed: " << #x << " (" << __x << ")" << " > " << #y << '\n'; \
        std::terminate(); \
    } \
} while (0)
#endif


/**
 * @brief do {} while (0) : 防止作为分支语句执行时，没有 {} 作用域，导致逻辑错误
 *
 */
#if NDEBUG
#define CHECK_GL(x) do { \
    (x); \
} while (0)
#else /* Not NDEBUG */
#define CHECK_GL(x) do { \
    (x); \
    check_gl_error(__FILE__, __LINE__, #x); \
} while (0)
#endif

/**
 * @brief 最外层 () 在 GCC 中表示一个表达式，GCC 中取表达式最后一个子表达式的值
 *
 */
#define MIN(x, y) ({ \
    typeof(x) __x = (x); \
    typeof(y) __y = (y); \
    __x < __y ? __x : __y; \
})


/**
 * @brief 变参宏用法
 *  "xxx" "yyy" 在C中，会拼接为 "xxxyyy"
 *  __VA_OPT__  C++ 20 特性，将 , 后面的参数作为变参输入
 */
#define STR2(x) #x
#define STR(x) STR2(x)
#define PRINT(x, ...) do { \
    printf(__FILE_NAME__ ":" STR(__LINE__) ": " x __VA_OPT__(,) __VA_ARGS__); \
} while (0)

#define SHOW(x) PRINT(#x " = %d\n", x)

int main() {
    int i = 1;
    SHOW(i);
    PRINT("hello, world\n");
    PRINT("answer is %d\n", 42);
    PRINT("diploma is %d + %d\n", 985, 211);
    return 0;

    if (!glfwInit()) {
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        CHECK_GL(glClear(GL_COLOR_BUFFER_BIT));

        CHECK_GL(glBegin(GL_TRIANGLES));
        CHECK_GL(glVertex2f(-0.5f, -0.5f));
        CHECK_GL(glVertex2f(0.5f, -0.5f));
        CHECK_GL(glVertex2f(0.0f, 0.5f));
        CHECK_GL(glEnd());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}