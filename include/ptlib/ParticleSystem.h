#ifndef PTLIB_PARTICLESYSTEM_H
#define PTLIB_PARTICLESYSTEM_H

namespace ptlib {

// reports a failed check of the effect library with a printf-style message; the expression comes first
void efAstMsg(const char* expression, const char* format, ...);
// prints a printf-style message of the effect library
void efMsg(const char* format, ...);

// the effect library's manager (particle_system.cpp)
class ParticleManager {
public:
    // the library's own memory: size bytes on an align boundary, cited with the requesting file and line
    static void* sysAlloc(unsigned int size, unsigned int align, const char* file, unsigned int line);
    static void sysFree(void* p);
};

}  // namespace ptlib

#endif
