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
    
    //variable for diffuse
    vec3 Rd = this->color_diffuse;
    vec3 Ld = {0,0,0};
    vec3 n = normal;
    vec3 l = {0,0,0};
    float decay;
    
    //variables for specular
    vec3 Rs = this->color_specular;
    vec3 r = {0,0,0};
    vec3 v = {0,0,0};
    
    
    for(unsigned int i = 0; i < world.lights.size(); i++)
    {
    //calculating diffuse
    // Id = Rd * Ld * max(dot(n,l),0)
        Ld = world.lights[i]->Emitted_Light(ray.direction);
        l = world.lights[i]->position - intersection_point;
        decay = l.magnitude_squared();
        Ld = Ld/decay;
        //n = n.normalized();
        l = l.normalized();
        Id = Rd * Ld * std::max(dot(n,l),0.0);
        
    //calculating specular
    // Is = Rs * Ls * max(dot(v,r),0)^alpha 
        r = l - n * (2*dot(n,l));
        r = r.normalized();
        v = intersection_point - ray.endpoint;
        v = v.normalized();
        
        Is = Rs * Ld * pow(std::max(dot(v,r),0.0),specular_power);
        
    }

    
    
    
    

    
    color = Ia + Id + Is;
    return color;
}
