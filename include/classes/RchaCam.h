#ifndef CLASSES_RCHACAM_H
#define CLASSES_RCHACAM_H

#include "classes/RchaNode.h"
#include "mm/Vec3.h"

// table 0x7100B71B58
// An Rcha node whose setup looks for the anms its getters read by name (the names in the table setup reads); each getter
// returns its anm's value at a frame, or a default when the data has none. The enum and field names are not the
// original's: the enum follows those anm names.
class RchaCam : public ::RchaNode {
public:
    enum {
        ANM_TRANSLATE_X,  // "cam/translate_x"
        ANM_TRANSLATE_Y,  // "cam/translate_y"
        ANM_TRANSLATE_Z,  // "cam/translate_z"
        ANM_ROTATE_X,  // "cam/rotate_x"
        ANM_ROTATE_Y,  // "cam/rotate_y"
        ANM_ROTATE_Z,  // "cam/rotate_z"
        ANM_ROTATE_ORDER,  // "cam/rotate_order"
        ANM_ATR_TRANSLATE_X,  // "camAtr/translate_x"
        ANM_ATR_TRANSLATE_Y,  // "camAtr/translate_y"
        ANM_ATR_TRANSLATE_Z,  // "camAtr/translate_z"
        ANM_ATR_DOF,  // "camAtr/Dof"
        ANM_ATR_DOF_DISTANCE,  // "camAtr/DofDistance"
        ANM_ATR_DOF_RANGE,  // "camAtr/DofRange"
        ANM_ATR_DOF_PIXEL,  // "camAtr/DofPixel"
        ANM_ATR_DOF_LENS,  // "camAtr/DofLens"
        ANM_ATR_DOF_STRENGTH,  // "camAtr/DofStrength"
        ANM_ATR_DOF_BLEND,  // "camAtr/DofBlend"
        ANM_ATR_DOF_PIXEL_LV,  // "camAtr/DofPixelLv"
        ANM_ATR_DOF_HLV,  // "camAtr/DofHlv"
        ANM_ATR_M_BLUR,  // "camAtr/MBlur"
        ANM_ATR_M_BLUR_STR,  // "camAtr/MBlur_Str"
        ANM_ATR_M_BLUR_SUB,  // "camAtr/MBlur_Sub"
        ANM_ATR_SM_VIS,  // "camAtr/SM_Vis"
        ANM_ATR_CLOCK,  // "camAtr/Clock"
        ANM_ATR_CLOCK_HOUR,  // "camAtr/ClockHour"
        ANM_ATR_WTR,  // "camAtr/Wtr"
        ANM_ATR_WTR_TYPE,  // "camAtr/WtrType"
        ANM_ATR_WTR_FADE,  // "camAtr/WtrFade"
        ANM_ATR_CAM_LGT,  // "camAtr/CamLGT"
        ANM_ATR_NEAR_FAR,  // "camAtr/NearFar"
        ANM_NUM
    };

    RchaCam();
    // inline: the table's slot 0 holds RchaNode's complete destructor, which this one became
    virtual ~RchaCam() {}  // slot 0
    virtual bool setup(mtl::ALLOC_HANDLE handle, void const* data);  // slot 2
    bool getPos(mm::Vec3* vec, float frame) const;
    bool getRot(mm::Vec3* vec, float frame) const;
    int getRotOrder(float frame) const;
    float getFov(float frame) const;
    float getMBlurStr(float frame) const;
    bool isEnableMBlur(float frame) const;
    float getMBlurSub(float frame) const;
    bool isEnableDOF(float frame) const;
    float getDistanceDOF(float frame) const;
    float getRangeDOF(float frame) const;
    float getPixelDOF(float frame) const;
    float getLensDOF(float frame) const;
    float getStrengthDOF(float frame) const;
    float getBlendDOF(float frame) const;
    int getPixelLvDOF(float frame) const;
    bool isHlvDOF(float frame) const;
    bool isSMapVis(float frame) const;
    bool isEnableTime(float frame) const;
    float getTimeVal(float frame) const;
    bool isEnableWeather(float frame) const;
    bool isCamLgtStop(float frame) const;
    int getNearFarType(float frame) const;
    int getWeatherType(float frame) const;
    int getWeatherFrame(float frame) const;

    bool m_hasAnm;  // 0x19A0 set by setup when it finds any of its anms (1.0.0's hasAnm returns it)
    int m_anmIndex[ANM_NUM];  // 0x19A4 per name, the index in m_anm of the anm setup found for it, -1 for none
};

#endif
