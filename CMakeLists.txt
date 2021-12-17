cmake_minimum_required(VERSION 3.3)

project(thunder-samples)

option(wpeframework-test "Include wpeframework-test." OFF) #TODO
option(jsonrpc-test "Include jsonrpc-test." ON)
option(core-timer "Include core-timer." ON)
option(rpc-test "Include rpc-test." ON)

if(wpeframework-test)
    add_subdirectory(wpeframework-test)
endif()
if(jsonrpc-test)
    add_subdirectory(jsonrpc-test)
endif()
if(core-timer)
    add_subdirectory(core-timer)
endif()
if(rpc-test)
    add_subdirectory(rpc-test)
endif()
