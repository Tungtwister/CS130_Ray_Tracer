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
    
    //calulating ambient
    colorA = this->world_input.ambient_color * this->world_input.ambient_intensity * this->color_ambient;
    
    color = colorA + colorD + colorS;
    return color;
}
