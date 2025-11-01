# ZeRay Tracer
This is a CPU ray tracer based on [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
The main program renders a simple scene with spheres.
## Alterations 
There were various things that I did differently than the textbook or most people.
### Chapter Source
Chapters are split into the `src/chapters` directory, with the `src/Main.cpp` representing the rerouter.
Each chapter is a `ChapterX.cpp` file.
The purpose of laying out the project this way is so progress is not lost or overwritten. This, I think, is beneficial
because I leave an abundance of comments demonstrating my thought process and challenges.
Not only is the code for each chapter visible, it is also possible to build them seperately (see `Building` section). 
Utility classes like `vec3` and the like are visible from the `src/core` directory. Their use is conditional to the chapter.
### Visible Renders
Final renders from each chapter are also visible in the `renders` directory with `chapter__x.ppm` naming convention. 
Though, they are still in the original PPM format.
### Coordinate System
The book advises the use of X (right), Y (up), and Z (forward). Not only does this seem not aligned with a Right Hand Coordinate System (RHCS)
despite the textbook saying so (it seems more like left handed), it is also not the coordinate system I am familiar with. Given UE5/UEFN I am used to 
the left handed coordinate system with X forward, Y right, and Z up. I thought for fun I would change it.


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
Though, as it stands currently this does nothing