

// hittable_list random_scene() {
//     hittable_list world;

//     shared_ptr<material> ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
//     world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

//     for (int a = 0; a < 5; a++) 
//     {
//         for (int b = 0; b < 5; b++) 
//         {
//             float choose_mat = random_float();
//             point3 center(a + 0.9*random_float(), 0.2, b + 0.9*random_float());
//             std::cout << length((center - point3(4, 0.2, 0))) << std::endl;

//             if (length((center - point3(4, 0.2, 0))) > 0.9) {
//                shared_ptr<material> sphere_material;

//                 if (choose_mat < 0.8) {
//                     // diffuse
//                     auto albedo = glm::color(random_float()*random_float());
//                     sphere_material = make_shared<lambertian>(albedo);
//                     world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                 } else if (choose_mat < 0.95) {
//                     // metal
//                     auto albedo = glm::color(random_float()*random_float());
//                     float fuzz = random_float(0, 0.5);
//                     sphere_material = make_shared<metal>(albedo, fuzz);
//                     world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                 } else {
//                     // glass
//                     sphere_material = make_shared<dielectric>(1.5);
//                     world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                 }
//             }
//         }
//     }

//     shared_ptr<material> material1 = make_shared<dielectric>(1.5);
//     world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

//     shared_ptr<material> material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
//     world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

//     shared_ptr<material> material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
//     world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

//     return world;
// }





// //     //  hittable_list scene = random_scene();
    
    
    
// //     shared_ptr<material> ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
// //    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));
   
// //    shared_ptr<material> material1 = make_shared<dielectric>(1.5);
// //    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

// //    shared_ptr<material> material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
// //    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

// //    shared_ptr<material> material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
// //    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

// //    float choose_mat = random_float();
// //    point3 center(0 + 0.9*random_float(), 0.2, 0 + 0.9*random_float());
// //    auto albedo = glm::color(random_float()*random_float());
// //    shared_ptr<material> sphere_material = make_shared<lambertian>(albedo);
// //    world.add(make_shared<sphere>(center, 0.2, sphere_material));

// //    // // shared_ptr<material>  material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
// //    // // shared_ptr<material>  material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
// //    // // shared_ptr<material>  material_left   = make_shared<dielectric>(1.5);
// //    // // shared_ptr<material>  material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

// //    // // world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
// //    // // world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
// //    // // world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
// //    // // world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
// //    // // world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));