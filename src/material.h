#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <cmath>
#include "AGLM.h"
#include "ray.h"
#include "hittable.h"

class material {
public:
  virtual bool scatter(const ray& r_in, const hit_record& rec, 
     glm::color& attenuation, ray& scattered) const = 0;
   virtual ~material() {}
};

class lambertian : public material {
public:
   lambertian(const glm::color& a) : albedo(a) {}

  virtual bool scatter(const ray& r_in, const hit_record& rec, 
     glm::color& attenuation, ray& scattered) const override 
  {
     // todo
      using namespace glm;
      // vec3 unitn = normalize(rec.normal);
      // vec3 lightdir = normalize(vec3(5,5,0) - rec.p);
      // color diffuse = max(vec3(0), dot(unitn, lightdir)) * albedo;
      // attenuation = diffuse;
      // return false;

      vec3 scatter_direction = rec.normal + random_unit_vector();
      if (near_zero(scatter_direction))
      {
         scatter_direction = rec.normal;
      }
      scattered = ray(rec.p, scatter_direction);
      // attenuation = albedo->value(rec.u, rec.v, rec.p);
      attenuation = albedo;
      return false; //bounce

  }

public:
glm::color albedo;
};
//diffuseColor(0,0,1), 
   //   specColor(1,1,1),
class phong : public material {
public:
  phong(const glm::vec3& view) :
     diffuseColor(0,0,1), 
     specColor(1,1,1),
     ambientColor(.01f, .01f, .01f),
     lightPos(5,5,0),
     viewPos(view), 
     kd(0.45), ks(0.45), ka(0.1), shininess(10.0) 
  {}

  phong(const glm::color& idiffuseColor, 
        const glm::color& ispecColor,
        const glm::color& iambientColor,
        const glm::point3& ilightPos, 
        const glm::point3& iviewPos, 
        float ikd, float iks, float ika, float ishininess) : 
     diffuseColor(idiffuseColor), 
     specColor(ispecColor),
     ambientColor(iambientColor),
     lightPos(ilightPos),
     viewPos(iviewPos), kd(ikd), ks(iks), ka(ika), shininess(ishininess) 
  {}

  virtual bool scatter(const ray& r_in, const hit_record& hit, 
     glm::color& attenuation, ray& scattered) const override 
  {
      using namespace glm;
      //ambient
      color ambient = ka*ambientColor;
      //diffuse
      vec3 l = lightPos - hit.p; //light vector
      vec3 unitL = normalize(l); 
      vec3 unitN = normalize(hit.normal);
      float scalarLN = dot(unitL, unitN);
      float max = std::max(0.0f, scalarLN);
      color diffuse = kd*max*diffuseColor*(1.0f);
      //specular
      vec3 r = 2 * dot(unitL, unitN) * unitN - unitL; //reflected ray
      vec3 unitR = normalize(r);
      vec3 v = viewPos - hit.p; //view vector
      vec3 unitV = normalize(v);
      float cosPhi = dot(unitV, unitR); 
      float positivePhi = std::max(0.0f, cosPhi);
      color specular = ks * specColor * std::pow(positivePhi, shininess); //ks*specColor * cosPhi * shininess; creates a bright object
      //final color               
      attenuation = ambient + diffuse + specular;
      return false;
  }

public:
  glm::color diffuseColor;
  glm::color specColor;
  glm::color ambientColor;
  glm::point3 lightPos;
  glm::point3 viewPos; 
  float kd; 
  float ks;
  float ka; 
  float shininess;
};

class metal : public material {
public:
   metal(const glm::color& a, float f) : albedo(a), fuzz(glm::clamp(f,0.0f,1.0f)) {}

   virtual bool scatter(const ray& r_in, const hit_record& rec, 
      glm::color& attenuation, ray& scattered) const override 
   {
      using namespace glm;
      vec3 unitn = normalize(rec.normal);
      vec3 rayn = normalize(r_in.direction());
      vec3 reflected = rayn - 2 * dot(rayn, unitn) * unitn;
      scattered = ray(rec.p, reflected + fuzz * random_unit_sphere());
      attenuation = albedo;
      return true;
   }

public:
   glm::color albedo;
   float fuzz;
};

class dielectric : public material {
public:
  dielectric(float index_of_refraction) : ir(index_of_refraction) {}

  virtual bool scatter(const ray& r_in, const hit_record& rec, 
     glm::color& attenuation, ray& scattered) const override 
   {
      using namespace glm;
      float refrationRatio = rec.front_face ? (1.0f / ir) : ir;
      //normals
      vec3 unitn = normalize(rec.normal);
      vec3 rayn = normalize(r_in.direction()); //ray in mornalized
      //thetha
      float cosTheta = fmin(dot(-rayn, unitn), 1.0f); 
      float sinTheta = sqrt(1 - cosTheta*cosTheta);
      float reflectanceMat = reflectance(cosTheta, refrationRatio);
      vec3 direction;
      if(refrationRatio * sinTheta > 1.0f || reflectanceMat > random_float())
      {
         vec3 rayn = normalize(r_in.direction());
         direction = rayn - 2 * dot(rayn, unitn) * unitn;
      }
      else
      {
         vec3 rPer = refrationRatio * (rayn + cosTheta * unitn); //perpidicular component
         //perpendicular component of refracted ray
         float rPerSquare = dot(rPer, rPer); 
         //parallel component of refracted ray
         vec3 rPar = -std::sqrt(1 - rPerSquare) * unitn;
         direction = rPar + rPer;
      }
      scattered = ray(rec.p, direction);
      attenuation = glm::color(1.0f);
      return true;
   }

public:
  float ir; // Index of Refraction
private:
   static float reflectance(float cosine, float ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
   }

};


#endif

