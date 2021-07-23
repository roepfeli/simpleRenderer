# simpleRenderer
a simple openGLES 3D engine

![Hello](https://i.imgur.com/WsKvs9f.png)

# features

## general
    - perspective 3D rendering
    - Textures

## lighting
    - ambient lighting (one per draw-call)
    - diffuse lighting (up to 64 per draw-call)
    - specular lighting (up to 64 per draw-call)

# build

## prerequisites

install glm, glew and glfw3 and build using cmake

```
sudo apt install libglm-dev libglew-dev libglfw3-dev cmake
```
```
git clone https://github.com/roepfeli/simpleRenderer.git
```
```
cd simpleRenderer

mkdir build && cd build
cmake ..
make
```
Execute program in master-directory:
```
./build/src/simpleRenderer
```
