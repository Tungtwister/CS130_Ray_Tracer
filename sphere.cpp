#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    TODO;
    Hit hit;
    std::cout << "sphere shit\n";
    vec3 u = ray.direction;
    vec3 v = ray.endpoint - center;
    
    float a = 1
    float b = 2 * dot(u, v);
    float c = dot(v, v) - (radius * radius);
    
    float discr = pow(b,2) - 4 * a * c;
    
    //finding t using quadratic equation
    float t0 =  (-b + sqrt(discr)) / (2 * a);
	float t1 =  (-b - sqrt(discr)) / (2 * a);
    //there is an intersection
    if(discr > 0)
    {
        if(t0 > small_t)
        {
            hit.object = this;
            hit.dist = t0;
            hit.part = part;
        }
        else
        {
            return {0,0,0};
        }
    }
    //technically one intersection 
    else if(discr == 0)
    {
        return {0,0,0};
    }
    else if(discr < 0)
    {
        return {0,0,0};
    }

}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
