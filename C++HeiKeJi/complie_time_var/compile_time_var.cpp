/*************************************************************************
    > File Name: compile_time_var.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <iostream>
#include <vector>
#include <variant>


template <class ...Fs>
struct match: protected Fs... {
    explicit match(Fs const &...fs): Fs(fs)... {}
    using Fs::operator()...;
};

template <class ...Fs>
match(Fs const & ...fs) -> match<Fs...>;



std::variant<std::false_type, std::true_type>
bool_variant(bool x) {
    if (x)
        return std::true_type{};
    else
        return std::false_type{};
}


void vary_version_func(std::vector<float> a, int b, int c) {
    auto condi_b = bool_variant(b != 1);
    auto condi_c = bool_variant(c != 0);
    // simd
    std::visit([&] (auto condi_b, auto condi_c) {
        static int _ = printf("instanced !! \n");
        for (auto &ai: a) {
            if constexpr (condi_b)
                ai *= b;
            if constexpr (condi_c)
                ai += c;
        }
    }, condi_b, condi_c);
}


int main(int argc, char *argv[]) {
    /*std::variant<std::false_type, std::true_type> v;*/
    //auto func = [&] (auto val) {
        //static int _ = printf("instanced !! \n");
        //if constexpr (val)
            //std::cout << "true" << std::endl;
        //else
            //std::cout << "false" << std::endl;
    //};

    //func(std::false_type{});
    //func(std::true_type{});


    // ===== ver 2 =====
    /*std::variant<std::false_type, std::true_type> v;*/
    //v = std::false_type{};
    //std::visit([&] (auto val) {
        //static int _ = printf("instanced !! \n");
        //if constexpr (val)
            //std::cout << "true" << std::endl;
        //else
            //std::cout << "false" << std::endl;
    //}, v);
    
    std::vector<float> a(1024);
    vary_version_func(a, 1, 0);
    vary_version_func(a, 1, 1);

    return 0;
}
