# SuperMiniRT

SuperMiniRT is a simple raytracing program written in C. It allows you to create and render 3D scenes with basic geometric objects, such as cones, cylinders, spheres, and planes. You can specify your scene in a file ending with `.rt` and render it by providing this file as an argument to the program.

## Installation

To install SuperMiniRT, clone the repository and compile the program using `make`:

### Mac
```bash
git clone https://github.com/yourusername/SuperMiniRT.git
cd SuperMiniRT
make
./miniRT path/to/your_scene.rt
```
### Linux
```bash
git clone https://github.com/yourusername/SuperMiniRT.git
cd SuperMiniRT
make linux
./miniRT path/to/your_scene.rt
```

## Features

- **3D Object Support**: Add cones, cylinders, spheres, and planes to your scenes.
- **Camera Movement**: Move the camera around to view your scene from different perspectives.
- **Bump Mapping**: Apply bump maps to objects for added surface detail.
- **Texture Mapping**: Apply images as textures to your objects.
- **Specular Reflection**: Simulate reflective surfaces with specular highlights.
- **Colored Lights**: Add colored light sources to your scenes.
- **Multithreading**: Take advantage of multithreading for faster rendering.

