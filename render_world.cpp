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
    Hit closest_hit;
    Hit orMiss;
    double min_t = 3.40282e+38;
    closest_hit.dist = min_t;

    for(unsigned int i = 0; i < objects.size(); ++i)
    {
        orMiss = objects[i]->Intersection(ray, objects[i]->number_parts);
        if(orMiss.dist < closest_hit.dist && orMiss.dist >= small_t)
        {
            closest_hit = orMiss;
        }
    }
    
    return closest_hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //check to make sure correct
    Ray ray;

    ray.endpoint = camera.position;
    ray.direction = (ray.endpoint - camera.World_Position(pixel_index)).normalized();

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
    vec3 color;
    vec3 intersect_point;
    vec3 normal;
    vec3 temp;
 
    Hit hit;
    hit = Closest_Intersection(ray);
    if(hit.object)
    {
        intersect_point = ray.Point(hit.dist);
        normal = hit.object->Normal(intersect_point, hit.part);
        color = hit.object->material_shader->Shade_Surface(ray, intersect_point, normal, recursion_depth);
    }
    else
    {
        color = this->background_shader->Shade_Surface(ray, temp, temp, recursion_depth);
    }

    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
