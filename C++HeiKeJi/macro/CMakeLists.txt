add_executable(macrotest macrotest.cpp)

# sudo apt-get install libglew-dev libsdl2-dev libsdl2-image-dev libglm-dev libfreetype6-dev libglfw3-dev libglfw3
find_package(OpenGL REQUIRED)
target_link_libraries(macrotest PUBLIC OpenGL)
find_package(glfw3 REQUIRED)
target_link_libraries(macrotest PUBLIC glfw)