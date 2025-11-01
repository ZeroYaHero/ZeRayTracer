# CMakeList.txt : CMake project for RayTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("RayTracer")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(CORE_DIR "${SRC_DIR}/core")
set(CORE "${CORE_DIR}/Vec3.cpp" "${CORE_DIR}/Ray.cpp")
add_library(Core STATIC ${CORE})
target_include_directories(Core PUBLIC ${CORE_DIR})

set(CHAPTERS_DIR "${SRC_DIR}/chapters")
file(GLOB CHAPTERS "${CHAPTERS_DIR}/Chapter*.cpp")
set(SOURCES "${SRC_DIR}/Main.cpp" ${CHAPTERS})

# Add source to this project's executable.
add_executable (RayTracer ${SOURCES})
target_include_directories(RayTracer PRIVATE ${CHAPTERS_DIR})
target_link_libraries(RayTracer PRIVATE Core)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
