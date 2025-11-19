# ZeRay Tracer
This is a CPU ray tracer based on [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).
The program is not 1:1. [Alterations seen here](#alterations)

## Building
If you would like to generate a VS or other platform project, it is a good idea to run CMake in a seperate directory for an out of source build
```
cmake -B <path-to-build> [-S <path-to-source>]
```
Alternatively,
```
cd path/to/build/directory
cmake path/to/source/directory
```
For building the executable/application,
```
cmake --build <dir> [<options>]
```
For more details, it is just best to follow [CMake's own synopsis](https://cmake.org/cmake/help/latest/manual/cmake.1.html)

With Visual Studio 2022 I was able to create a new CMake project instead of the solution. This automatically runs the target include/links on save and build.
This also comes with `CMakePresetsSettings.json` which I did not include due to it really being platform specific to VS.

I wanted a better way to select chapters via a simple build/link argument in the command line but I am still a newbie. 
Everything was pointing towards a configuration step, which from my understanding makes it so you would have to regenerate the build system.

### Chapter Specific 
For chapter specific builds I opted for a define/preprocessor symbol seen in `src/chapters/ChapterInterface.h`
Simply just replace the define with
```
#define CHAPTER_X
```
where `X` has a corresponding `src/chapters/ChapterX.cpp` file.

## Running
Wherever you built the application, simply just call:
```
RayTracer.exe
```
Though, with how renders get exported in this book, you need to pipe the output to a file. So something like this should do the trick:
```
RayTracing.exe > image.ppm
```


## Alterations 
There were various things that I did differently than the textbook or most people.
Before you take a look, just know that I will not argue these alterations are the best. 
I am beginner and a learner. I find that making decisions like these allows me to learn why you do
something and why you do not. I also think that having changes like these tested me a little more in understanding the concepts 
rather than me just repeating them.
### Chapter Source
Chapters 1-7 are split into the `src/chapters` directory, with the `src/Main.cpp` being the entry point and `src/chapters/ChapterInterface.h` being the "rerouter."
Each chapter is a `ChapterX.cpp` file.
The purpose of laying out the project this way is so progress is not lost or overwritten. This, I think, is beneficial
because I leave an abundance of comments demonstrating my thought process and challenges.
Not only is the code for each chapter visible, it is also possible to build them seperately (see [Building](#building) section). 
Utility classes like `vec3` and the like are visible from the `src/core` directory. Their use is conditional to the chapter. 
### Visible Renders
Final renders from each chapter are also visible in the `renders` directory with `chapter_x.ppm` naming convention. 
Though, they are still in the original PPM format.
### Coordinate System
The book advises the use of X (right), Y (up), and Z (forward). It is not the coordinate system I am familiar with. Given UE5/UEFN I am used to its coordinate system with X forward, Y right, and Z up (FRU). I thought for fun I would change it... 
<!--So I did for Chapters 1-5, but by 6 it started to cause extra complexity.-->
In hindsight, after doing some additional readings like this one here [Learn OpenGL](https://learnopengl.com/Getting-started/Coordinate-Systems) I realized it would have been best to go with a graphical coordinate system like the book.
Though I still perservered anyway.
 
### Not Header Only
The textbook utilizes headers only, which honestly I am not against. It offers simplicity and removes a good bit of redundancy. I can see how it can even be seen as preferable.
Though, I like having headers that make it easy to see the available functions without the actual implementation. Not to mention, it enables you to implement the functions differently if you wanted to.
Using `.cpp` files also prevented some issues with source order. In example, I was able to have the `vec3` class utilize the dot product instead of actually repeating the same operations in it's `length_squared` method.

### Face Normals
The textbook has the hit payload/record keep track of a normal boolean value. This seemed unnecessary and with my implementations only caused issues. Instead, I just used the dot product to determine the normal (as the textbook suggested as alternative).

### Smaller Alterations
Here are some alterations that are based on personal preference, self explanatory, or basic.

- **Units**: A centimeter is the best smallest unit to use in a 3D graphical application, and I will stand by this (just based on vibes).
- **Vector Unary**: There was no negative unary operator overload so I decided to add one for convenience. *Its presence is assumed in Listing 19?*
- **Move Semantics**: Tried to take advantage of moves whenever since there is a decent portion of code that utilizes rvalues.
- **Omission of Common Header**: In the textbook there is a `rtweekend.h` file that contains a lot of the includes used. I am not a fan of this. I like being able to choose specifically which files are included and I find it to be clearer.
- **I Didn't Do It In "One Weekend"**: *TeeHee,* I am a fulltime student. I needed to break it up.

## Additional Notes
- The use of object oriented programming for something like this makes sense, but as I was going through it I could not help but think about how a much more simple a C version of the program would be. The reason why you do not see me doing this textbook in C though is because there is a lot of value in understanding C++ and *it's* primitives.
- The textbooks use of m
