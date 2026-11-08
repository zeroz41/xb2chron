#ifndef PTLIB_EMITTER_EMITTEROBJ_H
#define PTLIB_EMITTER_EMITTEROBJ_H

#include "ptlib/IntrusiveList.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"
#include "ptlib/math/KeyFrameIP.h"

namespace ml { class DrGpuCheckBase; }
namespace ptlib { class FxHeader; class DrDrawWorkInfoEF; }
namespace ptlib { namespace renderer { class StreamObj; class RenderSet; } }

namespace ptlib { namespace emitter {

class EmitterObj;

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
    unsigned char pad_8[0x8];
    // 0x10: ParticleObj::emitter_create_local_common_grav_wind turns the wind by its rotation rows (the name is not
    // the original's)
    mm::Mat44 m_mtx;
    unsigned char pad_50[0x20];
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
        // 0x10, 0x20, 0x30: ParticleObj::emitter_create_local_common_grav_wind's gravity (a zeroed vector and a speed
        // drawn from the emitter's GravityParam) and wind (the names are not the original's)
        mm::Vec3 m_gravityVec;
        float m_gravity;
        unsigned char pad_24[0xC];
        mm::Vec3 m_wind;
        mm::Vec3 m_noise;  // 0x40: ParticleObj::calcNoise sums its turbulence here (the name is not the original's)
        unsigned char pad_50[0xB8];
        void* m_pLgt;  // 0x108: the light ParticleManager::deleteLgt deletes (the name is not the original's)
        // the particle's model or, with a light, the light's id (the names are not the original's)
        union {
            void* m_pMdl;  // 0x110: the model the DrFunc hooks drive (ParticleManager::update_model_spd)
            unsigned char m_lgtId;
        };
        void* pad_118;
        void* pad_120;
        unsigned char pad_128[0x8];
        // 0x130, 0x140: the particle's two colours ParticleObj::calcExternalColor tints by the emitter's colour (the
        // names are not the original's)
        mm::Vec3 m_color;
        mm::Vec3 m_color2;
        unsigned char pad_150[0x24];
        float m_alpha;  // 0x174: the colours' alpha (the name is not the original's)
        unsigned char pad_178[0x4];
        unsigned int m_rgba;   // 0x17C: m_color and m_alpha as Utility::conv_rgba bytes (the name is not the original's)
        unsigned int m_rgba2;  // 0x180: m_color2's (the name is not the original's)
        unsigned char pad_184[0x30];
        // 0x1B4: the keys ParticleObj::move01_common_keyframe draws its vector with (the name is not the original's)
        math::EPkey m_vecKey;
        unsigned char pad_1c0[0x5A];
        short m_vecKeyIndex;  // 0x21A: EmitterArg::get_kf's key index for m_vecKey (the name is not the original's)
    };
    // deletes the particle's model or light and clears its work
    void particle_clear_union();
    // 0 to 1: how far the particle is into a span's fade-in or out of its fade-out (0 outside begin..end)
    float move_common_check_begin_end_fin_fout(EmitterObj* pEmitter, unsigned short begin, unsigned short end,
                                               unsigned short fadeIn, unsigned short fadeOut, int type);
    void calcNoise(EmitterObj* pEmitter, mm::Vec3& speed);
    void calcIsFit(int isFit, EmitterObj* pEmitter, mm::Vec3& dir);
    void calcExternalColor(mm::Vec3& color, EmitterObj* pEmitter, float& alpha, int setColor, int setColor2);
    // turns pParticle along the line to its neighbour in the list pHead heads and gives its pitch and yaw to pRot
    void move_type1_fit(ParticleObj* pHead, ParticleObj* pParticle, EmitterObj* pEmitter, mm::Vec3NA* pRot);
    // moves the particle along its emitter's key frames at its own frame (what the float and int mean is not known yet)
    void move01_common_keyframe(EmitterObj* pEmitter, float rate, int flag);
    // starts the particle's gravity, wind and noise from its emitter's
    void emitter_create_local_common_grav_wind(EmitterObj* pEmitter);
    void calcSpeedKeyframe(EmitterObj* pEmitter, math::KeyFrameIP& kf, float frame, float emitterFrame);
    void calcParSize(int flag, EmitterObj* pEmitter, math::KeyFrameIP& kf, float frame, float emitterFrame, bool key);
    void calcParRot(math::KeyFrameIP& kf, float frame, EmitterObj* pEmitter, bool key, float rate);
    void move_common_keyframe_uv1_full(EmitterObj* pEmitter, float frame, float rate);
    void calcMatColor(float frame, math::KeyFrameIP& kf, EmitterObj* pEmitter, float emitterFrame, bool key);
    void move01_common_posVec(EmitterObj* pEmitter, int flag);
    void move01_common_keyframe_uv23(EmitterObj* pEmitter, int flag, float rate);
    void move_field_clip(EmitterObj* pEmitter, mm::Vec3& min, mm::Vec3& max);
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
    unsigned char pad_60[0x34];
    // 0x94, 0x98: the particle's pitch and yaw (calcIsFit turns it along a direction; the names are not the original's)
    float m_rotX;
    float m_rotY;
    unsigned char pad_9c[0x4];
    mm::Vec3NA m_keyVec;  // 0xA0: move01_common_keyframe's keyed vector (the name is not the original's)
    unsigned char pad_ac[0xC];
    // 0xB8, 0xBC: their product is the particle's frame for move_common_check_begin_end_fin_fout (the names are not the
    // original's)
    float m_frame;
    float m_frameSpeed;
    unsigned short m_life;  // 0xC0: 0x7FFF lives on (the name is not the original's)
    unsigned char pad_c2;  // createCommon clears it
    // 0xC3: frames before the particle starts moving; the move01_type* loops count it down (the name is not the
    // original's)
    unsigned char m_delay;
    unsigned char pad_c4[0x2C];
    float* m_pVecKf;  // 0xF0: EmitterArg::get_kf's key data for m_keyVec (the name is not the original's)
    unsigned char pad_f8[0x38];
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

// what an emitter was made from (EmitterObj::m_pData: move01_common_keyframe calls EmitterArg::get_kf on it; the size
// is not known yet)
class EmitterArg {
public:
    // reads key-frame data into kf (what the arguments mean is not known yet)
    void get_kf(math::KeyFrameIP* kf, unsigned short count, int type, float frame, short& index, math::EPkey* key,
                float** ppData, float* pTable);

