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
    //R is the reflectance, ratio of reflection of incoming light
    //L is the intensities, often as RGB values, "color of the lights"
    //l which is the direction vector from the point on the surface toward each light source,
    //n which is the normal at this point on the surface,
    //r which is the direction that a perfectly reflected ray of light would take from this point on the surface
    //v which is the direction pointing towards the viewer (such as a virtual camera).
    
    //calulating ambient
    // Ia = Ra * La     0 <= Ra <= 1
    vec3 La = world.ambient_color * world.ambient_intensity;
    vec3 Ra = this->color_ambient;
    Ia =  La * Ra;
    
    //variables for diffuse
    vec3 Rd = this->color_diffuse;
    vec3 Ld = {0,0,0};
    vec3 n = normal;
    vec3 l = {0,0,0};
    
    //variables for specular
    vec3 Rs = this->color_specular;
    vec3 Ls = {0,0,0};
    vec3 r = {0,0,0};
    vec3 v = {0,0,0};
    
    
    for(unsigned int i = 0; i < world.lights.size(); i++)
    {
      if(world.enable_shadows)
      {
        Hit hit;
        Ray temp;
            temp.endpoint = intersection_point;
            temp.direction = l.normalized();
            hit = world.Closest_Intersection(temp);
            if(hit.dist < l.magnitude())
            {
	              continue;
            }
      }
    //calculating diffuse
    // Id = Rd * Ld * max(dot(n,l),0)
        Ld = world.lights[i]->Emitted_Light(ray.direction);
        l = world.lights[i]->position - intersection_point;
        Ld = Ld/l.magnitude_squared(); //take into account light decay
        l = l.normalized();
        
        Id += Rd * Ld * std::max(dot(n,l),0.0);
        
    //calculating specular
    // Is = Rs * Ls * max(dot(v,r),0)^alpha
        Ls = Ld; //Ls and Ld are the same thing
        r = (2*dot(n,l)) * n - l; //i love wikipedia
        r = r.normalized();
        v = ray.endpoint - intersection_point;
        v = v.normalized();
        
        Is += Rs * Ls * pow(std::max(dot(v,r),0.0),specular_power);
    }

    //still gotta do shadows
    //pseudo code: 
    //if ( ! shadow ray hits an object )
        //add light’s diffuse and specular components 

    color = Ia + Id + Is;
    return color;
}
