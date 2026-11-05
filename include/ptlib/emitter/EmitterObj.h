#ifndef PTLIB_EMITTER_EMITTEROBJ_H
#define PTLIB_EMITTER_EMITTEROBJ_H

#include "ptlib/IntrusiveList.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ptlib { class FxHeader; class DrDrawWorkInfoEF; }
namespace ptlib { namespace renderer { class StreamObj; class RenderSet; } }

namespace ptlib { namespace emitter {

// what an emitter is created or updated with. The field names are not the original's; the size is not known yet.
class EmitterParam {
public:
    mm::Mat44 m_mtx;  // EmitterManager::emitter_set_param_pos_only takes it whole, _pos_only2 its translation
    unsigned char pad_40[0x3C];
    // EmitterManager::emitter_set_param(handle, ...) runs the emitter ahead by so many frames, two at a time
    float m_preFrames;
};

// what an emitter follows on a model: EmitterManager::emitter_set_casname/_casparam set it, getEmitterScale reads
// its scale. The type and field names are not the original's; the size is not known yet.
class EmitterCas {
public:
    // 1 unless a model is set
    float getScale() const {
        float scale = m_scale;
        return m_pModel == nullptr ? 1.0f : scale;
    }

    const void* m_pModel;  // emitter_set_casname/_casparam's second argument
    unsigned char pad_8[0x68];
    char m_name[0x10];  // emitter_set_casname's name (at most 15 characters); _casparam empties it
    unsigned char pad_80[0x8];
    float m_scale;
};

// a particle (particle_emitter.cpp); its links are its emitter's particle list or EmitterManager's free list. The size
// is not known yet.
class ParticleObj : public IntrusiveListNode {
public:
    // the particle's work block (the name is not the original's; the size is not known yet)
    // (EmitterManager::particleAlloc's "et->getExtParam().getEmParent()" suggests it is the particle's ext param)
    struct Work {
        unsigned char pad_0[0x8];
        EmitterObj* getEmParent() const { return m_pEmParent; }

        EmitterObj* m_pEmParent;  // 0x8: the emitter the particle belongs to ("getEmParent()")
        unsigned char pad_10[0xF8];
        void* m_pLgt;  // 0x108: the light ParticleManager::deleteLgt deletes (the name is not the original's)
        // the particle's model or, with a light, the light's id (the names are not the original's)
        union {
            void* m_pMdl;  // 0x110: the model the DrFunc hooks drive (ParticleManager::update_model_spd)
            unsigned char m_lgtId;
        };
        void* pad_118;
        void* pad_120;
    };
    // deletes the particle's model or light and clears its work
    void particle_clear_union();
    // the particle's work ("et->getExtParam()")
    Work& getExtParam() { return *m_pWork; }
    // numbers the particle and resets its state (EmitterManager::particleAlloc inlines it; idCounter is its static)
    void initUtilObj() {
        static unsigned int idCounter;
        pad_14c = 0;
        pad_13f = 0;
        m_id = idCounter++;
        if (idCounter > 10000) {
            idCounter = 0;
        }
        pad_145 = 2;
    }

