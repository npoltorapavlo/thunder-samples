project(jsonrpc-high-load)

cmake_minimum_required(VERSION 3.8)

set(TARGET ${PROJECT_NAME})

find_package(PkgConfig)
find_package(Threads REQUIRED)
find_package(WPEFramework)
find_package(WPEFrameworkCore REQUIRED)
find_package(WPEFrameworkTracing REQUIRED)
find_package(WPEFrameworkPlugins REQUIRED)
find_package(WPEFrameworkProtocols REQUIRED)
find_package(WPEFrameworkSecurityUtil REQUIRED)

add_executable(${TARGET}
        jsonrpc-high-load.cpp
        )

target_link_libraries(${TARGET} PRIVATE
        Threads::Threads
        WPEFrameworkCore::WPEFrameworkCore
        WPEFrameworkTracing::WPEFrameworkTracing
        WPEFrameworkPlugins::WPEFrameworkPlugins
        WPEFrameworkProtocols::WPEFrameworkProtocols
        WPEFrameworkSecurityUtil::WPEFrameworkSecurityUtil
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

install(TARGETS ${TARGET} DESTINATION bin)
install(FILES voice-message.json DESTINATION bin)
