set (opengl_src
    #cpp files
    Sprite.cpp
    GLSLProgram.cpp
    Log.cpp
    IOManager.cpp
    Window.cpp
    Engine.cpp
    Camera2D.cpp
    SpriteBatch.cpp
    InputManager.cpp
    Timing.cpp
    GLTexture.cpp
    Application.cpp
    Layers.cpp
    ImGuiLayer.cpp

    #header files MainGame.h Sprite.h
    Layers.h
    GLSLProgram.h
    Camera2D.h
    Window.h
    Engine.h
    IOManager.h #not using this anywhere
    Log.h
    GLTexture.h
    SpriteBatch.h
    InputManager.h
    Timing.h
    Application.h
    Entrypoint.h
    ImGuiLayer.h
    )


add_subdirectory(3rdparty)
add_subdirectory(Events)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(3rdparty/glad/include)
include_directories(3rdparty/spdlog/include)
include_directories(3rdparty/imgui)
include_directories(3rdparty/imgui/backends)
include_directories(3rdparty/stb_image)
include_directories(3rdparty/glm/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

get_property(global_SRC GLOBAL PROPERTY global_SRC) 
set(global_SRC
    ${opengl_src}
    ${global_SRC}
    )

add_library(${PROJECT_NAME} ${global_SRC})
add_compile_options(-extra-arg-before=-xc++)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS} spdlog stb_image glm imgui)
