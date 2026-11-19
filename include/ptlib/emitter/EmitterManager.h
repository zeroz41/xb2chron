#ifndef PTLIB_EMITTER_EMITTERMANAGER_H
#define PTLIB_EMITTER_EMITTERMANAGER_H

#include "ptlib/IntrusiveList.h"
#include "classes/effect/SystemManager.h"
#include "mm/mtl/FixedArray.h"
#include <string.h>

namespace ptlib { class FxHeader; class StaticAllocObj; }
namespace ptlib { namespace math { class KeyFrameIP; } }

namespace ptlib { namespace emitter {
class EmitterArg;
class EmitterParam;
class EmitterObj;
class EmitterSetNode;
class ParticleObj;

// the emitters' manager: its per-category speeds (effect::SystemManager::setCategorySpd)
class EmitterManager {
public:
    // one bond (kizuna) line's points as the emitters read them; SystemManager::updateKizunaPos copies a
    // SystemManager::KizunaWork into it field by field (the field names are not the original's)
    struct KizunaWork {
        KizunaWork() : pad_140(0), pad_151(false), pad_152(true) {
            memset(pad_148, 0xFF, sizeof(pad_148));
            pad_154 = 1.0f;
            pad_158 = 1.0f;
            pad_15c = 1.0f;
            pad_160 = 1.0f;
            m_scrollA = 0.0f;
            m_scrollB = 0.0f;
            pad_16c = 0.3f;
            m_points.assign(mm::Vec3::zero);
        }

        mm::mtl::FixedArray<mm::Vec3, 20> m_points;
        unsigned long pad_140;
        // updateKizunaPos fills [0], [2], [4], [6] from the source's pairs' firsts, then [1], [3], [5], [7], then [8]
        unsigned char pad_148[9];
        bool pad_151;
        bool pad_152;
        float pad_154;
        float pad_158;
        float pad_15c;
        float pad_160;
        float m_scrollA;
        float m_scrollB;
        float pad_16c;
    };

    // init builds the manager in place and empties its lists
    EmitterManager() : pad_1788(nullptr) { clear(); }

    static EmitterManager* get();
    static EmitterManager*& getPtr();
    static void init();
    static void term();
    void init_sub(StaticAllocObj* pAlloc);

    // ParticleManager's emitter_set_* forward to these (what they return is not known yet)
    // frees every emitter and effect file, releases the free emitters' streams and particles and clears the
    // materials (allClear's flag)
    void emitter_set_free_all_sub(bool flag);
    // frees an active emitter: its particles cleared, unlinked and moved to the free list; returns the emitter that
    // followed it
    EmitterObj* emitter_free_core(EmitterObj* pEmitter);
    // the effect file named name (a backslash matches a slash; with id, of that user parameter), or pHeader when
    // it is linked (the last argument is unused)
    FxHeader* emitter_set_search(int id, const char* name, void* pHeader, unsigned int);
    void emitter_set_param_pos_only(unsigned int handle, EmitterParam* pParam);
    void emitter_set_param_pos_only2(unsigned int handle, EmitterParam* pParam);
    void emitter_set_param(unsigned int handle, EmitterParam* pParam);
    void emitter_set_param(FxHeader* pHeader, EmitterParam* pParam);
    // gives the emitters of a handle a model, its scale and up to 15 characters of name (no model: clears both;
    // the int before the scale is unused)
    void emitter_set_casname(unsigned int handle, const void* pModel, const char* name, int, float scale, int mode);
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
    // links a type-1 effect file to the emitters (ParticleManager::parseEfb; what it returns is not known yet)
    void emitter_set_link(FxHeader* pHeader);
    // gives an effect file's nodes back to the free list (what it returns is not known yet)
    void emitter_set_unlink(FxHeader* pHeader);
    // rebuilds the draw chains (m_pDrawTop) from the active emitters that are seen and visible
    void move();
    // empties the emitter lists and the effect files' node lists and resets the draw chains
    void clear();
    // what it returns is not known yet
    void emitter_update(unsigned int handle, float frames, bool flag);
    bool emitter_set_check(FxHeader* pHeader);
    IntrusiveList<EmitterObj>* getEmitterActiveList();
    // takes a particle off the free list and links it into an emitter's particles, first or last
    ParticleObj* particleAlloc(EmitterObj* pEmitter, bool front);
    // allocates a particle for an emitter and places it at the emitter's start (create_local01; nullptr when none
    // is left)
    ParticleObj* createCommon(EmitterObj* pEmitter);
    // a new particle's speed: the emitter's SpeedParam with a random range, keyed by kf when key is set, times the
    // emitter's scale (create_local01)
    void createSpd(EmitterObj* pEmitter, EmitterArg* pArg, math::KeyFrameIP& kf, float frame, ParticleObj* pParticle,
                   bool key);
    // takes a particle off the free list and resets it, nullptr when none is left
    ParticleObj* getFreeParticle();
    // takes an emitter off the free list, nullptr when none is left
    EmitterObj* getEmitterFree();
    // releases an emitter's stream and particles and takes it off the active list
    void removeEmitterActive(EmitterObj* pEmitter);

    // two sets of the bond lines' points: SystemManager::updateKizunaPos writes set m_flip, tail copies it to the
    // other (the name is not the original's)
    mm::mtl::FixedArray<KizunaWork, 8> m_kizunaWorks[2];
    float m_categorySpeed[1];  // indexed by category; the count is not known yet
    unsigned char pad_1704[0x44];
    unsigned long pad_1748;  // clear zeroes it
    // 0x1750: the first emitter of each draw chain, linked through EmitterObj::m_pDrawNext; move rebuilds [0]
    // (emitter types 0, 1, 9, 12), [1] (4, 5) and [2] (2) and clears [3]; clear zeroes all five (the name is not
    // the original's)
    EmitterObj* m_pDrawTop[5];
    unsigned char pad_1778[0x10];
    void* pad_1788;  // clear zeroes it when set
    // ParticleManager::tail flips it between 0 and 1 after moveAfter each frame (the name is not the original's)
    unsigned int m_flip;
    unsigned char pad_1794[0x4];
    unsigned long pad_1798;  // clear zeroes it
    unsigned char pad_17a0[0x8];
    IntrusiveList<EmitterObj> m_emitterActiveList;  // getEmitterActiveList's; the emitter_set_* setters walk it
    // the emitters not in use (getEmitterFree takes them; the name is not the original's)
    IntrusiveList<EmitterObj> m_emitterFreeList;
    // the particles not in use (EmitterObj::remove_particle_free_tbl gives them back; the name is not the original's)
    IntrusiveList<ParticleObj> m_particleFreeList;
    // the emitter sets' nodes (emitter_set_check walks it; the name is not the original's)
    IntrusiveList<EmitterSetNode> m_emitterSetList;
    // the emitter sets' nodes not in use (emitter_set_link takes them; the name is not the original's)
    IntrusiveList<EmitterSetNode> m_emitterSetFreeList;
};
}}  // namespace ptlib::emitter

#endif
