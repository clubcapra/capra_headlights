project(capra_headlights)

cmake_minimum_required(VERSION 3.1)
add_definitions(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        std_msgs
        message_generation
        )


catkin_package(
        CATKIN_DEPENDS roscpp std_msgs
)


add_library(jetsonGPIO_headlights include/jetsonGPIO/jetsonGPIO.c include/jetsonGPIO/jetsonGPIO.h)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
)

add_executable(headlights
        src/headlights.cpp
        )

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(headlights
        ${catkin_EXPORTED_TARGETS}
        )

target_include_directories(headlights PRIVATE jetsonGPIO)

target_link_libraries(headlights ${catkin_LIBRARIES})
