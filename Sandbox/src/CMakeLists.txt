set(game_SRC
    main.cpp
    MainGame.cpp

    MainGame.h
    )

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/Engine/src)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src/3rdparty/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src/3rdparty/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/src/3rdparty/stb_image)

add_executable(${PROJECT_NAME} ${game_SRC})

target_link_libraries(${PROJECT_NAME} engine)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
