# SDF Renderer
This project aims to develop an SDF-based ray marching renderer from scratch (without any game engine), supporting real-time Boolean operations and offering a flexible, performant approach to procedural rendering. 
![sdf-img](https://i.ibb.co/39h54pQc/Screenshot-2025-03-22-013750.png)

## Features
1. Add/Remove simple primitives to scene (Sphere, Box, Cylinder)
2. Diffuse Lighting
3. User modifiable shape properties
4. Boolean operations to provide CSG functionality

## Compilation
run the following commands to setup the project using cmake.
```bash
mkdir build-release
cd  build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
```
Once the above cmake command finishes running and no errors show up, run
```bash
cmake --build . --target spline_editor -j 30
```
```-j 30``` lets cmake build in parallel, it is recommended to use this to make your compile times shorter.

Once compiled, the executable will be available in a new directory ```bin``` in the root directory of the project.

## Known Compilation Issues
Debug builds fails, due large obj file size. This is not present in Release build.
