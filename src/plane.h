#ifndef PLANE_H_
#define PLANE_H_

#include "hittable.h"
#include "AGLM.h"

class plane : public hittable {
public:
   plane() : a(0), n(0), mat_ptr(0) {}
   plane(const glm::point3& p, const glm::vec3& normal, 
      std::shared_ptr<material> m) : a(p), n(normal), mat_ptr(m) {};

   virtual bool hit(const ray& r, hit_record& rec) const override;
   

public:
   glm::vec3 a;
   glm::vec3 n;
   std::shared_ptr<material> mat_ptr;
};

bool plane::hit(const ray& r, hit_record& rec) const
   {
      glm::vec3 pNot = r.origin() - a;
      glm::vec3 p_prime = a - r.origin();
      glm::vec3 v = r.direction();
      float t = -1;
      float valueDV = dot(v, n);
      if(dot(pNot, n) == 0 && valueDV == 0) //ray is in the plane along with ray direction
      {
         return false;
      } 
      else
      {
         if(dot(pNot, n) == 0) //ray origin in the plane
         {
            if (valueDV ==  length(v) * length(n) )
            {
               t = 0;
            }
            else if(valueDV ==  -1 * length(v) * length(n))
            {
               t = 0;
               
            } 
         }

         if (valueDV == 0) 
         {
            t = infinity;
         }
         else
         { 
            float t = dot(p_prime, n)/ valueDV;
            if (t < 0 )
            {
               return false;
            }
            rec.t = t; // save the time when we hit the object
            rec.p = r.at(t); // ray.origin + t * ray.direction
            rec.mat_ptr = mat_ptr; 

         // save normal
            glm::vec3 outward_normal = n; 
            rec.set_face_normal(r, outward_normal);
            return true;
         }
         return false;
      }
   }

#endif
