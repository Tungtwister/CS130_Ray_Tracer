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
    vec3 colorA = {0,0,0}; //ambient
    vec3 colorD = {0,0,0}; //diffuse
    vec3 colorS = {0,0,0}; //specular
    //L which is the direction vector from the point on the surface toward each light source ( {\displaystyle m} m specifies the light source),
    //N which is the normal at this point on the surface,
    //R which is the direction that a perfectly reflected ray of light would take from this point on the surface
    //V which is the direction pointing towards the viewer (such as a virtual camera).
    
    //calulating ambient
    // Ia = Ra * La     0 <= Ra <= 1
    vec3 La = world.ambient_color * world.ambient_intensity;
    vec3 Ra = this->color_ambient;
    colorA =  La * Ra;
    
    color = colorA + colorD + colorS;
    return color;
}
