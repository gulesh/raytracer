// camera.h, from https://raytracing.github.io by Peter Shirley, 2018-2020
// modified 2021, by alinen, to support glm/float

#ifndef CAMERA_H
#define CAMERA_H

#include "AGLM.h"

class camera 
{
public:
   camera() : origin(0), horizontal(2, 0, 0), vertical(0, 2, 0)
   {
      lower_left_corner = origin - horizontal * 0.5f - vertical * 0.5f - glm::vec3(0,0,1);
   }

   camera(glm::point3 pos, float viewport_height, float aspect_ratio, float focal_length) 
   {
      origin = pos;
      float viewport_width = aspect_ratio * viewport_height;
      horizontal = viewport_width * glm::vec3(1, 0, 0);
      vertical = viewport_height * glm::vec3(0, 1, 0);
      lower_left_corner = origin - horizontal * 0.5f - vertical * 0.5f - glm::vec3(0,0,focal_length);
      u = glm::vec3(0.0f);
      v = glm::vec3(0.0f);
      w = glm::vec3(0.0f);

   }

   camera(glm::point3 lookfrom,
          glm::point3 lookat,
          glm::vec3   vup,
          float vfov, // vertical field-of-view in radian
          float aspect_ratio) 
   {
      float theta = vfov;
      float h = tan(theta/2);
      float viewport_height = 2.0 * h;
      float viewport_width = aspect_ratio * viewport_height;

      w = lookfrom - lookat;
      glm::vec3 unitW = normalize(w);
      u = cross(vup, unitW);
      glm::vec3 unitU = normalize(u);
      v = cross(unitW, unitU);

      origin = lookfrom;
      horizontal = viewport_width * unitU;
      vertical = viewport_height *v;
      lower_left_corner = origin - horizontal * 0.5f - vertical * 0.5f - unitW;
     
   }

   camera(glm::point3 lookfrom,
         glm::point3 lookat,
         glm::vec3   vup,
         float vfov, // vertical field-of-view in degrees
         float aspect_ratio,
         float aperture,
         float focal_length) 
   {
      float theta = vfov;
      float h = tan(theta/2);
      float viewport_height = 2.0 * h;
      float viewport_width = aspect_ratio * viewport_height;

      w = lookfrom - lookat;
      glm::vec3 unitW = normalize(w);
      u = cross(vup, unitW);
      glm::vec3 unitU = normalize(u);
      v = cross(unitW, unitU);

      origin = lookfrom;
      horizontal = focal_length * viewport_width * unitU;
      vertical = focal_length * viewport_height * v;
      lower_left_corner = origin - horizontal * 0.5f - vertical * 0.5f - focal_length * unitW;
      
      lenRadius = aperture/2;

   }

   virtual ray get_ray(float a, float b) const 
   {
      glm::vec3 random = lenRadius * random_unit_disk();
      glm::vec3 offset;
      if(u.x == 0.0f)
      {
         offset = glm::vec3(0,0,0);
      }
      else
      {
         offset = normalize(u) * random.x + normalize(v) * random.y;
      }
      
      return ray(origin + offset, lower_left_corner + a * horizontal + b * vertical - origin - offset);
   }

protected:
  glm::point3 origin;
  glm::point3 lower_left_corner;
  glm::vec3 horizontal;
  glm::vec3 vertical;
  glm::vec3 u;
  glm::vec3 v;
  glm::vec3 w;
  float lenRadius;
};
#endif

