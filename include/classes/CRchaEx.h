#ifndef CLASSES_CRCHAEX_H
#define CLASSES_CRCHAEX_H

#include "classes/RchaNode.h"
#include "mm/Vec3.h"

// table 0x7100B71E68
// An Rcha node whose setup looks for the anms its getters read by name (the names in the table setup reads); each getter
// returns its anm's value at a frame, or a default when the data has none. The enum and field names are not the
// original's: the enum follows those anm names.
class CRchaEx : public ::RchaNode {
public:
    enum {
        ANM_DMY,  // "dmy"
        ANM_DYNAMICS_BLEND,  // "ptExAnm/DynamicsBlend"
        ANM_WEAPON_DISP,  // "ptExAnm/WeaponDisp"
        ANM_WEAPON_MOUNT,  // "ptExAnm/WeaponMount"
        ANM_WEAPON_BATTLE,  // "ptExAnm/WeaponBattle"
        ANM_WEAPON_SP_MOT,  // "ptExAnm/WeaponSpMot"
        ANM_WEAPON_TRANSLATE_X,  // "ptExAnm/WeaponTranslateX"
        ANM_WEAPON_TRANSLATE_Y,  // "ptExAnm/WeaponTranslateY"
        ANM_WEAPON_TRANSLATE_Z,  // "ptExAnm/WeaponTranslateZ"
        ANM_WEAPON_ROTATE_X,  // "ptExAnm/WeaponRotateX"
        ANM_WEAPON_ROTATE_Y,  // "ptExAnm/WeaponRotateY"
        ANM_WEAPON_ROTATE_Z,  // "ptExAnm/WeaponRotateZ"
        ANM_WEAPON_SCALE,  // "ptExAnm/WeaponScale"
        ANM_FOOT_EFFECT_L,  // "ptExAnm/FootEffectL"
        ANM_FOOT_EFFECT_R,  // "ptExAnm/FootEffectR"
        ANM_AO_ACTIONID,  // "ptExAnm/AO_actionid"
        ANM_AO_FACE_PRISET_TYPE,  // "ptExAnm/AO_facePrisetType"
        ANM_AO_EYE_TYPE,  // "ptExAnm/AO_eyeType"
        ANM_AO_TRANSLATE_X,  // "ptExAnm/AO_translate_x"
        ANM_AO_TRANSLATE_Y,  // "ptExAnm/AO_translate_y"
        ANM_AO_TRANSLATE_Z,  // "ptExAnm/AO_translate_z"
        ANM_AO_ROTATE_X,  // "ptExAnm/AO_rotate_x"
        ANM_AO_ROTATE_Y,  // "ptExAnm/AO_rotate_y"
        ANM_AO_ROTATE_Z,  // "ptExAnm/AO_rotate_z"
        ANM_AO_SCALE,  // "ptExAnm/AO_scale"
        ANM_AOTGT_ENABLE,  // "ptExAnm/AOTGT_enable"
        ANM_AOTGT_TRANSLATE_X,  // "ptExAnm/AOTGT_translate_x"
        ANM_AOTGT_TRANSLATE_Y,  // "ptExAnm/AOTGT_translate_y"
        ANM_AOTGT_TRANSLATE_Z,  // "ptExAnm/AOTGT_translate_z"
        ANM_NUM
    };

    CRchaEx();
    // inline: the table's slot 0 holds RchaNode's complete destructor, which this one became
    virtual ~CRchaEx() {}  // slot 0
    virtual bool setup(mtl::ALLOC_HANDLE handle, void const* data);  // slot 2
    virtual void clear();  // slot 3
    bool getVisible(int& visible, const char* name, float frame) const;
    bool getDynamicsBlend(float& value, float frame) const;
    bool getWeaponDisp(int& value, float frame) const;
    bool getWeaponMount(int& value, float frame) const;
    bool getWeaponBattle(int& value, float frame) const;
    bool getWeaponSpMotion(float frame) const;
    void getWeaponPos(mm::Vec3& vec, float frame) const;
    void getWeaponRot(mm::Vec3& vec, float frame) const;
    void getWeaponScl(float& value, float frame) const;
    bool getFootEffectL(int& value, float frame) const;
    bool getFootEffectR(int& value, float frame) const;
    int getActionType(float frame) const;
    int getFacePrisetType(float frame) const;
    int getEyeType(float frame) const;
    void getObjPos(mm::Vec3& vec, float frame) const;
    void getObjRot(mm::Vec3& vec, float frame) const;
    void getObjScl(float& value, float frame) const;
    bool isTargetEnable(float frame) const;
    void getTarget(mm::Vec3& vec, float frame) const;

    bool m_hasAnm;  // 0x19A0 set by setup whatever it finds (1.0.0's hasAnm returns it)
    int m_anmIndex[ANM_NUM];  // 0x19A4 per name, the index in m_anm of the anm setup found for it, -1 for none
};

#endif
