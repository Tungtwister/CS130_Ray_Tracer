#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    TODO;
    //theres a seg fault here somewhere
    Hit closest_hit;
    Hit orMiss;
    double min_t = 12345;
    closest_hit.dist = min_t;

    for(unsigned int i = 0; i < objects.size(); ++i)
    {
        orMiss = objects[i]->Intersection(ray, -1);
        if((orMiss.dist < closest_hit.dist) && (orMiss.dist >= small_t))
        {
            closest_hit = orMiss;
        }
    }
    std::cout << "pls work\n";
    return closest_hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    TODO;
    //check to make sure correct
    Ray ray;

    ray.endpoint = camera.position;
    ray.direction = (camera.World_Position(pixel_index) - ray.endpoint).normalized();

    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    TODO;
    vec3 color = {0,0,0};
    vec3 intersect_point = {0,0,0};
    vec3 norm = {0,0,0};
    vec3 temp = {0,0,0};
 
    Hit hit = {0,0,0};
    hit = Closest_Intersection(ray);
    std::cout << "well shit\n";
    //if hit exists
    if(hit.object)
    {
        intersect_point = ray.Point(hit.dist);
        std::cout << "inter point works\n";
        //seg faults right here
        norm = hit.object->Normal(intersect_point, -1);
        std::cout << "normal works\n";
        color = hit.object->material_shader->Shade_Surface(ray, intersect_point, norm, recursion_depth);
        std::cout << "shade surface\n";
    }
    else
    {
        color = this->background_shader->Shade_Surface(ray, temp, temp, recursion_depth);
    }
    std::cout << "pls dont reach\n";
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
