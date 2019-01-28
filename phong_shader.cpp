#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    TODO; //determine the color
    vec3 Ia = {0,0,0}; //ambient
    vec3 Id = {0,0,0}; //diffuse
    vec3 Is = {0,0,0}; //specular
    //L which is the direction vector from the point on the surface toward each light source ( {\displaystyle m} m specifies the light source),
    //N which is the normal at this point on the surface,
    //R which is the direction that a perfectly reflected ray of light would take from this point on the surface
    //V which is the direction pointing towards the viewer (such as a virtual camera).
    
    //calulating ambient
    // Ia = Ra * La     0 <= Ra <= 1
    vec3 La = world.ambient_color * world.ambient_intensity;
    vec3 Ra = this->color_ambient;
    Ia =  La * Ra;
    
    //calculating diffuse
    // Id = Rd * Ld * max(dot(n,l),0)
    
    // vec3 Rd = this->color_diffuse;
    // vec3 Ld = {0,0,0};
    // vec3 n = normal;
    // vec3 l = {0,0,0};
    // for(unsigned int i = 0; i < world.lights.size(); i++)
    // {
    //     Ld = world.lights[i]->Emitted_Light(ray);
    //     l = world.lights[i].position;
        
    //     Id = Rd * Ld * dot(n,l);
    // }
    
    
    //calculating specular
    // Is = Rs * Ls * max(dot(v,r),0)^alpha
    
    color = Ia + Id + Is;
    return color;
}
