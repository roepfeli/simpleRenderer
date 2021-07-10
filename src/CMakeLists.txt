add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(util)

target_link_libraries(simpleRenderer PUBLIC graphics input util)