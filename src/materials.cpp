// Raytracer framework from https://raytracing.github.io by Peter Shirley, 2018-2020
// alinen 2021, modified to use glm and ppm_image class

#include "ppm_image.h"
#include "AGLM.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "hittable_list.h"

using namespace glm;
using namespace agl;
using namespace std;


color ray_color(const ray& r, const hittable_list& world, int depth)
{
   hit_record rec;
   if (depth <= 0)
   {
      return color(0);
   }

   if (world.hit(r, 0.001f, infinity, rec))
   {
      ray scattered;
      color attenuation;
      if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      {
         color recurseColor = ray_color(scattered, world, depth - 1);
         return attenuation * recurseColor;
      }
      return attenuation;
   }
   vec3 unit_direction = normalize(r.direction());
   auto t = 0.5f * (unit_direction.y + 1.0f);
   return (1.0f - t) * color(0.5, 0.5, 0.5) + t * color(0.5f, 0.7f, 1.0f);
}


color ray_color2(const ray& r, const hittable_list& world, int depth, color& color1, color& color2)
{
   hit_record rec;
   if (depth <= 0)
   {
      return color(0);
   }

   if (world.hit(r, 0.001f, infinity, rec))
   {
      ray scattered;
      color attenuation;
      if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      {
         color recurseColor = ray_color(scattered, world, depth - 1);
         return attenuation * recurseColor;
      }
      return attenuation;
   }
   vec3 unit_direction = normalize(r.direction());
   auto t = 0.5f * (unit_direction.y + 1.0f);
   return (1.0f - t) * color2 + t * color1;
}

color normalize_color(const color& c, int samples_per_pixel)
{
   // todo: implement me!
   float scale = 1.0f / samples_per_pixel;
   float r = std::min(0.999f, std::max(0.0f, c.r * scale));
   float g = std::min(0.999f, std::max(0.0f, c.g * scale));
   float b = std::min(0.999f, std::max(0.0f, c.b * scale));

   // apply gamma correction 
   r = sqrt(r);
   g = sqrt(g);
   b = sqrt(b);

   return color(r, g, b);
}

void ray_trace(ppm_image& image)
{
   // Image
   int height = image.height();
   int width = image.width();
   float aspect = width / float(height);
   int samples_per_pixel = 10; // higher => more anti-aliasing
   int max_depth = 10; // higher => less shadow acne

   
   // Camera
   vec3 camera_pos(0, 0, 6);
   float viewport_height = 2.0f;
   float focal_length = 4.0; 
   float vfov = 1.5708;

   camera cam(camera_pos,viewport_height,aspect, focal_length);

   
   // World
   hittable_list world;
   shared_ptr<material> gray = make_shared<lambertian>(color(0.5f));
   shared_ptr<material> matteGreen = make_shared<lambertian>(color(0, 0.5f, 0));
   shared_ptr<material> metalRed = make_shared<metal>(color(1, 0, 0), 0.3f);
   shared_ptr<material> glass = make_shared<dielectric>(1.5f);
   shared_ptr<material> phongDefault = make_shared<phong>(camera_pos);
   
   world.add(make_shared<sphere>(point3(-2.25, 0, -1), 0.5f, phongDefault));
   world.add(make_shared<sphere>(point3(-0.75, 0, -1), 0.5f, glass));
   world.add(make_shared<sphere>(point3(2.25, 0, -1), 0.5f, metalRed));
   world.add(make_shared<sphere>(point3(0.75, 0, -1), 0.5f, matteGreen));
   world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, gray));
   

   // Ray trace
   for (int j = 0; j < height; j++)
   {
      for (int i = 0; i < width; i++)
      {
         color c(0, 0, 0);
         for (int s = 0; s < samples_per_pixel; s++) // antialias
         {
            float u = float(i + random_float()) / (width - 1);
            float v = float(height - j - 1 - random_float()) / (height - 1);

            ray r = cam.get_ray(u, v);
            c += ray_color(r, world, max_depth);
         }
         c = normalize_color(c, samples_per_pixel);
         
         int x = i;
         int y = j;
         //clamping width
         if (x >= image.width())
         {
            x= image.width() - 1;
         }
         else
         {
            if( x < 0)
            {
               x = 0;
            }
         }
         //clamping height
         if (y >= image.height())
         {
            y = image.height() - 1;
         }
         else
         {
            if( y< 0)
            {
               y = 0;
            }
         }

         image.set_vec3(y, x, c);
      }
   }
   image.save("materials.png"); 
}

void make_scene(ppm_image& image)
{
    // Image
    const float aspect = 3.0 / 2.0;
    const int width = 1200;
    const int height = static_cast<int>(width / aspect);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // Camera
    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 1.25, aspect, aperture, dist_to_focus); 

    //world
    hittable_list world;

   shared_ptr<material>  material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
   shared_ptr<material>  material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
   shared_ptr<material>  material_left   = make_shared<dielectric>(1.5);
   shared_ptr<material>  material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

   world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
   world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
   world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
   world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
   world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));



}
