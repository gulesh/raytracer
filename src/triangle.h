#ifndef TRIANGLE_H_
#define TRIANGLE_H_


#include "hittable.h"
#include "AGLM.h"

class triangle : public hittable {
public:
   triangle() : a(0), b(0), c(0), mat_ptr(0) {}
   triangle(const glm::point3& v0, const glm::point3& v1, const glm::point3& v2, 
      std::shared_ptr<material> m) : a(v0), b(v1), c(v2), mat_ptr(m) {};
      
   virtual bool hit(const ray& r, hit_record& rec) const override;

   

public:
   glm::point3 a;
   glm::point3 b;
   glm::point3 c;
   std::shared_ptr<material> mat_ptr;
};

bool triangle::hit(const ray& r, hit_record& rec) const 
   {
      float eps = 0.00001;
      glm::vec3 e1 = b - a;
      glm::vec3 e2 = c - a;
      glm::vec3 outNormal = normalize(cross(e1,e2));
      float len = length(r.direction());
      glm::vec3 unitR = r.direction()/len;
      glm::vec3 p = cross(unitR,e2);
      float aDot = dot(e1, p);
      if(std::abs(aDot) < eps)
      {
         return false;
      }
      float f = 1/aDot;
      glm::vec3 s = r.origin() - a;
      float u = f * (dot(s,p));
      if(u < 0.0 || u > 1.0)
      {
         return false;
      }
      glm::vec3 q = cross(s, e1);
      float v = f * (dot(unitR, q));
      if( (v < 0.0) ||  ( (u+v) > 1.0 ) )
      {
         return false;
      }

      float t = f * (dot(e2, q));
      if( t < 0)
      {
         return false;
         
      }
      // std::cout << dot(s, outNormal)  <<std::endl;
      if(dot(unitR, outNormal) == 0)
      {
         return false;
      }
      rec.t = t/len; // save the time when we hit the object
      rec.p = r.at(rec.t); // ray.origin + t * ray.direction
      rec.mat_ptr = mat_ptr; 

         // save normal
         // glm::vec3 e1n = normalize(e1);
         // glm::vec3 e2n = normalize(e2);
      glm::vec3 outward_normal = outNormal; 
      // std::cout << outward_normal <<std::endl;// compute unit length normal
      rec.set_face_normal(r, outward_normal);
         
      return true;

      
   }

#endif
