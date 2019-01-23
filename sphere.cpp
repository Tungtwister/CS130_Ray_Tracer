#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    vec3 u = ray.direction;
    vec3 v = ray.endpoint - center;
    
    float a = 1;
    float b = 2 * dot(u, v);
    float c = dot(v, v) - (radius * radius);
    float disc = pow(b,2) - 4 * a * c; // finding the discriminant
    float t0 =  (-b + sqrt(disc)) / (2 * a); //finding t using quadratic equation
	float t1 =  (-b - sqrt(disc)) / (2 * a);
	if(t0 < small_t) //unsure to compare if t0 < small_t or if t0 < t1
	{
	    std::swap(t0,t1);
	}
	Hit hit = {0,0,0};
    //there is an intersection
    if(disc > 0)
    {
        if(t0 > small_t)
        {
            hit.object = this;
            hit.dist = t0;
            hit.part = part;
            return hit;
        }
        else
        {
            return hit;
        }
    }
    //technically one intersection, but unecessary due to precision errors as said by prof 
    else if(disc == 0)
    {
        return hit;
    }
    else
    {
        return hit;
    }

}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    normal = point - center;
    normal = normal.normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
