// Raytracer framework from https://raytracing.github.io by Peter Shirley, 2018-2020
// alinen 2021, modified to use glm and ppm_image class

#include "ppm_image.h"
#include "AGLM.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
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
   return (1.0f - t) * color(1, 0.5, 0) + t * color(0.0f, 0.5f, 1.0f);
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


hittable_list random_scene() {
    hittable_list worldscene;

    shared_ptr<material> ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    worldscene.add(make_shared<sphere>(point3(0,-100,0), 100, ground_material));

    for (int a = -3; a < 3; a++) 
    {
        for (int b = -3; b < 3; b++) 
        {
            float choose_mat = random_float();
            point3 center(a + 0.9*random_float(), 0.2, b + 0.9*random_float());
            std::cout << length((center - point3(4, 0.2, 0))) << std::endl;

            if (length((center - point3(4, 0.2, 0))) > 0.9) {
               shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = glm::color(0.6*random_float(0,.5), 0.3 *random_float(0,.5), 0.4 * random_float(0,.5));
                    sphere_material = make_shared<lambertian>(albedo);
                    worldscene.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = glm::color(0.2*random_float(0,.5), 0.4 *random_float(0,.5), 0.5 * random_float(0,.5));
                    float fuzz = random_float(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    worldscene.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    worldscene.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    shared_ptr<material> material1 = make_shared<dielectric>(1.5);
    worldscene.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    shared_ptr<material> material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    worldscene.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    shared_ptr<material> material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    worldscene.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return worldscene;
}
    

void ray_trace(ppm_image& image)
{
   // Image
   int height = image.height();
   int width = image.width();
   float aspect = width / float(height);
   int samples_per_pixel = 10; // higher => more anti-aliasing
   int max_depth = 10; // higher => less shadow acne

// UNIQUE Scene case
   // Camera
   // point3 lookfrom(-40, 10, 30);
   // point3 lookAt(0,0,0);
   // vec3 vyup(0,1,0);
   // float vfov = 5;
   // float aperture = 10.0f;
   // float viewport_height = 2.0f;
   // float focal_length = 5.0f;
   
   
   // camera cam(lookfrom, lookAt, vyup, vfov, aspect);
   // World
   // hittable_list world = random_scene() ;

//below is a different image which is used to test blur and zoom


   vec3 camera_pos(0, 50, 300);
   point3 lookfrom(0, 50, 100); //angle-4 Front
   point3 lookAt(0,50,0);
   vec3 vyup(0,1,0);
   
   // point3 lookfrom(10, 100, 0); // angle -3 TOP
   // point3 lookAt(0,0,0);
   // vec3 vyup(0,1,-1);
   
   // point3 lookfrom(100, 100, 100);  angle-2
   // point3 lookAt(0,0,0);
   // vec3 vyup(0,1,-1);

   // point3 lookfrom(0, 100, 100); //angle-1
   // point3 lookAt(0,0,0);
   // vec3 vyup(0,1,-1);

   float vfov = 120;
   float aperture = 1.0f;
   float viewport_height = 5.0f;
   float focal_length = 50.0f;
   //float focal_length = length(lookAt - lookfrom);

   camera cam(lookfrom, lookAt, vyup, vfov, aspect);
   // camera cam(lookfrom, lookAt, vyup, vfov, aperture, aspect, focal_length); //focal blur camera 
  

   //world
   hittable_list world;
   
   shared_ptr<material> red = make_shared<metal>(color(1, 0.2, 0.2), 0.1f);
   shared_ptr<material> green = make_shared<metal>(color(0.2, 1, 0.2), 0.1f);
   shared_ptr<material> blue = make_shared<metal>(color(0.2, 0.2, 1),0.1f);
   shared_ptr<material> yellow = make_shared<metal>(color(0.6, 0.6, 0), 0.0f);
   shared_ptr<material> material1 = make_shared<lambertian>(color(0.4, 0.0, 0.7));
   shared_ptr<material> darkgray = make_shared<lambertian>(color(0.25, 0.25, 0.25));
   shared_ptr<material> material2 = make_shared<lambertian>(color(0.0, 0.5f, 1.0f));
   shared_ptr<material> metal1 = make_shared<metal>(color(0, 0.5, 0.5), 0.3f);
   shared_ptr<material> metal2 = make_shared<metal>(color(1, 0.1, 0.5), 0.2f);
   shared_ptr<material> glass1 = make_shared<dielectric>(1.5f);
   shared_ptr<material> glass2 = make_shared<dielectric>(1.7f);
   shared_ptr<material> glass = make_shared<dielectric>(1.0f);
   shared_ptr<material> phongDefault = make_shared<phong>(camera_pos);

   //setting the background
   shared_ptr<material> phongDefaultBackWall = make_shared<phong>(color(0,1,1), color(1,0,1), color(.01f, .01f, .01f), point3(5,5,0), vec3(0,200,-99),0.45, 0.45, 0.1, 10 ); //used for back wall
   shared_ptr<material> phongDefault2 = make_shared<phong>(color(0.6, 0.6, 0), color(0.4, 0.0, 0.7), color(.01f, .01f, .01f), point3(0,100,0), lookfrom, 0.5, 0.6, 0.3, 20);
   shared_ptr<material> phongDefaultFloor = make_shared<phong>(color(0.8, 0.8, 0.8), color(0.6, 0.4, 0.7), color(.01f, .01f, .01f), point3(0,50,0), lookfrom, 0.3, 0.2, 0.5, 50);
   shared_ptr<material> phongDefaultLeftWall = make_shared<phong>(color(0.8, 0.8, 0.8), color(0.6, 0.4, 0.7), color(.01f, .01f, .01f), point3(-199,100,0), lookfrom, 0.3, 0.2, 0.5, 50);
   shared_ptr<material> phongDefaultRightWall = make_shared<phong>(color(0.8, 0.8, 0.8), color(0.6, 0.4, 0.7), color(.01f, .01f, .01f), point3(199,100,0), lookfrom, 0.3, 0.2, 0.5, 50);


   world.add(make_shared<plane>(point3(0, 0, 0), vec3(0,1,0), phongDefaultFloor)); //floor plane
   world.add(make_shared<plane>(point3(200, 0, 0), vec3(-1,0,0), phongDefaultRightWall)); //righ wall plane
   world.add(make_shared<plane>(point3(-200, 0, 0), vec3(1,0,0), phongDefaultLeftWall)); //left wall plane
   world.add(make_shared<plane>(point3(0, 0, -100), vec3(0,0,1), phongDefaultBackWall)); //back wall

   // world.add(make_shared<triangle>(point3(100, -100, -100), point3( 0, 50, -100), point3(-100, -100, -100), phongDefault));
   // world.add(make_shared<triangle>(point3(100, -100, -100), point3( 0, 50, -100), point3(-100, -100, -100), phongDefault));
   world.add(make_shared<sphere>(point3(0, 0, 0), 50, glass1));
   world.add(make_shared<sphere>(point3(0, 20, 80), 20, red));
   world.add(make_shared<sphere>(point3(0, 20, -80), 20, green));
   world.add(make_shared<sphere>(point3(80, 20, 0), 20, blue));
   world.add(make_shared<sphere>(point3(-80, 20, 0), 20, yellow));
   // world.add(make_shared<sphere>(point3(-70, 30, 0), 30, metal1));
   // world.add(make_shared<triangle>(point3(50, 50, 50), point3( -50, 50, 0), point3(50, 50, -50), metal2));
   // world.add(make_shared<triangle>(point3(100, -100, -20), point3( 0, 50, -20), point3(-100, -100, -20), phongDefault));
   // world.add(make_shared<triangle>(point3(200, -100, -100), point3( 100, 50, -100), point3(100, -100, -100), metal1));
   // world.add(make_shared<triangle>(point3(100, -100, -100), point3( 0, -130, -100), point3(-100, -100, -100), phongDefault));

   // world.add(make_shared<triangle>(point3(-100, 100, 1), point3( 0, -50, 1), point3(100, 0, 1), material2));
   // world.add(make_shared<triangle>(point3(-100, 100, 1), point3( 0, 50, 1), point3(100, 100, 1), metal2));
   // world.add(make_shared<triangle>(point3(-100, 100, 1), point3( 0, 130, 1), point3(100, 100, 1), phongDefault));

   
   



   

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
         image.set_vec3(j, i, c);
      }
   }

   image.save("raytracer.png");
   
}