    // EmitterManager::particleAlloc starts the second at the first (the names are not the original's)
    mm::Vec3 m_pos;
    mm::Vec3 m_prevPos;
    mm::Vec3 m_goal;  // 0x30: calc_start2goal01's goal (EmitterManager::createCommon; the name is not the original's)
    mm::Vec3 pad_40;  // createCommon zeroes it
    mm::Vec3 pad_50;  // createCommon zeroes it
    unsigned char pad_60[0x62];
    unsigned char pad_c2;  // createCommon clears it
    unsigned char pad_c3[0x6D];
    Work* m_pWork;  // 0x130
    unsigned int m_id;  // 0x138: initUtilObj's number (the name is not the original's)
    unsigned char pad_13c[0x2];
    bool m_hasMdl;  // 0x13E: update_model_spd sets the speed of m_pWork->m_pMdl only when it is set (the name is not the original's)
    unsigned char pad_13f;  // initUtilObj clears it
    unsigned char pad_140[0x4];
    bool m_hasLgt;  // 0x144: m_pWork holds a light (the name is not the original's)
    unsigned char pad_145;  // initUtilObj sets it to 2
    unsigned char pad_146[0x6];
    unsigned int pad_14c;  // initUtilObj clears it
};

// an emitter (particle_emitter.cpp); its links are EmitterManager's active list. The field names are not the
// original's unless a comment says so; the size is not known yet.
class EmitterObj : public IntrusiveListNode {
public:
    // what the emitter was made from (the name is not the original's; the size is not known yet)
    struct Data {
        // 4: the particles carry a model, 5: a light (EmitterManager::particleAlloc; the name is not the original's)
        unsigned char m_type;
        unsigned char pad_1[0xFC];
        unsigned char m_hashValue;  // 0xFD: HashManager::build records it with the handle (the name is not the original's)
        unsigned char pad_fe[0x14E];
        char m_name[4];  // 0x24C: HashManager::build's entry name; the length is not known yet
    };
    void emitter_set_param_sub(EmitterParam* pParam);
    // the move types' count ("m_move_type < MOVE_TYPE_MAX"; only MOVE_TYPE_MAX's name is the original's)
    enum { MOVE_TYPE_MAX = 7 };
    // moves the emitter's particles by its move type (what the int means is not known yet)
    int move_func(float frame, int flag);
    int move01_type0(float frame, int flag);
    int move01_type1(float frame, int flag);
    void move01_type9(float frame, int flag);
    int move01_type_model(float frame, int flag);
    int move01_type5(float frame, int flag);
    int move01_type12(float frame, int flag);
    // a new particle's start and goal (EmitterManager::createCommon passes the particle's m_pos and m_goal)
    static void calc_start2goal01(EmitterObj* pEmitter, mm::Vec3* pStart, mm::Vec3* pGoal);
    // m_fadeCount out of m_fadeFrames, 1 without a fade
    float calc_fade();
    // EmitterManager's speed of the emitter's category
    float getCateSpd();
    void* lockStream(const DrDrawWorkInfoEF* pDrInfo);
    void unlockStream(const DrDrawWorkInfoEF* pDrInfo, unsigned int count);
    void renderStreamNum(renderer::RenderSet& set, const DrDrawWorkInfoEF* pDrInfo);
    // m_casScale times the model's scale (1 without a model)
    float getEmitterScale();
    void releaseParticleAll();
    // takes a particle off the emitter and gives it back to EmitterManager's free list
    void remove_particle_free_tbl(ParticleObj* pParticle);

    unsigned char pad_10[0x30];
    IntrusiveList<ParticleObj> m_particleList;  // the emitter's particles (the name is not the original's)
    FxHeader* m_pHeader;  // EmitterManager::emitter_set_param(FxHeader*, ...) picks the emitters of a header
    renderer::StreamObj* m_pStream;
    unsigned char pad_68[0x18];
    // what it points at is not known yet; while it is set, the emitter_set_param_pos_only* setters leave m_mtx alone
    void* m_pAttach;
    unsigned char pad_88[0x8];
    void* m_pGrp;  // ParticleManager::getGrp(m_viewNum) (the name is the original's: "em->m_pGrp")
    Data* m_pData;  // 0x98 (the name is not the original's)
    unsigned char pad_a0[0x20];
    EmitterCas* m_pCas;
    unsigned char pad_c8[0x8];
    int m_move_type;  // 0xD0: below MOVE_TYPE_MAX; move_func dispatches on it ("m_move_type < MOVE_TYPE_MAX")
    unsigned char pad_d4[0xC];
    mm::Mat44 m_mtx;  // the emitter's placement: EmitterParam::m_mtx
    unsigned char pad_120[0xC];
    float m_alpha;  // emitter_set_alpha's
    unsigned char pad_130[0x1C];
    float m_casScale;  // emitter_set_casname's scale
    unsigned char pad_150[0x1];
    unsigned char m_disp;    // emitter_set_disp's
    unsigned char m_nowait;  // emitter_set_nowait's
    unsigned char pad_153[0x5];
    float m_speed;  // emitter_set_speed's
    unsigned char pad_15c[0x14];
    unsigned int m_category;  // emitter_set_category's; indexes EmitterManager::m_categorySpeed
    unsigned char pad_174[0xD];
    unsigned char m_fadeCount;   // calc_fade's numerator
    unsigned char m_fadeFrames;  // calc_fade's denominator
    unsigned char pad_183[0xDE];
    // 0x261: low four bits; 1 makes createCommon link the particle in first (the name is not the original's)
    unsigned char m_allocMode : 4;
    unsigned char pad_262[0x2];
    unsigned int m_handle;  // the handle the emitter_set_* setters look for
    unsigned char pad_268[0x4];
    unsigned char m_flags;  // 0x26C: HashManager::build skips the emitter while bit 4 is set (the name is not the original's)
    unsigned char pad_26d[0x7];
    unsigned char m_viewNum;  // emitter_set_viewnum's
};

}}  // namespace ptlib::emitter

#endif
