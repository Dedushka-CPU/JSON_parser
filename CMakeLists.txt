cmake_minimum_required(VERSION 3.10)

project(JSONParser VERSION 1.0)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(JsonParser
    JSONNode.cpp
    JSONParser.cpp
    Tokenizer.cpp
)
target_include_directories(JsonParser PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(JSONParserProg main.cpp)

target_link_libraries(JSONParserProg PRIVATE JsonParser)


