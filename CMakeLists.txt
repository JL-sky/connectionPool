cmake_minimum_required(VERSION 3.0)
project(connectionPool)

# 配置编译器选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
# 配置可执行程序生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/dbConnection)

# 加载源文件子目录
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
