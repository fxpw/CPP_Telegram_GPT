cmake_minimum_required(VERSION 2.8...3.28)
project(cpp_telegram_gpt VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


configure_file(${CMAKE_SOURCE_DIR}/.env ${CMAKE_BINARY_DIR}/.env COPYONLY)
add_executable(${PROJECT_NAME} src/main.cpp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)



# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
# Copy <filename> to build directory
# set(copy_source_dir "${CMAKE_SOURCE_DIR}/src/<path>")
# set(copy_dest_dir "${CMAKE_BINARY_DIR}/Build/<path>/$<CONFIG>")
# set(copy_file_name "<filename>")
# add_custom_command(
#     TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${copy_dest_dir}
# )
# add_custom_command(
#     TARGET ${PROJECT_NAME} POST_BUILD 
#     COMMAND ${CMAKE_COMMAND} -E copy "${copy_source_dir}/${copy_file_name}" "${copy_dest_dir}/${copy_file_name}"
#     COMMENT "Copying ${copy_file_name} to build directory"
# )