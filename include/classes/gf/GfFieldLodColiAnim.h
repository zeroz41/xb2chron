#ifndef CLASSES_GF_GFFIELDLODCOLIANIM_H
#define CLASSES_GF_GFFIELDLODCOLIANIM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/ColiUserData.h"

namespace fw { class UpdateInfo; class ColiObject; }
namespace ml { class ScnObjModel; class ScnObjAccPartsPos; }
namespace mm { class Mat44; }
namespace gf { class GfFieldLod; class GF_OBJ_HANDLE; }
namespace idcoli { class IDColiObj; }

namespace gf {
// what a LOD part is doing, by which its effect assets are chosen (GfFieldLodEffect::getAsset takes it; 5 = none).
// The enumerators' names are not the original's: GfFieldLod::setAnimReverse passes 0/1 by its reverse flag,
// GfFieldLod::setFade 2 when shown, else 4 with a fade time, 3 without
enum GfFieldLodState {
    LOD_STATE_ANIM,
    LOD_STATE_ANIM_REVERSE,
    LOD_STATE_POP,
    LOD_STATE_DEPOP,
    LOD_STATE_DEPOP_FADE,
    LOD_STATE_NONE,
};

// a LOD part's effects: one asset per state (a class with no table)
class GfFieldLodEffect {
public:
    GfFieldLodEffect();
    ~GfFieldLodEffect() { disposeAsset(); }
    void* getAsset(GfFieldLodState state) const;
    void createAsset(int bdatId);
    void disposeAsset();
    void createInst(GfFieldLodState state, ml::ScnObjAccPartsPos& pos, bool flag);

    void* m_assets[LOD_STATE_NONE];  // 0x00: by state (the name is not the original's)
    unsigned short m_skipFrame;      // 0x28: BDAT column effect_skipframe (createInst hands it on)
    bool m_hasAsset;                 // 0x2a: createAsset found one (the name is not the original's)
    unsigned int m_handle;           // 0x2c: the playing effect's (EffectManager::remove takes it)
    GfFieldLodState m_state;         // 0x30: the playing effect's state (the name is not the original's)
};
}  // namespace gf

namespace gf {
// a class with no table: the LOD model's animated parts (GfFieldLod's m_coliAnim)
class GfFieldLodColiAnim {
public:
    // what create takes (GfFieldLod::createColiAnim fills it)
    struct CreateInfo {
        CreateInfo() : m_model(nullptr), m_coli(nullptr), m_lod(nullptr), m_flag(false) {}
        ml::ScnObjModel* m_model;  // 0x00
        idcoli::IDColiObj* m_coli;  // 0x08: the ground collision's (GfMapManager::getColiObject()'s m_coliObj)
        const GfFieldLod* m_lod;   // 0x10: the owner
        bool m_flag;               // 0x18: createColiAnim's flag (createPosInfos takes it)
    };
    class ColiUserData;
    class PosInfo;

    GfFieldLodColiAnim(const CreateInfo* info = nullptr);
    ~GfFieldLodColiAnim() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void createPosInfos(bool flag);
    void disposePosInfos();
    void update(fw::UpdateInfo const& info);
    void validateVeSe(GfFieldLod const& lod);
    bool play(unsigned short lodId, bool reverse, bool immediate);
    bool isPlayEnd(unsigned short lodId) const;
    void setPlaySpeed(unsigned short lodId, float speed);
    float getAnimEndTime(unsigned short lodId) const;
    void setFade(unsigned short lodId, bool visible, float time);
    // 1.0.0's symbols name it (3.0.1 inlines it into GfFieldLod::createBdatInfos): a seam part of the model has the id
    bool isLodIdExist(unsigned short lodId) const;

    CreateInfo m_info;                    // 0x00
    mm::mtl::Vector<PosInfo> m_posInfos;  // 0x20
};

// table 0x7100B51ED0
class GfFieldLodColiAnim::ColiUserData : public ::fw::ColiUserData {
public:
    virtual const mm::mtl::RTTI* getRTTI() const;  // slot 0
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_8[8];
};

// an object's user data 1 (GfComBehaviorMapLodAnim updates it each frame); the field names are not the original's
// except where a BDAT column names them
class GfFieldLodColiAnim::PosInfo {
public:
    void update(fw::UpdateInfo const& info);
    void updateAnim(ml::ScnObjAccPartsPos& pos, float frame);
    void updateFade(ml::ScnObjAccPartsPos& pos, float time);
    void updatePopDepopEffect(ml::ScnObjAccPartsPos& pos);
    void syncGfTransform(mm::Mat44 const& mat);

    GfFieldLodColiAnim* m_owner;   // 0x00
    GfFieldLodEffect m_effect;     // 0x08
    unsigned int m_lodId;          // 0x40: the part's id (ScnObjAccPartsPos::getID)
    int m_index;                   // 0x44: the part's index in the model's seam positions (-1: none)
    int m_moveObjIdx;              // 0x48: the collision's move object (IDColiParmsGrand::getMoveObjIdx; -1: none; the name is not the original's)
    unsigned char pad_4c[4];
    GF_OBJ_HANDLE* m_objHandle;    // 0x50: -1 while no object carries it
    ColiUserData m_userData;       // 0x58
    bool m_playing;                // 0x68
    bool m_reverse;                // 0x69
    float m_speed;                 // 0x6c
    bool m_visible;                // 0x70
    float m_fadeTime;              // 0x74
    float m_fadeElapsed;           // 0x78
    float m_popDistSq;             // 0x7c: "effect_pop_dist" squared (50 for looping effects)
    bool m_fadeInColi;             // 0x80: flag LOD_fadeIN_collision
    bool m_fadeOutColi;            // 0x81: flag LOD_fadeOUT_collision
};
}  // namespace gf

#endif
