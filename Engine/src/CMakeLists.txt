set (opengl_src
    #cpp files
    Sprite.cpp
    GLSLProgram.cpp
    Log.cpp
    IOManager.cpp
    ImageLoader.cpp
    ResourceManager.cpp
    TextureCache.cpp

    #header files MainGame.h Sprite.h
    GLSLProgram.h
    IOManager.h
    Log.h
    ImageLoader.h
    GLTexture.h
    ResourceManager.h
    TextureCache.h
    )

add_subdirectory(3rdparty)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(3rdparty/glad/include)
include_directories(3rdparty/spdlog/include)
include_directories(3rdparty/stb_image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${opengl_src})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS} spdlog stb_image)
