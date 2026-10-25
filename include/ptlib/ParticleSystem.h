#ifndef PTLIB_PARTICLESYSTEM_H
#define PTLIB_PARTICLESYSTEM_H

namespace mtl { class ALLOC_HANDLE; }

namespace ptlib {
class DrDrawWorkInfoEF;

// an effect resource's header, as effect::SystemManager::es_regist hands it out (the names are not the original's:
// es_is_loop and es_contais_cam_axis read the flags)
class FxHeader {
public:
    unsigned char pad_0[0x9];
    unsigned char m_loop;
    unsigned char m_containsCamAxis;
};

// reports a failed check of the effect library with a printf-style message; the expression comes first
void efAstMsg(const char* expression, const char* format, ...);
// prints a printf-style message of the effect library
void efMsg(const char* format, ...);
// prints a printf-style warning of the effect library
void efWng(const char* format, ...);

// the effect library's manager (particle_system.cpp)
class ParticleManager {
public:
    // the library's own memory: size bytes on an align boundary, cited with the requesting file and line
    static void* sysAlloc(unsigned int size, unsigned int align, const char* file, unsigned int line);
    static void sysFree(void* p);

    static ParticleManager* get();
    static ParticleManager*& getPtr();
    static void init(const DrDrawWorkInfoEF* pDrInfo);
    void term();
    void move();
    void setDrInfo(const DrDrawWorkInfoEF* pDrInfo);
    void draw(const DrDrawWorkInfoEF* pDrInfo, int view, bool blur);
    void emitter_set_free(FxHeader* pHeader, int frames);
    void emitter_set_free_all(bool flag);

    // the game's hooks (effect::SystemManager passes them on; setUserFuncClear clears them all)
    static void setUserAllocFunc(void* (*alloc)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                 void (*free)(void*, void*),
                                 void* (*alloc2)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                 void (*free2)(void*, void*), mtl::ALLOC_HANDLE (*handle)(),
                                 mtl::ALLOC_HANDLE (*handle2)());
    static void setUserFileFunc(void* (*load)(const char*, int&), void (*release)(void*));
    static void setUserOutputString(void (*print)(const char*), void (*warn)(const char*));
    static void setUserDrFunc(void* (*a)(const void*, const char*, int, const void*, int), void (*b)(void*),
                              void* (*c)(unsigned int, int), void (*d)(unsigned int, void*), void (*e)(void*, void*),
                              void (*f)(void*, void*), void (*g)(void*, void*), void (*h)(void*, float),
                              void (*i)(void*, void*), void (*j)(unsigned int, void*, void*),
                              void (*k)(unsigned int, void*, void*), void (*l)(unsigned int, void*, void*),
                              void (*m)(void*), void* (*n)(int, int), void (*o)(void*));
};

// the live effects' handles (searchDead is -1 for an unknown handle)
class HashManager {
public:
    static HashManager*& getPtr();
    bool check(unsigned int handle);
    int searchDead(unsigned int handle);
};

}  // namespace ptlib

#endif
