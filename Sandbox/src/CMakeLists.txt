set(game_SRC
    MainGame.cpp
    MainGame.h

    ExampleLayer.cpp
    ExampleLayer.h
    )

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/Engine/src)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src/3rdparty/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src/3rdparty/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src/3rdparty/stb_image)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src/3rdparty/imgui)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src/3rdparty/glm/glm)

add_executable(${PROJECT_NAME} ${game_SRC})

target_link_libraries(${PROJECT_NAME} engine)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
