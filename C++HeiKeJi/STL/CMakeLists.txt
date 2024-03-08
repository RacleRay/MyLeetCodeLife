add_executable(test_function function.hpp test_function.cpp)
add_executable(test_unique unique_ptr.hpp test_unique.cpp)
add_executable(test_array Array.hpp test_array.cpp)
add_executable(test_vector Vector.hpp test_vector.cpp)

add_executable(test_any Any.hpp test_Any.cpp)
target_compile_definitions(test_any PRIVATE -DGLOG_USE_GLOG_EXPORT -std=c++20 -lglog)