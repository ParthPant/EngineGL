set (opengl_src
    #cpp files
    main.cpp
    MainGame.cpp

    #header files
    MainGame.h)


add_subdirectory(3rdparty)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(3rdparty/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#add_library (opengl_base ${opengl_src})

add_executable(${PROJECT_NAME} ${opengl_src})

#target_link_libraries(${PROJECT_NAME} opengl_base)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS})


