cmake_minimum_required(VERSION 2.8...3.28)
project(cpp_telegram_gpt VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(Boost_USE_MULTITHREADED ON)

# configure_file(${CMAKE_SOURCE_DIR}/.env.example ${CMAKE_BINARY_DIR}/.env COPYONLY)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/.env.example ${CMAKE_BINARY_DIR}/.env
)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})

find_package(OpenSSL REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENSSL_LIBRARIES})

find_package(Boost COMPONENTS system REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

find_package(CURL REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)


if(WIN32)
    # Добавьте здесь опции, специфичные для Windows
    add_definitions(-DWINDOWS_PLATFORM)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/lib/libTgBot.lib ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
endif()

if(UNIX AND NOT APPLE)
    add_definitions(-DLINUX_PLATFORM)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-linux/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
endif()

# find_package(tgbot-cpp CONFIG REQUIRED)
# include_directories(${TgBot_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} PRIVATE TgBot::TgBot)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

include_directories(include)
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