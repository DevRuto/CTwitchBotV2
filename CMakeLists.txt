cmake_minimum_required(VERSION 3.6)
project(CTwitchBotV2)

if(UNIX)
    find_package(Threads)
endif(UNIX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(SOURCE_FILES main.c nr_socket.c nr_socket.h nr_platform.h nr_twitch.c nr_twitch.h nr_utils.c nr_utils.h nr_dictionary.c nr_dictionary.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(CTwitchBotV2 ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(CTwitchBotV2 wsock32 ws2_32)
endif(WIN32)

if(UNIX)
    target_link_libraries(CTwitchBotV2 ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX)