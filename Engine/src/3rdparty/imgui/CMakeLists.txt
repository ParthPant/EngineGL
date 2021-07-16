set (imgui_src
    
    CMakeLists.txt
    imconfig.h
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui.h
    imgui_impl_opengl3.cpp
    imgui_impl_opengl3.h
    imgui_impl_sdl.cpp
    imgui_impl_sdl.h
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    )

find_package(SDL2 REQUIRED)

add_library(imgui ${imgui_src})

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

target_include_directories(imgui PRIVATE ${PARENT_DIR}/glad/include) 
target_include_directories(imgui PRIVATE ${SDL2_INCLUDE_DIRS}) 
target_include_directories(imgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 
target_compile_definitions(imgui PUBLIC -DIMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(imgui PRIVATE glad ${CMAKE_DL_LIBS})
