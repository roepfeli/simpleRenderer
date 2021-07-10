add_library(graphics
    Camera.hpp
    Camera.cpp
    Display.hpp
    Display.cpp
    Mesh.hpp
    Mesh.cpp
    Render.hpp
    Render.cpp
    Shader.hpp
    Shader.cpp
    stb_image.h
    stb_image.cpp
    Texture.hpp
    Texture.cpp
)

target_include_directories(graphics PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    ../input
    ../util
)

target_link_libraries(graphics PUBLIC -lGL -lGLEW -lm)