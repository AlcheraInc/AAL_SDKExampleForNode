cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)

project(examples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_definitions(-DNAPI_VERSION=4)
include_directories(${PROJECT_SOURCE_DIR}/../node_modules/node-addon-api)
message(STATUS ${PROJECT_SOURCE_DIR}/../node_modules/node-addon-api)
include_directories(${CMAKE_JS_INC})

# OpenCV
set(OpenCV_DIR $ENV{HOME}/opencv/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")
message(STATUS "OpenCV ${OpenCV_VERSION} found (${OpenCV_CONFIG_PATH})")
include_directories(${OpenCV_INCLUDE_DIR})

# add_executable(examples main.cpp)
set(SOURCE_FILES bindings.cpp)
add_library(examples SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(examples PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(examples ${CMAKE_JS_LIB} ${OpenCV_LIBRARIES})