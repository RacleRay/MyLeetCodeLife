#include "template_ins.h"

#include <vector>
#include <iostream>


template <class V>
struct variant_to_tuple_of_vector;


template <class ...Ts>
struct variant_to_tuple_of_vector<std::variant<Ts...>> {
    using type = std::tuple<std::vector<Ts>...>;
};

// class std::tuple<std::vector<int>, std::vector<double>, std::vector<std::basic_string<char>>>
static variant_to_tuple_of_vector<Object>::type objects;


//=================================================================================
// static for

template <size_t N, class Lambda>
auto static_for(Lambda&& lambda) {
    return [&] <size_t ...Is> (std::index_sequence<Is...>) {
        return (lambda(std::integral_constant<size_t, Is>{}), ...);
    }(std::make_index_sequence<N>());
}


template <size_t N, class Lambda>
auto static_for_break_if_false(Lambda&& lambda) {
    return [&] <size_t ...Is> (std::index_sequence<Is...>) {
        return (lambda(std::integral_constant<size_t, Is>{}) && ...);
    }(std::make_index_sequence<N>());
}


template <size_t N, class Lambda>
void static_for_break_if_true(Lambda&& lambda) {
    return [&] <size_t ...Is> (std::index_sequence<Is...>) {
        return (lambda(std::integral_constant<size_t, Is>{}) || ...);
    }(std::make_index_sequence<N>());
}


// template <size_t N, class Lambda>
// void static_for(Lambda&& lambda) {
//     if constexpr (N > 0) {
//         static_for<N - 1>(lambda);
//         lambda(std::integral_constant<size_t, N - 1>{});
//     }
// }


//=================================================================================
// 

void add_object(Object o) {
    static_for_break_if_false<std::variant_size_v<Object>>([&] (auto ic) {
        if (o.index() == ic.value) {
            std::get<ic.value>(objects).push_back(std::get<ic.value>(o));
            return false;
        }
        return true;
    });
}


void print_objects() {
    static_for<std::variant_size_v<Object>>([&] (auto ic) {
        std::cout << "objects[" << ic.value << "]: ";
        for (auto& o : std::get<ic.value>(objects)) {
            std::cout << o << " ";
        }
        std::cout << std::endl;
    });
}
