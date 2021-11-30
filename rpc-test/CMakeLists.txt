project(rpc-test)

cmake_minimum_required(VERSION 3.8)

set(TARGET ${PROJECT_NAME})

find_package(PkgConfig)
find_package(WPEFramework)
find_package(WPEFrameworkProtocols REQUIRED)

add_executable(${TARGET}
        rpc-test.cpp
        )

target_link_libraries(${TARGET} PRIVATE
        WPEFrameworkCore::WPEFrameworkCore
        WPEFrameworkProtocols::WPEFrameworkProtocols
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS ${TARGET} DESTINATION bin)