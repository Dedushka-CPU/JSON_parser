cmake_minimum_required(VERSION 3.10)

project(JSONParserProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    JSONNode.cpp
    JSONParser.cpp
    Tokenizer.cpp
    main.cpp  
)

set(HEADERS
    JSONNode.h
    JSONParser.h
    Tokenizer.h
)

add_executable(JSONParser ${SOURCES} ${HEADERS})

target_include_directories(JSONParser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(JSONParser PRIVATE -Wall -Wextra -Wpedantic)
endif()