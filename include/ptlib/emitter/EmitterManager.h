#ifndef PTLIB_EMITTER_EMITTERMANAGER_H
#define PTLIB_EMITTER_EMITTERMANAGER_H

#include "ptlib/IntrusiveList.h"

namespace ptlib { class FxHeader; }

namespace ptlib { namespace emitter {
class EmitterParam;
class EmitterObj;
class EmitterSetNode;
class ParticleObj;

// the emitters' manager: its per-category speeds (effect::SystemManager::setCategorySpd)
class EmitterManager {
public:
    static EmitterManager* get();
    static EmitterManager*& getPtr();
    static void init();
    static void term();

    // ParticleManager's emitter_set_* forward to these (what they return is not known yet)
    void emitter_set_free_all_sub(bool flag);
    void emitter_set_search(int a, const char* b, void* c, unsigned int d);
    void emitter_set_param_pos_only(unsigned int handle, EmitterParam* pParam);
    void emitter_set_param_pos_only2(unsigned int handle, EmitterParam* pParam);
    void emitter_set_param(unsigned int handle, EmitterParam* pParam);
    void emitter_set_param(FxHeader* pHeader, EmitterParam* pParam);
    void emitter_set_casname(unsigned int handle, const void* a, const char* b, int c, float d, int e);
    void emitter_set_casparam(unsigned int handle, const void* a, EmitterParam* pParam);
    void emitter_set_disp(unsigned int handle, int disp);
    void emitter_set_alpha(unsigned int handle, float alpha);
    void emitter_set_speed(unsigned int handle, float speed);
    void emitter_set_category(unsigned int handle, unsigned int category);
    void emitter_set_viewnum(unsigned int handle, int view);
    void emitter_set_nowait(unsigned int handle, int nowait);
    void emitter_set_fadeout(unsigned int handle, int frames);
    void emitter_set_fadeout(FxHeader* pHeader, int frames);
    void emitter_set_fadeout(void* p, int frames);
    void emitter_pack_free(unsigned long pack);
    void emitter_set_free(FxHeader* pHeader, int frames);
    void moveAfter();
    // what it returns is not known yet
    void emitter_update(unsigned int handle, float frames, bool flag);
    bool emitter_set_check(FxHeader* pHeader);
    IntrusiveList<EmitterObj>* getEmitterActiveList();
    // takes an emitter off the free list, nullptr when none is left
    EmitterObj* getEmitterFree();
    // releases an emitter's stream and particles and takes it off the active list
    void removeEmitterActive(EmitterObj* pEmitter);

    unsigned char pad_0[0x1700];
    float m_categorySpeed[1];  // indexed by category; the count is not known yet
    unsigned char pad_1704[0xA4];
    IntrusiveList<EmitterObj> m_emitterActiveList;  // getEmitterActiveList's; the emitter_set_* setters walk it
    // the emitters not in use (getEmitterFree takes them; the name is not the original's)
    IntrusiveList<EmitterObj> m_emitterFreeList;
    // the particles not in use (EmitterObj::remove_particle_free_tbl gives them back; the name is not the original's)
    IntrusiveList<ParticleObj> m_particleFreeList;
    // the emitter sets' nodes (emitter_set_check walks it; the name is not the original's)
    IntrusiveList<EmitterSetNode> m_emitterSetList;
};
}}  // namespace ptlib::emitter

#endif
