add_library(graphics
    Camera.hpp
    Camera.cpp
    Display.hpp
    Display.cpp
    Mesh.hpp
    Mesh.cpp
    render.hpp
    render.cpp
    Shader.hpp
    Shader.cpp
    stb_image.h
    stb_image.cpp
    Texture.hpp
    Texture.cpp
    Vertex.hpp
)

target_include_directories(graphics PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    ../input
    ../util
)

target_link_libraries(graphics PUBLIC -lGL -lGLEW -lm)