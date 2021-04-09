// ray.h, from https://raytracing.github.io by Peter Shirley, 2018-2020
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "AGLM.h"

class sphere : public hittable {
public:
   sphere() : radius(0), center(0), mat_ptr(0) {}
   sphere(const glm::point3& cen, float r, std::shared_ptr<material> m) : 
      center(cen), radius(r), mat_ptr(m) {};

   virtual bool hit(const ray& r, hit_record& rec) const override;

public:
   glm::point3 center;
   float radius;
   std::shared_ptr<material> mat_ptr;

private:
 
      // static void get_sphere_uv(const glm::point3& p, float& u, float& v) {
      //    // p: a given point on the sphere of radius one, centered at the origin.
      //    // u: returned value [0,1] of angle around the Y axis from X=-1.
      //    // v: returned value [0,1] of angle from Y=-1 to Y=+1.
      //    //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
      //    //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
      //    //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

      //    auto theta = acos(-p.y);
      //    auto phi = atan2(-p.z, p.x) + pi;

      //    u = phi / (2*pi);
      //    v = theta / pi;
      // }
};

bool sphere::hit(const ray& r, hit_record& rec) const 
{

   glm::vec3 el = center - r.origin();
   float len = length(r.direction());
   glm::vec3 unitR = r.direction()/len;

   float s = dot(el, unitR);
   float elSqr = dot(el, el);
   float rSqr = radius * radius;
   if (s < 0 && elSqr > rSqr)
   {
      return false;
   }
   float mSqr = elSqr - s*s;
   if (mSqr > rSqr)
   {
      return false;
   }
   float q = sqrt(rSqr - mSqr);
   float t = -1;
   if(elSqr > rSqr)
   {
      t = s - q;
   }
   else
   {
      t = s + q;
   }

   // save relevant data in hit record
   rec.t = t/len; // save the time when we hit the object
   rec.p = r.at(rec.t); // ray.origin + t * ray.direction
   rec.mat_ptr = mat_ptr; 

   // save normal
   glm::vec3 outward_normal = normalize(rec.p - center); // compute unit length normal
   rec.set_face_normal(r, outward_normal);

   return true;


   // glm::vec3 oc = r.origin() - center;
   // float a = glm::dot(r.direction(), r.direction());
   // float half_b = glm::dot(oc, r.direction());
   // float c = glm::length2(oc) - radius*radius;

   // float discriminant = half_b*half_b - a*c;
   // if (discriminant < 0) return false;
   // float sqrtd = sqrt(discriminant);

   // float t = (-half_b - sqrtd) / a;
   // if (t < 0) t = (-half_b + sqrtd) / a;
   
   // if (t < 0) return false;

   // // save relevant data in hit record
   // rec.t = t; // save the time when we hit the object
   // rec.p = r.at(t); // ray.origin + t * ray.direction
   // rec.mat_ptr = mat_ptr; 

   // // save normal
   // glm::vec3 outward_normal = normalize(rec.p - center); // compute unit length normal
   // rec.set_face_normal(r, outward_normal);

   // return true;
}


#endif

