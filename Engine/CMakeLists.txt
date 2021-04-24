cmake_minimum_required(VERSION 3.10)

# set the project name
project(engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY global_SRC "")
macro (add_source sources)
    foreach(_SRC ${ARGV})
        get_filename_component(_ABS_SRC ${_SRC} ABSOLUTE)
        set_property(GLOBAL APPEND PROPERTY global_SRC ${_ABS_SRC})
    endforeach()
    unset(_SRC)
    unset(_ABS_SRC)
endmacro()

add_subdirectory(src)

