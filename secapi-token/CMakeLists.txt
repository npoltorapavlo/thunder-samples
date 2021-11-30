project(secapi-token)

cmake_minimum_required(VERSION 3.8)

set(TARGET ${PROJECT_NAME})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(PkgConfig)
find_package(WPEFramework REQUIRED)
find_package(Threads REQUIRED)

# default
if (NOT DEFINED SECAPI_LIB)
    set(SECAPI_LIB sec_api_crypto sec_api_common_crypto)
endif()

find_library(SECAPI NAMES ${SECAPI_LIB})
if (SECAPI)
    set(SECAPI_RELATED_SOURCES token.cpp)
endif() 

add_executable(${TARGET}
        Module.cpp
        secapi-token.cpp
        ${SECAPI_RELATED_SOURCES}
        )

if (WPEFRAMEWORK_FOUND)
    target_include_directories(${TARGET} PRIVATE ${WPEFRAMEWORK_INCLUDE_DIRS})
    target_link_libraries(${TARGET} PRIVATE ${WPEFRAMEWORK_LIBRARIES})
else()
    message(FATAL_ERROR "WPEFramework not found")
endif()

if (SECAPI)
    target_link_libraries(${TARGET} PRIVATE ${SECAPI_LIB})
    add_definitions(-DENABLE_SECAPI)
else()
    message(WARNING "SECAPI not found")
endif()

target_link_libraries(${TARGET} PRIVATE Threads::Threads)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )

install(TARGETS ${TARGET} DESTINATION bin)
