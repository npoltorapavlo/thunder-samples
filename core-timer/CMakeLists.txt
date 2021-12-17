project(core-timer)

cmake_minimum_required(VERSION 3.8)

find_package(PkgConfig)
find_package(WPEFramework)
find_package(WPEFrameworkProtocols REQUIRED)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} core-timer.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Threads::Threads
        WPEFrameworkProtocols::WPEFrameworkProtocols
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
