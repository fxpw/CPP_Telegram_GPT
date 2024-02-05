cmake_minimum_required(VERSION 2.8...3.28)
project(cpp_telegram_gpt VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

if(WIN32)
	add_definitions(-D_WIN32_WINNT=0x0601)
endif()

set(Boost_USE_MULTITHREADED ON)
if(MSVC)
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/.env.example ${CMAKE_BINARY_DIR}/Release/.env
	)
else()
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/.env.example ${CMAKE_BINARY_DIR}/.env
	)
endif()

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
    add_definitions(-DWINDOWS_PLATFORM)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/lib/TgBot.lib ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
endif()

if(UNIX AND NOT APPLE)
    add_definitions(-DLINUX_PLATFORM)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-linux/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
endif()

include_directories(include)
