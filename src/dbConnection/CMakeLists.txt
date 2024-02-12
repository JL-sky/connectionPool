# 将当前目录下的所有源文件定义到SRC_LIST中
aux_source_directory(. SRC_LIST)

# 可执行文件的生成
add_executable(connectionPool ${SRC_LIST})
# 指定可执行文件生成所需的链接库
target_link_libraries(connectionPool mysqlclient pthread)