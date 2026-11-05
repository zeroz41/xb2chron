#ifndef CLASSES_GF_GFOBJSETUP_H
#define CLASSES_GF_GFOBJSETUP_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "classes/gf/GfInitParam.h"
#include "classes/gf/DataParamAcc.h"
namespace fw { class Transform; }
namespace mm { class Mat44; }
namespace gf {
class GF_OBJ_HANDLE;
class GfInitParamDriver;
class GfInitParamBlade;
class GfInitParamMapSeamless;
class GfInitParamMapLodAnim;
class GfInitParamEnemy;
class GfInitParamNpc;
class GfInitParamMob;
class GfInitParamGimmick;
class GfInitParamFobj;
class GfInitParamWeapon;
class GfInitParamEnWeapon;
class GfInitParamBelonging;
class GfInitParamExtra;
class GfInitParamEventObj;
class GfInitParamUiObj;

// table 0x7100B6A4C8
class GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetup() {}  // slot 1
    virtual unsigned int getFootStep() const;  // slot 3
    virtual unsigned int getFootStepEffect() const;  // slot 4
    virtual unsigned int getEnArrangeID() const { return 0; }  // slot 5
    void setInitialScale(float scale);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamDriver& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamBlade& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamMapSeamless& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamMapLodAnim& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamEnemy& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamNpc& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamMob& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamGimmick& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamFobj& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamWeapon& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamEnWeapon& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamBelonging& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamExtra& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamEventObj& param);
    static GfObjSetup* createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamUiObj& param);
    // takes a matrix's translation and its rotation (euler angles, scale removed) as the object's initial ones
    // (GfFieldLodColiAnim::createPosInfos)
    void setInitialTransform(const mm::Mat44& mtx);
    // takes a transform as the object's initial one (GfObjUtil::copyTransformToSetup)
    void setInitialTransform(const fw::Transform& transform);
    static mm::mtl::RTTI m_rtti;

    // which kind of object the setup makes: 3 a driver, 4 a blade (getFootStep reads the driver's or the blade's
    // data by it; the name is not the original's)
    int m_type;
    int pad_c;
    // the object's bdat row: the data objects' constructors read it (DataObjNpc, DataObjMap, DataObjMob,
    // DataObjGmk; the name is not the original's)
    unsigned int m_bdatId;
    // the id GfGameScene::isRideParty takes for the object (GfGameRide::isRideOnPair passes the leader driver's)
    // (the name is not the original's)
    unsigned int m_partyId;
    unsigned int pad_18;
    // the parameter's m_createType (the constructor copies it)
    int m_createType;
    // the object's initial position: setInitialTransform's (the name is not the original's)
    mm::Vec3 m_initialPos;
    // the parameter's pad_70 (the constructor copies it with the position); setInitialTransform writes the
    // initial rotation's euler angles into it
    mm::Vec3 pad_30;
    // the object's scale: 1.0.0's setInitialScale(float) and setInitialScale(const mm::Vec3&) set it (the name is
    // not the original's)
    mm::Vec3 m_initialScale;
    // the parameter's pad_50; a belonging's createSetupParam sets it to 1.0f or 0.0f (a float)
    float pad_50;
    // the parameter's isAllWeapon() (the constructor stores it; the name is not the original's)
    bool m_isAllWeapon;
    unsigned int pad_58;
    // the parameter's m_gimmickType: for a gimmick its type, DataObjGmk(GF_OBJ_HANDLE*) copies it (the name is
    // not the original's)
    GimmickType m_gimmickType;
    bool pad_60;
    int pad_64;
    int pad_68;

protected:
    // every kind's constructor starts so (inline: no copy of its own in the original)
    GfObjSetup(int type, const GfInitParam& param)
        : m_type(type), pad_c(param.pad_40), m_bdatId(param.m_objId), m_partyId(param.pad_20),
          pad_18(param.pad_24), m_createType(param.m_createType), m_isAllWeapon(param.isAllWeapon()), pad_58(0),
          m_gimmickType(param.m_gimmickType), pad_60(param.pad_81), pad_64(-1), pad_68(-1) {
        if (param.m_hasTransform) {
            m_initialPos = param.m_initialPos;
            pad_30 = param.pad_70;
        } else {
            m_initialPos = mm::Vec3::zero;
            pad_30 = mm::Vec3::zero;
        }
        setInitialScale(param.m_scale);
        pad_50 = param.pad_50;
    }
};

// the create types GfAssetFactory makes event setups for (the name is not the original's; inline in
// gf_obj_factory and in GfQuestTarget's talk icon lookup)
inline bool isEventCreateType(int type) {
    switch (type) {
    case 2:
    case 3:
    case 11:
        return true;
    default:
        return false;
    }
}
}  // namespace gf

#endif
