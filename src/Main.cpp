#include <iostream>

#include "ChapterInterface.h"

int main()
{
	init_chapter();
	return 0;
}

// Notes:
// - At its core: a raytracer sends rays through each pixels, and computes the color seen in the direction of those rays.
// 1. Not a rasterizer. Rasterizer: for each object, if its pixels are closer we keep. Raytracer: for each pixel, the closest intersection we keep. https://youtu.be/ynCxnR1i0QY?si=fFcG4s2VuogPPV56
//		- Will not be going into it (?), but space partitioning: Bounding Volume Hierarcy: O(log N), in a lot of practical situations you only throw the ray against some of the objects, not all of them. (usually bounding boxes)
//		- Rasterization can also take advantage of similar things (frutstum culling, culling in general, etc)
//		- Rasterization is good if you do not really care about non-uniform distributed pixel samples. 
//		- In combination: you use rasterization for the eye-rays, and raytracing for the light sources for glossier effects. (Then you can use alternative anti-aliasing methods).
// 2. Calculate the ray from the “eye” through the pixels. Notice that ray tracers bounce rays from the viewpoint to light sources, not vice versa (this is reverse of real world).
// 3. Determine which objects the ray intersects, and compute a color for the closest intersection point.
// 4. Light and objects are not discrete, they are both continous. With a single ray, we get an image that expects things to be discrete. This pixel model (path tracing?) with a ray in the center leads to aliasing (harsh pixels).
// 5. Anti-aliasing can be done post-process with FXAA and a depth image. Or it can be done with multiple rays and averaging.
// 6. The above "multiple rays" are distributed in different strategies ways. regular assumes constant offsets for each pixel, random is randomized (with different stratgies to pick those random points!).
// 7. 1984: Cook Stochastic (or Distributed Ray Tracing). This is more about shooting off multiple different rays for reflections, than from the eye. It helps you get softer shadows (some reflections hit some don't!) https://www.youtube.com/watch?v=gBPNO6ruevk
// 8. Kajiya-Style Diffuse Interreflection actually has multiple rays through one pixel giving anti-aliasing, but it is "for free" as in its a side-effect or benefit
// 9. "Rendering equation" is an intergral equation that expresses the amount of light leaving a point on a surface (emitted light and reflected light). Every point on surface has this equation, but calculating it for everything is obviously no feasible. 
// 10. Reflection direction: recall linear algebra reflect concepts of two vectors. Refraction: goes through but may have its wave length changed.
// 11. Algorithms that randomize the bounce direction of light generally make materials appear matte