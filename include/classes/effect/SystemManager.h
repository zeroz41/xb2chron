#ifndef CLASSES_EFFECT_SYSTEMMANAGER_H
#define CLASSES_EFFECT_SYSTEMMANAGER_H

#include "mm/mtl/FixedVector.h"
#include "ptlib/forcefield/FfManager.h"

namespace mtl { class ALLOC_HANDLE; }
namespace ptlib { class DrDrawWorkInfoEF; }

namespace effect {
class SendParam;
class IEffectCallBack;

// table 0x7100B80770
class SystemManager {
public:
    // one queued request of the es_ functions, run by es_command_core (the field names are not the original's)
    struct Command {
        unsigned int m_type;
        unsigned char pad_4[0xC];
        unsigned int m_handle;
        unsigned char pad_14[0xDC];
    } __attribute__((aligned(16)));
    struct KizunaWork;

    SystemManager()
        : m_enableUpdate(true), m_enableAlphaRender(true), m_dispEmitterList(false), m_flagC(true), m_clearAllFlag(false),
          m_destroyFlag(false), m_testRenderFlagA(false), m_testRenderFlagB(false), m_writeSide(0), m_secondBuffer(false),
          m_clearAllCount(0) {}
    virtual ~SystemManager();  // slot 0

    static SystemManager* get();
    static SystemManager*& getPtr();  // the system's manager, null while there is none
    static bool isValid();
    static void testUpdate(float delta);
    static void testRender(const ptlib::DrDrawWorkInfoEF* info);
    static SystemManager* create(const ptlib::DrDrawWorkInfoEF* info);
    static void destroy();
    static void setUserFuncClear();
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
    void updateCam(const ptlib::DrDrawWorkInfoEF* info);
    void MainLoop(const ptlib::DrDrawWorkInfoEF* info);
    void es_command_core();
    // registers effect resource `data` (`size` bytes); null when it cannot
    void* es_regist(void* data, unsigned int size);
    void es_free(void* handle);
    void es_pause(bool pause);
    // an effect from an effect resource (efb), its handle
    unsigned int es_create(void* efb, bool flag);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fw::EffectManager::fn_7100179D30
    // calls it on getPtr()'s manager and its code sits in effect_update_manager's unit. What it does: hands the flag on to
    // ptlib::ParticleManager::get()'s manager; GfMapManager (through fw::EffectManager::fn_7100179D30) passes false before
    // building a map's data, true before destroying it.
    void fn_710083FF24(bool flag);
    // the instance handle's effect fades out over `frames` (fw::EffectManager::kill passes 1, remove -1, dead 0)
    void es_fade_core(void* instance, unsigned int handle, int frames);
    void es_set_disp(unsigned int handle, int disp);
    void es_set_alpha(unsigned int handle, float alpha);
    void es_set_speed(unsigned int handle, float speed);
    void es_set_category(unsigned int handle, unsigned int category);
    void es_set_viewnum(unsigned int handle, int viewnum);
    void es_set_param_pos_only(unsigned int handle, const SendParam* param);
    void es_set_param_pos_only2(unsigned int handle, const SendParam* param);
    void es_set_param(unsigned int handle, const SendParam* param);
    int es_isalive(unsigned int handle);  // above 0 while the handle's effect lives
    int es_getDeadFlag(unsigned int handle);  // -1 for an unknown handle
    bool es_is_loop(void* data) const;
    bool es_contais_cam_axis(void* data);
    void es_clearall(bool flag);
    void setGlobalSpeed(float speed);
    void setCategorySpd(unsigned int category, float speed);
    void begin();
    void end();
    void apply(const ptlib::DrDrawWorkInfoEF* info);
    void opacityRender(const ptlib::DrDrawWorkInfoEF* info);
    void alphaRender(const ptlib::DrDrawWorkInfoEF* info);
    void lastRender(const ptlib::DrDrawWorkInfoEF* info);
    void finalRender(const ptlib::DrDrawWorkInfoEF* info);
    void blurRender(const ptlib::DrDrawWorkInfoEF* info);
    void tail(bool flag);
    void moveMain();
    void getNum(unsigned int& a, unsigned int& b, unsigned int& c);

    // the field names are not the original's
    unsigned char pad_8[0x1];
    bool m_enableUpdate;       // apply runs MainLoop while set
    bool m_enableAlphaRender;  // alphaRender draws while set
    bool m_dispEmitterList;    // testUpdate prints the emitter list (DISP_EMITTER_LIST_START) while set
    bool m_flagC;              // create sets it; nothing in 3.0.1 reads it
    unsigned char pad_d[0x3];
    mm::mtl::FixedVector<ptlib::AddForceParam, 8> m_addForces;  // tail hands them to the force-field manager
    unsigned char pad_218[0x8];
    // the es_ functions queue their requests on side m_writeSide; es_command_core runs them
    mm::mtl::FixedVector<Command, 1152> m_commands[2];
    float m_globalSpeed[2];  // setGlobalSpeed writes the side m_writeSide is not
    bool m_clearAllFlag;     // es_clearall's flag, for emitter_set_free_all
    bool m_destroyFlag;      // destroy clears it before the destructor; nothing in 3.0.1 reads it
    bool m_testRenderFlagA;  // testRender tests it
    bool m_testRenderFlagB;  // testRender tests it
    unsigned char m_writeSide;
    // the stream renderers lock and unlock the second half of their double buffer while set
    // a byte, not a bool: the readers compare it with 0 (cmp, cset), which a bool load would not need
    unsigned char m_secondBuffer;
    unsigned char m_frameCount;     // MainLoop counts the main view's frames
    unsigned char m_clearAllCount;  // es_clearall starts it, tail counts it up, MainLoop clears everything at 3
};
}  // namespace effect

#endif
