# raytracer

Implements a raytracer based on the book [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html). 

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
raytracer $ mkdir build
raytracer $ cd build
raytracer/build $ cmake -G "Visual Studio 16 2019" ..
raytracer/build $ start CS312-Raytracer.sln
```

Your solution file should contain multiple projects, such as `gradient` and `normals`.
To run from the git bash command shell, 

```
raytracer/build $ ../bin/Debug/gradient
raytracer/build $ ../bin/Debug/normals
```

*macOS*

Open terminal to the directory containing this repository.

```
raytracer $ mkdir build
raytracer $ cd build
raytracer/build $ cmake ..
raytracer/build $ make
```

To run each program from build, you would type

```
raytracer/build $ ../bin/gradient
raytracer/build $ ../bin/normals
```


# lectures Demos

#1 Gradient

<img width="640" alt="Screen Shot 2021-04-09 at 12 03 44 AM" src="https://user-images.githubusercontent.com/60520906/114126798-2022d680-98c7-11eb-8cb3-19fc14858a3d.png">

#2 Silhoutte

<img width="638" alt="Screen Shot 2021-04-09 at 12 05 03 AM" src="https://user-images.githubusercontent.com/60520906/114126888-48123a00-98c7-11eb-8d2a-eb04f88f99ce.png">

#3 Normals

<img width="638" alt="Screen Shot 2021-04-09 at 12 06 19 AM" src="https://user-images.githubusercontent.com/60520906/114126969-7728ab80-98c7-11eb-8219-8acb27defc24.png">

# Basic RayTracer

#1 Simple Ray Tracer (no scattering)

<img width="642" alt="Screen Shot 2021-04-09 at 12 10 10 AM" src="https://user-images.githubusercontent.com/60520906/114127237-0f269500-98c8-11eb-932e-44e2e48e6580.png">

#2 Ray Scattering 

<img width="639" alt="Screen Shot 2021-04-09 at 12 08 45 AM" src="https://user-images.githubusercontent.com/60520906/114127271-1f3e7480-98c8-11eb-9104-df6a527e0b68.png">

# Primitives
#1 Plane: the ground beneath the sphere is a plane.

<img width="640" alt="Screen Shot 2021-04-09 at 12 17 34 AM" src="https://user-images.githubusercontent.com/60520906/114127909-35006980-98c9-11eb-9818-9653fc730988.png">

#Triangles

<img width="640" alt="Screen Shot 2021-04-09 at 12 24 46 AM" src="https://user-images.githubusercontent.com/60520906/114128281-046cff80-98ca-11eb-9c7c-67d3ca354452.png">

# Materials
from left to right:
1.Phong
2.Glass
3.Matte
4.Metal


<img width="636" alt="Screen Shot 2021-04-09 at 12 26 27 AM" src="https://user-images.githubusercontent.com/60520906/114128441-5ca40180-98ca-11eb-8def-0e13df6db7dd.png">

# Unique Features
1. Changing camera position
2. Focal blur
4. Zooming in and out

## field of view = 50 degrees:

<img width="639" alt="Screen Shot 2021-04-09 at 1 30 56 PM" src="https://user-images.githubusercontent.com/60520906/114218850-f6ee5e80-9937-11eb-944b-0197b81d9d6b.png">

## field of view = 80 degrees:

<img width="640" alt="Screen Shot 2021-04-09 at 1 32 58 PM" src="https://user-images.githubusercontent.com/60520906/114219019-2735fd00-9938-11eb-93d1-5e9dacbe48ab.png">



# Unique Images
1. Spheres randomly arranged

<img width="636" alt="Screen Shot 2021-04-09 at 12 00 12 AM" src="https://user-images.githubusercontent.com/60520906/114128609-bc9aa800-98ca-11eb-83af-1ded25636e88.png">







