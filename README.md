# SuperMiniRT

SuperMiniRT is a powerful raytracing renderer written in C that enables the creation of stunning 3D scenes with geometric primitives, advanced lighting effects, textures, and reflections. The program renders scenes defined in `.rt` files, producing high-quality images with realistic lighting and surface effects.

![SuperMiniRT Render Example](https://github.com/yourusername/SuperMiniRT/raw/master/screenshots/render_example.png)

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

- **3D Object Support**: Create scenes with spheres, planes, cylinders, and cones
- **Realistic Lighting**: Ambient lighting, point lights with intensity control, and colored light sources
- **Material Properties**: Adjust specular reflection for shiny surfaces and mirror reflections
- **Texture Mapping**: Apply XPM images as textures to any object
- **Bump Mapping**: Add surface detail with bump maps for realistic terrain and textures
- **Checkerboard Patterns**: Apply built-in checkerboard patterns to object surfaces
- **Interactive Camera**: Navigate your scenes in real-time with keyboard controls
- **Multithreaded Rendering**: Utilize multiple CPU cores for faster rendering

## Controls

### Standard Keyboard Controls
- **Camera Movement**:
  - `W`: Move forward
  - `S`: Move backward
  - `A`: Move left
  - `D`: Move right
  - Special keys `LS` and `RS`: Move up and down
  
- **Camera Rotation**:
  - `↑`: Tilt camera up
  - `↓`: Tilt camera down
  - `←`: Rotate camera left
  - `→`: Rotate camera right
  
- **General**:
  - `ESC`: Exit the application

### Linux/Controller Support
The application also supports controller inputs when compiled with the Linux target.

## Scene File Format (.rt)

SuperMiniRT uses a simple text-based format for scene definition. Each element is defined on its own line with space-separated parameters.

### Scene Elements

#### Ambient Lighting
```
A [intensity] [R,G,B]
```
Example: `A 0.2 255,255,255`

#### Camera
```
C [x,y,z] [norm_x,norm_y,norm_z] [FOV]
```
Example: `C 0,0,-50 0,0,1 70`

#### Light
```
L [x,y,z] [intensity] [R,G,B]
```
Example: `L 0,10,-30 0.6 255,255,255`

### Objects

#### Sphere
```
sp [x,y,z] [diameter] [R,G,B] [spec] [reflect] [texture] [bump] [disrupt]
```
Example: `sp 0,0,0 10 255,255,0 0 0 0 0 0`

#### Plane
```
pl [x,y,z] [norm_x,norm_y,norm_z] [R,G,B] [spec] [reflect] [texture] [bump] [disrupt]
```
Example: `pl 0,0,80 0,0,1 255,0,0 0 0 0 0 0`

#### Cylinder
```
cy [x,y,z] [norm_x,norm_y,norm_z] [diameter] [height] [R,G,B] [spec] [reflect] [texture] [bump] [disrupt]
```
Example: `cy 0,0,0 1,0,0 10 3 255,255,0 0 0 0 0 0`

#### Cone
```
co [x,y,z] [norm_x,norm_y,norm_z] [diameter] [height] [R,G,B] [spec] [reflect] [texture] [bump] [disrupt]
```
Example: `co 0,-8,0 0,1,1 5 5 255,0,255 0 0 0 0 0`

### Parameter Details

- **Position (x,y,z)**: Coordinates in 3D space
- **Normal Vector (norm_x,norm_y,norm_z)**: Normalized direction vector
- **Colors (R,G,B)**: RGB values ranging from 0-255
- **spec**: Specular reflection coefficient (0.0+)
- **reflect**: Reflectivity (0.0-1.0)
- **texture**: Path to texture image (.xpm) or 0 for none
- **bump**: Path to bump map (.xpm) or 0 for none
- **disrupt**: Disruption option (0 = none, 1 = checkerboard)

## Example Scenes

SuperMiniRT comes with several example scenes in the `scenes/` directory:

- `SphereBasic.rt`: Basic scene with spheres
- `PlaneBasic.rt`: Scene demonstrating planes
- `CylinderBasic.rt`: Scene with various cylinders
- `ConeBasic.rt`: Scene featuring cones
- `ComplexBasic.rt`: Complex scene with multiple object types
- `MegaMirror.rt`: Scene demonstrating reflective surfaces
- `Pretty_Scene.rt`: Aesthetically pleasing demo scene

## Advanced Features

### Textures and Bump Mapping
Use any XPM image from the `imgs/` directory as a texture or bump map:
```
sp 0,0,0 10 255,255,0 0 0 imgs/earth_map.xpm imgs/bump_earth_final.xpm 0
```

### Reflective Surfaces
Create mirrors or partially reflective surfaces:
```
pl 0,0,80 0,0,1 255,255,255 0 0.8 0 0 0
```

### Combined Effects
Combine textures, bump maps, and reflections for stunning results:
```
sp 0,0,0 10 255,255,0 0.5 0.3 imgs/earth_map.xpm imgs/bump_earth_final.xpm 0
```

## Tips and Tricks

1. For realistic scenes, use moderate ambient light (0.1-0.3)
2. Position multiple lights to create interesting shadows and highlights
3. Use bump maps with textured objects for more realistic surfaces
4. Experiment with specular values between 0.0 and 1.0 for different material effects
5. Keep reflectivity under 0.5 for most objects unless creating mirrors

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Technical Implementation

SuperMiniRT implements specific ray tracing algorithms and techniques from computer graphics literature:

### Core Algorithm
- **Whitted Ray Tracing**: Classic ray tracing algorithm by Turner Whitted (1980) supporting reflection, shadows, and specular highlights
- **Ray-Surface Intersection**: Direct algebraic solutions for geometric primitives
- **Recursive Ray Tracing**: Implements tree-based recursive ray calculations with configurable depth limit
- **Scanline Parallel Processing**: Divides image into columns for thread-based parallel rendering

### Geometric Intersection Algorithms
- **Analytic Quadratic Solution**: For ray-sphere intersection, using the discriminant method from computational geometry
- **Plane Equation Solver**: Implements the ray-plane intersection using the parametric plane equation
- **Parametric Cylinder Equation**: Full cylinder intersection with quadratic solution for body and plane intersection for caps
- **Generalized Cone Formulation**: Specialized quadratic solution using the cone parameter m = (radius²/height²)

### Illumination Model
- **Phong Reflection Model**: Complete implementation of the classic Bui Tuong Phong (1975) illumination model with:
  - Lambert's Cosine Law for diffuse reflection (dot product of normal and light direction)
  - Phong specular term: cos^n(R·V) using reflection vector and view direction
  - Constant ambient term
- **Shadow Ray Algorithm**: Direct occlusion testing using ray casting from intersection point to light source

### Material & Texture Techniques
- **Fresnel-Approximated Reflection**: Simplified reflection model with configurable reflection coefficient
- **Spherical UV Mapping**: Arctangent-based spherical coordinate mapping for texture projection
- **Cylindrical UV Mapping**: Combination of angular and linear mapping for cylinder surfaces
- **Tangent Space Normal Mapping**: TBN (Tangent, Bitangent, Normal) matrix transformation for bump mapping
- **Procedural Checkerboard Generation**: Mathematical pattern generation using position coordinates

### Optimization Techniques
- **Thread Pool Implementation**: Worker thread architecture for CPU parallelization (up to 50 threads)
- **Function Pointer Dispatch**: Virtual method table pattern for polymorphic object behavior
- **Spatial Bounds Optimization**: Ray parameter bounds (tmin, tmax) for limiting intersection tests
- **Early Ray Termination**: Immediate ray exit when shadow intersection is found
- **Mutex-Based Synchronization**: Thread-safe work distribution model

## Acknowledgments

- The MiniLibX library for handling graphics
- The ray tracing algorithms are based on "Ray Tracing in One Weekend" by Peter Shirley