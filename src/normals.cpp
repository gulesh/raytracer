#include <iostream>
#include "ppm_image.h"
#include "AGLM.h"
#include "ray.h"

using namespace glm;
using namespace agl;
using namespace std;

float hit_sphere(const ray& ray, const vec3& vector, float radius)
{
   vec3 oc = ray.origin()-vector;
   float a = dot(ray.direction(), ray.direction());
   float b = 2.0f * dot(oc, ray.direction());
   float c = dot(oc,oc) - radius*radius;
   float discriminant = b*b - 4*a*c;
   if(discriminant < 0)
   {
      return -1;
   }
   else
   {
      return (-b - sqrt(discriminant))/2*a;
   }
}

color ray_color(const ray& ray)
{
   vec3 sphere_center = point3(0,0,-1);
   float t = hit_sphere(ray, sphere_center, 0.5f);
   if (t > 0)
   {
      vec3 hit_point = ray.origin() + t*ray.direction();
      vec3 normal = normalize(hit_point- sphere_center);
      color c = 0.5f *(normal + vec3(1));
      return c;
   }
   vec3 unit_direction = normalize(ray.direction());
   float alpha = 0.5f * (unit_direction.y + 1.0f);
   color c1(0.5, 0.7, 1.0);
   color c2(1.0);
   color c = c2 * (1 - t) + c1 * t;
   return c;
}

void ray_trace(ppm_image& image)
{
   int height = image.height();
   int width = image.width();
   float aspect = width / (float)height;
   float world_height = 2.0f;
   float world_width = world_height * aspect;
   float focal_length = 1.0f;
   vec3 camera_pos = vec3(0);
   vec3 lower_left = camera_pos
      - 0.5f * vec3(world_width, world_height, 0)
      - vec3(0, 0, focal_length);
   for (int i = 0; i < height; i++) // rows
   {
      for (int j = 0; j < width; j++) // cols
      {
         float u = j / ((float)width - 1);
         float v = (height - i - 1) / ((float)height - 1);
         vec3 world_pos = lower_left + vec3(u*world_width, v*world_height, 0);
         color c = ray_color(ray(camera_pos, world_pos - camera_pos));
         image.set_vec3(i, j, c);
         // float u = j / ((float)width - 1);
      }
   }
   image.save("normals.png");
}
