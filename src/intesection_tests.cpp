#include <cassert>
#include "AGLM.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include "box.h"
#include "plane.h"
#include "triangle.h"
#include "hittable.h"

using namespace glm;
using namespace std;

float eps = 0.0001f; // epsilon for comparing floats

template <class T>
bool vecEquals(T a, T b)
{
   return all(epsilonEqual(a, b, eps));
}

template <class T>
bool equals(T a, T b)
{
   return abs<T>(a - b) < eps;
}

void check(bool val, const std::string& message, const hit_record& hit, const ray& ray)
{
   if (!val)
   {
      cout << message << endl;
      cout << hit.str() << endl;
      cout << ray.str() << endl;
   }
   assert(val);
}

void test_sphere(const sphere& s, const ray& r, bool hits, const hit_record& desired) {
   std::cout << "testing sphere" << std::endl;
   hit_record hit;
   bool result = s.hit(r, hit);

   check(result == hits, "error: sphere ray should hit", hit, r);
   if (hits) {
      check(vecEquals(hit.p, desired.p), "error: sphere position incorrect:", hit, r);
      check(vecEquals(hit.normal, desired.normal), "error: sphere normal incorrect:", hit, r);
      check(equals(hit.t, desired.t), "error: sphere hit time incorrect", hit, r);
      check(hit.front_face == desired.front_face, "error: sphere front facing incorrect", hit, r);
   }
}

void test_plane(const plane& p, const ray& r, bool hits, const hit_record& desired) {
   std::cout << "testing planes" << std::endl;
   hit_record hit;
   bool result = p.hit(r, hit);

   check(result == hits, "error: plane ray should hit", hit, r);
   if (hits) {
      check(vecEquals(hit.p, desired.p), "error: plane position incorrect:", hit, r);
      check(vecEquals(hit.normal, desired.normal), "error: plane normal incorrect:", hit, r);
      check(equals(hit.t, desired.t), "error: plane hit time incorrect", hit, r);
      check(hit.front_face == desired.front_face, "error: plane front facing incorrect", hit, r);
   }
}

void test_triangles(const triangle& t, const ray& r, bool hits, const hit_record& desired) {
   std::cout << "testing triangles" << std::endl;
   hit_record hit;
   bool result = t.hit(r, hit);

   check(result == hits, "error: triangle ray should hit", hit, r);
   if (hits) {
      check(vecEquals(hit.p, desired.p), "error: triangle position incorrect:", hit, r);
      check(vecEquals(hit.normal, desired.normal), "error: triangle normal incorrect:", hit, r);
      check(equals(hit.t, desired.t), "error: triangle hit time incorrect", hit, r);
      check(hit.front_face == desired.front_face, "error: triangle front facing incorrect", hit, r);
   }
}

int main(int argc, char** argv)
{
   shared_ptr<material> empty = 0; 
   hit_record none = hit_record{ point3(0), point3(0), -1.0f, false, empty};

   sphere s(point3(0), 2.0f, empty);
   test_sphere(s, 
               ray(point3(0, 0, 3), vec3(0, 0, -1)), // ray outside/towards sphere
               true, 
               hit_record{vec3(0,0,2), vec3(0,0,1), 1, true, empty}); 

   test_sphere(s, 
               ray(point3(0, 0, 0), vec3(0, 0, -1)), // ray inside sphere
               true, 
               hit_record{ vec3(0,0,-2), vec3(0,0,1), 2, false, empty}); 

   test_sphere(s, 
               ray(point3(0, 0, 3), vec3(0, 0, 1)), // ray outside/away sphere
               false, 
               none); 

   test_sphere(s, 
               ray(point3(0, 0, 3), vec3(0, 5,-1)), // ray outside/towards sphere (miss)
               false, 
               none); 

   test_sphere(s, 
               ray(point3(0, 0, 3), vec3(0, 1,-3)), // ray outside/towards sphere (hit)
               true, 
               hit_record{vec3(0,0.3432f, 1.9703f), vec3(0,0.1716f, 0.9851f), 0.3432f, true, empty}); 

   // TODO: Your tests here
   plane p = plane(point3(0,0,0), vec3(0,0,1), empty);

   test_plane(p, ray(point3(0,0,2), vec3(0,0,-1)), 
                     true,                         //ray outside and towards plane. Hits the plane
                     hit_record{vec3(0,0,0), vec3(0,0,1), 2, true, empty}); 

   test_plane(p, ray(point3(1,0,0), vec3(-1,0,0)), 
                     false,                    //ray inside which is a trivial case and I treat is false i.e. not hitting
                     hit_record{vec3(0,0,0), vec3(0,0,1), 1, false, empty});

   test_plane(p, ray(point3(0,0,2), vec3(0,0,1)), 
                     false,                         //ray outside and pointing away from plane. Misses the plane t = infinity here
                     none); 
   
   test_plane(p, ray(point3(0,0,2), vec3(-1,0,0)), 
                     false,                         //ray outside and parallel to the plane. misses the plane
                     none); 
   
   test_plane(p, ray(point3(0,0,0), vec3(0,0,1)), 
                     true,                    //ray inside but direction is outside thus hitting
                     hit_record{vec3(0,0,0), vec3(-0,-0,-1), 0, false, empty});

   triangle t = triangle(point3(-3,-3,0), point3(0,3,0), point3(3, -3, 0), empty);
   triangle t1 = triangle(point3(-3,-3,0), point3(3,-3,0), point3(0, 3, 0), empty);

   test_triangles(t, ray(point3(0,0,2), vec3(0,0,-1)), 
                     true,                         //ray outside and towards triangle. Hits the triangle but outward_normal on other side
                     hit_record{vec3(0,0,0), vec3(-0,-0,1), 2, false, empty}); 
   
   test_triangles(t1, ray(point3(0,0,2), vec3(0,0,-1)), 
                     true,                         //ray outside and towards triangle. Hits the triangle but outward normal on hitting side
                     hit_record{vec3(0,0,0), vec3(-0,-0,1), 2, true, empty}); 

   test_triangles(t1, ray(point3(0,0,0), vec3(0,-1,0)), 
                     false,                         //ray inside the triangle and the direction is in the plane too, we consider this case as not hitting.
                     none); 
   test_triangles(t1, ray(point3(0,0,15), vec3(0,-1,-1)), 
                     false,                         //ray outside and towards triangle but misses
                     none); 
   test_triangles(t1, ray(point3(0,0,15), vec3(0,1,1)), 
                     false,                         //ray outside, away from triangle and misses
                     none); 
   
   test_triangles(t1, ray(point3(0,0,0), vec3(0,0,-1)), 
                     true,                         //ray origin in the triangle but the direction is not in the plane,so we consider this case as  hitting.
                     hit_record{vec3(0,0,0), vec3(-0,-0,1), 0, true, empty}); 


   
}
