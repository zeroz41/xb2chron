#ifndef GF_GFOBJUTIL_H
#define GF_GFOBJUTIL_H

#include "mm/mtl/FixedVector.h"

namespace fw { class Transform; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_MOUNT_HANDLE; }
#include "gf/GFATTACH.h"
namespace gf { class GfAppendHandles; }
namespace gf { class GfComProperty; }
namespace gf { class GfObjProperty; }
namespace gf { class GfObj; }
namespace gf { class GFOBJ_INFO; }
namespace gf { class GfObjSetup; }
namespace gf { class GfAppend; }
namespace gf { class GfAppendInfo; }
namespace gf { enum OPTMNT : int; }
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfComModel; }
namespace gf { class GfVolumeFade; }

namespace gf {

// a fade an animation annotation describes ("fadein_<frames>" or "fadeout_<frames>[_<numbers>]"), as
// GfObjUtil::parseFadeParam reads it (the field names are not the original's)
struct GfFadeInfo {
    int m_type;              // 1 "fadeout", 0 "fadein"
    unsigned int m_frames;   // the fade's length in frames
    mm::mtl::FixedVector<int, 6> m_values;  // the numbers after the length
};

// helpers for the objects behind handles (functions, by its symbols)
class GfObjUtil {
public:
    static bool isTrinityBlade(gf::GF_OBJ_HANDLE* handle);
    // an info's flag bits (GfObjAcc's setFlag / testFlag forward to them)
    static bool setFlag(gf::GFOBJ_INFO* info, unsigned int flag, bool on);  // whether it changed
    static bool testFlag(const gf::GFOBJ_INFO* info, unsigned int flag);
    // the object this one is attached to, none without one
    static gf::GfObj* getParentObj(gf::GfObj* obj);
    // SCOM_OBJ_WARP_POS and SCOM_OBJ_VFADE_OFF pass their request's object
    static void setWarpTransform(GF_OBJ_HANDLE* handle, const fw::Transform& transform, bool);
    static void setVolumeFadeUserFlag(GF_OBJ_HANDLE* handle, bool);
    static unsigned int getPartyID(GF_OBJ_HANDLE*);
    // the object behind a handle, none for an invalid handle or one with no object
    static gf::GfObj* getObj(gf::GF_OBJ_HANDLE* handle);
    static void setEnableEyeBlink(gf::GF_OBJ_HANDLE* handle, bool enable);
    // sets obj's m_execUpdate: whether its components are to be updated
    static void applyExecUpdate(gf::GfObj* obj);
    static bool isValid(gf::GF_OBJ_HANDLE* handle);
    // what the object behind handle has mounted at a point (its info's mount's), -1 without
    static gf::GF_MOUNT_HANDLE* getMountHandle(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    // the objects appended to an object's mount point 1 (GfMountManager::getAppendHandles)
    static gf::GfAppendHandles* getExtraMountObject(gf::GF_OBJ_HANDLE* handle);
    static void destroy(gf::GF_OBJ_HANDLE* handle);
    // attaches the object behind child to the one behind parent, and detaches it again
    static void attachGfObj(gf::GF_OBJ_HANDLE* parent, gf::GF_OBJ_HANDLE* child);
    static void dettachGfObject(gf::GF_OBJ_HANDLE* parent, gf::GF_OBJ_HANDLE* child);
    // the kind of the object behind a handle (its info's setup's), 0 without one; 5 is what isActiveRangeLure lures
    static int getObjType(gf::GF_OBJ_HANDLE* handle);
    // whether an enemy object is a blade (DataParamAcc::setupObjHandle then makes a DataObjEnemyBlade)
    static bool isEnemyBlade(gf::GF_OBJ_HANDLE* handle);
    // whether the object is in battle (GfGameTarget::setTargetNearestEnemyBattle takes only those)
    static bool isBattle(gf::GF_OBJ_HANDLE* handle);
    // the property of the object behind a handle (its object info's, GfObjManager::createGfObjProperty's), none
    // without an info
    static gf::GfObjProperty* getProperty(gf::GF_OBJ_HANDLE* handle);
    static bool isTalking(gf::GF_OBJ_HANDLE* handle);
    // the setup of the object behind a handle (its object info's), none without an info
    static gf::GfObjSetup* getObjSetup(gf::GF_OBJ_HANDLE* handle);
    static unsigned int getHp(gf::GF_OBJ_HANDLE* handle);  // the object's current HP (DataObjEnemy::getHp)
    // whether the object plays the DLC versions of its sounds (WaterInPlugin::onEvent prefixes their names with
    // "dlc_"): a blade-type object (DataParamAcc's type 3) whose bdat id GfDataBlade's fn_710023F9A8 accepts.
    // The name is not the original's (the symbols call it fn_7100552DF4).
    static bool isDlcSound(gf::GF_OBJ_HANDLE* handle);
    // the object's motion resource name (its data's), none without one
    static const char* getMotionResourceName(gf::GF_OBJ_HANDLE* handle);
    // reads a fade annotation's text into info: false when it is not one
    static bool parseFadeParam(const char* text, gf::GfFadeInfo* info);
    static void unmountFromBone(gf::GF_OBJ_HANDLE* handle);
    static void mountToBone(gf::GF_OBJ_HANDLE* handle, gf::GF_OBJ_HANDLE* parent, const char* bone);
    // the append at an object's point (its mount's current one), none without
    static gf::GfAppend* getAppend(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    static gf::GfAppendInfo* getAppendInfo(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    static void setOwner(gf::GF_OBJ_HANDLE* handle, gf::GF_OBJ_HANDLE* owner);
    static gf::GF_OBJ_HANDLE* getParentHandle(gf::GF_OBJ_HANDLE* handle);
    static bool isUpdate(gf::GF_OBJ_HANDLE* handle);
    // the layer bit of the object behind a handle (its m_updateBit), 4 without one
    static unsigned int getObjLayer(gf::GF_OBJ_HANDLE* handle);
    // the scale the object's setup gives it (x), 1 without a setup
    static float getSetupScale(gf::GF_OBJ_HANDLE* handle);
    static gf::GF_ASSET_HANDLE* getAssetHandle(gf::GF_OBJ_HANDLE* handle);
    // the first layer of the section of three a layer is in (0; 1-3, 4-6, 7-9, 10-12), 4 for any other
    static unsigned int getLayerSection(unsigned int layer);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits between
    // GfObjUtil's getExtraMountObject and fn_710054FCDC, takes a handle and reads its GfObjManager info like
    // the getters around it. What it does: returns the info's m_subHandle (+0x88), -1 without an info.
    static gf::GF_OBJ_HANDLE* fn_710054FCB4(gf::GF_OBJ_HANDLE* handle);
    static bool isLoading(gf::GF_OBJ_HANDLE* handle);
    static gf::GF_OBJ_HANDLE* getOwner(gf::GF_OBJ_HANDLE* handle);
    // whether the object's asset has a state machine resource (its extend resource 0's, a GfExtendPacking)
    static bool isExistAsm(gf::GF_OBJ_HANDLE* handle);
    // has the object rebuilt: destroyed outright when it carries user data 0, else flagged (6) and queued
    static void rebuild(gf::GF_OBJ_HANDLE* handle);
    static const char* getResourceName(gf::GF_OBJ_HANDLE* handle);  // the object's model resource name
    static void setLimitHP(gf::GF_OBJ_HANDLE* handle, unsigned int hp);
    static void setInvincible(gf::GF_OBJ_HANDLE* handle, bool on, bool);
    static void setDisableAutoHeal(gf::GF_OBJ_HANDLE* handle, bool on);
    static bool setFlag(gf::GF_OBJ_HANDLE* handle, unsigned int flag, bool on);  // whether it changed
    static bool testFlag(gf::GF_OBJ_HANDLE* handle, unsigned int flag);
    static const char* getModelBaseName(gf::GF_OBJ_HANDLE* handle);
    static const char* getAssetMotionName(gf::GF_OBJ_HANDLE* handle);
    // whether an object it follows is not ready yet (applyExecUpdate keeps its components still meanwhile)
    static bool isFollowObjNotReady(gf::GF_OBJ_HANDLE* handle);
    static gf::GfComModel* getComModel(gf::GF_OBJ_HANDLE* handle);  // the object's model component (slot 1)
    static gf::GfVolumeFade* getVolumeFade(gf::GF_OBJ_HANDLE* handle);
    static bool isVolumeFadeForUser(gf::GF_OBJ_HANDLE* handle);  // its info's flag 20
    static void setTalking(gf::GF_OBJ_HANDLE* handle, bool on);  // its info's flag 21
    // the sound category of the object's sounds: 3 for create types 6, 7 and 12, else 13 (14 without slow)
    static unsigned int getSoundCategoryNormal(gf::GF_OBJ_HANDLE* handle);
    static unsigned int getSoundCategoryWithoutSlow(gf::GF_OBJ_HANDLE* handle);
    // gives dst's setup src's world transform as its initial one
    static void copyTransformToSetup(gf::GF_OBJ_HANDLE* src, gf::GF_OBJ_HANDLE* dst);
};

}  // namespace gf

#endif
