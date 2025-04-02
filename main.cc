//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"

int main() {
    hittable_list world;

    auto material1 = make_shared<lambertian>(color(0.6, 0.8, 1.0));  
    auto material2 = make_shared<lambertian>(color(0.2, 0.2, 0.2));  
    auto light = make_shared<diffuse_light>(color(15, 15, 15));    

    // Floor
    world.add(make_shared<quad>(point3(-500, 0, -500), vec3(1000, 0, 0), vec3(0, 0, 1000), material2));

    // Cube
    shared_ptr<hittable> box1 = box(point3(-82.5, 0, -82.5), point3(82.5, 165, 82.5), material2);
    box1 = make_shared<rotate_y>(box1, -30);
    box1 = make_shared<translate>(box1, vec3(-15, 0, 0));
    world.add(box1);

    // Light Sources
    world.add(make_shared<quad>(point3(-200, 900, -200), vec3(400, 0, 0), vec3(0, 0, 400), light));

    hittable_list lights;
    lights.add(make_shared<quad>(point3(-200, 900, -200), vec3(400, 0, 0), vec3(0, 0, 400), shared_ptr<material>()));


    camera cam;
    cam.aspect_ratio      = 1.0;
    cam.image_width       = 600;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = color(0.6, 0.8, 1.0); 

    cam.vfov     = 40;
    cam.lookfrom = point3(0, 200, -500);
    cam.lookat   = point3(0, 100, 0);
    cam.vup      = vec3(0, 1, 0);
    cam.defocus_angle = 0;

    cam.render(world, lights);
}
