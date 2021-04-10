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
1. Changing camera position:

*The image is a room with three walls and a floor and in the middle is a dinnign table made of spheres* 
(float vfov = 100; float aperture = 10.0f; float viewport_height = 2.0f; float focal_length = 50.0f;)

#Angle-1: point3 lookfrom(0, 100, 100); point3 lookAt(0,0,0); vec3 vyup(0,1,-1);

<img width="636" alt="angle-1" src="https://user-images.githubusercontent.com/60520906/114258505-dc969e00-9994-11eb-8fa7-d5a08af351e4.png">

#Angle-2: point3 lookfrom(100, 100, 100); point3 lookAt(10,50,0); vec3 vyup(0,0,-1);

<img width="639" alt="Screen Shot 2021-04-10 at 12 32 58 AM" src="https://user-images.githubusercontent.com/60520906/114258523-ff28b700-9994-11eb-8939-f42a31368d04.png">

#Angle-3:TOP - point3 lookfrom(10, 100, 0); point3 lookAt(0,0,0); vec3 vyup(0,1,-1);

<img width="640" alt="Screen Shot 2021-04-10 at 12 33 47 AM" src="https://user-images.githubusercontent.com/60520906/114258543-254e5700-9995-11eb-9ea3-21fd0385a8fe.png">

#Angle-4:Front - point3 lookfrom(0, 50, 100); point3 lookAt(0,50,0); vec3 vyup(0,1,0);

<img width="637" alt="Screen Shot 2021-04-10 at 12 34 32 AM" src="https://user-images.githubusercontent.com/60520906/114258572-5fb7f400-9995-11eb-9272-ef197030e373.png">

2. Focal blur
<img width="639" alt="Screen Shot 2021-04-10 at 12 58 42 AM" src="https://user-images.githubusercontent.com/60520906/114258906-069d8f80-9998-11eb-9d7d-c4fc89713df1.png">
<img width="654" alt="Screen Shot 2021-04-10 at 12 59 17 AM" src="https://user-images.githubusercontent.com/60520906/114258907-09988000-9998-11eb-9768-fd3ba1632a5c.png">

3. Zooming in and out

## field of view = 50 degrees:

<img width="639" alt="Screen Shot 2021-04-09 at 1 30 56 PM" src="https://user-images.githubusercontent.com/60520906/114218850-f6ee5e80-9937-11eb-944b-0197b81d9d6b.png">

## field of view = 80 degrees:

<img width="640" alt="Screen Shot 2021-04-09 at 1 32 58 PM" src="https://user-images.githubusercontent.com/60520906/114219019-2735fd00-9938-11eb-93d1-5e9dacbe48ab.png">



# Unique Images
1. Spheres randomly arranged

<img width="636" alt="Screen Shot 2021-04-09 at 12 00 12 AM" src="https://user-images.githubusercontent.com/60520906/114128609-bc9aa800-98ca-11eb-83af-1ded25636e88.png">







