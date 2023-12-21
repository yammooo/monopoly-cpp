set(CMAKE_CXX_STANDARD 11)
project(MonopolyCpp)
cmake_minimum_required(VERSION 3.0)

include_directories(include)

# add_library(${PROJECT_NAME} SHARED src/Book.cpp src/BookShelf.cpp src/Date.cpp)

add_executable(main src/main.cpp src/ObjectModels/Player.cpp src/DependencyInjection/ServiceProvider.cpp)
# target_link_libraries(main ${PROJECT_NAME})