    // 4: the particles carry a model, 5: a light (EmitterManager::particleAlloc; the name is not the original's)
    unsigned char m_type;
    unsigned char pad_1[0x8];
    bool m_fitParent;  // 0x9: ParticleObj::calcIsFit takes the parent particle's rotation (the name is not the original's)
    unsigned char pad_a[0x8A];
    unsigned char m_constParam;  // 0x94: RenderGrObj::draw_common_uconst's fourth constant (the name is not the original's)
    unsigned char pad_95[0x2F];
    // 0xC4: 8 and 9 turn the particles along their motion (ParticleObj::calcIsFit; the name is not the original's)
    unsigned char m_fitType;
    unsigned char pad_c5[0x1B];
    // 0xE0: RenderGrObj::draw_common_uconst's thirteenth constant (the name is not the original's)
    unsigned char m_constParam2;
    unsigned char pad_e1[0x1];
    unsigned short m_vecKfCount;  // 0xE2: move01_common_keyframe's get_kf count (the name is not the original's)
    unsigned char pad_e4[0x19];
    unsigned char m_hashValue;  // 0xFD: HashManager::build records it with the handle (the name is not the original's)
    unsigned char pad_fe[0x6];
    // 0x104: the draw type: 0x9X and 0xD, 4 and 5 pick draw_common_uparam's values (the name is not the original's)
    unsigned char m_drawType;
    unsigned char pad_105[0x3];
    // 0x108: draw_common_uparam's flags: 4 a constant, 0x10 and 0x20 its flag bits (the name is not the original's)
    unsigned char m_drawFlags;
    bool m_externalColor;  // 0x109: ParticleObj::calcExternalColor tints by the emitter (the name is not the original's)
    unsigned char pad_10a[0x12];
    // 0x11C..0x138: draw_common_uconst's and draw_common_uparam's values (the names are not the original's)
    float m_drawDist;    // 0x11C: 1000 when negative or without a draw type
    float m_uconst14;    // 0x120
    float m_uparam9;     // 0x124
    float m_drawDepth;   // 0x128: -3 replaces it while the emitter's m_drawLayer is 0xFF
    float m_uparamScale; // 0x12C
    float m_uparamRate;  // 0x130
    float m_uparam8;     // 0x134: only for draw types 4 and 5
    float m_uparam10;    // 0x138
    unsigned char pad_13c[0x110];
    char m_name[4];  // 0x24C: HashManager::build's entry name; the length is not known yet
};

// an emitter's gravity: a speed and its random range (ParticleObj::emitter_create_local_common_grav_wind; the type
// and field names are not the original's; the size is not known yet)
struct GravityParam {
    unsigned char pad_0[0x14];
    float m_speed;
    float m_speedRange;
};

// an emitter's wind: a direction, turned by the model's rotation unless m_type is 0, 8, 10 or 11, and a strength
// (ParticleObj::emitter_create_local_common_grav_wind; the type and field names are not the original's; the size is
// not known yet)
struct WindParam {
    unsigned char pad_0[0x6];
    unsigned short m_type;
    unsigned char pad_8[0x4];
    mm::Vec3NA m_dir;
    float m_strength;
};

// an emitter's noise: frames, fade frames and the turbulence (ParticleObj::calcNoise; the type and field names are not
// the original's; the size is not known yet)
struct NoiseParam {
    unsigned short m_begin;
    unsigned short m_end;
    unsigned short m_frameType;  // move_common_check_begin_end_fin_fout's type
    unsigned short m_octaves;
    unsigned short m_fadeIn;
    unsigned short m_fadeOut;
    float m_frequency;
    float m_amplitude;
};

// an emitter (particle_emitter.cpp); its links are EmitterManager's active list. The field names are not the
// original's unless a comment says so; the size is not known yet.
class EmitterObj : public IntrusiveListNode {
public:
    void emitter_set_param_sub(EmitterParam* pParam);
    // true while the GPU check sees the emitter (or it has none), else while m_frame is below 60
    bool isRenderCheck() const;
    // the height of the ground below pos (down to height under it; -80 without ground); pAngle gets the ground's
    // slope and direction
    static float check_ground(const mm::Vec3& pos, float height, float* pAngle);
    void move_common_cas_update(EmitterArg* pArg);
    // a random colour from pRange (hue, saturation and value), as red, green and blue
    static void calc_scale_col(mm::Vec3* pOut, math::Vec3r* pRange, float, unsigned int& seed);
    void move01_common_posVec_emitter();
    // the field's bounds for move_field_clip (the parameter names are not the original's)
    void move_field_begin(EmitterArg* pArg, mm::Vec3& min, mm::Vec3& max);
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
    // (ParticleObj::calcIsFit reads it as the particle the emitter is attached to)
    ParticleObj* m_pAttach;
    unsigned int m_attachId;  // 0x88: m_pAttach's m_id when attached (the name is not the original's)
    unsigned char pad_8c[0x4];
    void* m_pGrp;  // ParticleManager::getGrp(m_viewNum) (the name is the original's: "em->m_pGrp")
    EmitterArg* m_pData;  // 0x98 (the name is not the original's)
    unsigned char pad_a0[0x20];
    EmitterCas* m_pCas;
    unsigned char pad_c8[0x8];
    int m_move_type;  // 0xD0: below MOVE_TYPE_MAX; move_func dispatches on it ("m_move_type < MOVE_TYPE_MAX")
    unsigned char pad_d4[0xC];
    mm::Mat44 m_mtx;  // the emitter's placement: EmitterParam::m_mtx
    // 0x120: the colour the particles are tinted by (ParticleObj::calcExternalColor; the names are not the original's)
    float m_colorR;
    float m_colorG;
    float m_colorB;
    float m_alpha;  // emitter_set_alpha's
    unsigned char pad_130[0x1C];
    float m_casScale;  // emitter_set_casname's scale
    unsigned char pad_150[0x1];
    unsigned char m_disp;    // emitter_set_disp's
    unsigned char m_nowait;  // emitter_set_nowait's
    unsigned char pad_153[0x4];
    bool m_drawFlag;  // 0x157: sets draw_common_uparam's flag bit 1 (the name is not the original's)
    float m_speed;  // emitter_set_speed's
    unsigned char pad_15c[0x14];
    unsigned int m_category;  // emitter_set_category's; indexes EmitterManager::m_categorySpeed
    unsigned char pad_174[0xC];
    // 0x180, 0x181: move01_common_keyframe reads both in one halfword (the first's name is not the original's)
    unsigned short m_fadeState : 8;
    unsigned short m_fadeCount : 8;  // calc_fade's numerator
    unsigned char m_fadeFrames;  // calc_fade's denominator
    unsigned char pad_183[0x9];
    float m_frame;  // 0x18C: the emitter's frame (move_common_check_begin_end_fin_fout; the name is not the original's)
    unsigned char pad_190[0x38];
    const GravityParam* m_pGravity;  // 0x1C8 (the name is not the original's)
    unsigned char pad_1d0[0x20];
    const WindParam* m_pWind;  // 0x1F0 (the name is not the original's)
    // 0x1F8: the particles' noise (ParticleObj::calcNoise; the type and name are not the original's)
    const NoiseParam* m_pNoise;
    unsigned char pad_200[0x60];
    unsigned char m_drawLayer;  // 0x260: 0xFF gives the draw constants -3 (the name is not the original's)
    // 0x261: low four bits; 1 makes createCommon link the particle in first (the name is not the original's)
    unsigned char m_allocMode : 4;
    unsigned char pad_262[0x2];
    unsigned int m_handle;  // the handle the emitter_set_* setters look for
    unsigned int m_seed;  // 0x268: the emitter's random seed (the name is not the original's)
    unsigned char m_flags;  // 0x26C: HashManager::build skips the emitter while bit 4 is set (the name is not the original's)
    unsigned char pad_26d[0x7];
    unsigned char m_viewNum;  // emitter_set_viewnum's
    unsigned char pad_275[0x5B];
    float* m_pKfTable;  // 0x2D0: EmitterArg::get_kf's last argument (the name is not the original's)
    unsigned char pad_2d8[0x38];
    // 0x310: emitter_set_param_sub's DrGpuCheckBase::createEffGpuCheckObj (the name is not the original's)
    ml::DrGpuCheckBase* m_pGpuCheck;
};

}}  // namespace ptlib::emitter

#endif
