#ifndef ML_DRENVIRONMENTANIM_H
#define ML_DRENVIRONMENTANIM_H

#include "classes/ml/DrFogObjGbl.h"
#include "classes/ml/DrLightObjDir.h"
#include "classes/ml/DrLightObjPnt.h"
#include "classes/ml/DrLightObjSpt.h"

namespace mm { class Vec3; }

namespace ml {
struct EnvFrameRange;
struct LgtObjData;

// One animated attribute: a run of keys in the anim file (field names are not the original's).
struct LgtAnimInf {
    unsigned int m_start;  // first key index
    float m_startFrame;
    float m_endFrame;
    unsigned short pad_c;
    unsigned short m_keyNum;
};

// A Hermite key as getHermiteAttr reads it (the type and field names are not the original's).
struct LgtAnimKey {
    float m_outTangent;
    float m_inTangent;
    float m_value;
    unsigned short m_frame;
    unsigned short pad_e;
};

// Not polymorphic: 1.0.0's constructor stores no table. Field names are not the original's; the
// env* setters (named by the symbols) say which value each one holds.
class DrEnvironmentAnim {
public:
    float getHermiteAttr(const LgtAnimInf*, float);
    // the s_pCallEnvChk callbacks animate a light's position with these
    void calcAnimTransPnt(DrLightObjPnt*, const LgtObjData*, const mm::Vec3&);
    void calcAnimTransSpt(DrLightObjSpt*, const LgtObjData*, const mm::Vec3&);

    void envlgt_amb_color_R(const LgtAnimInf*, float);
    void envlgt_amb_color_G(const LgtAnimInf*, float);
    void envlgt_amb_color_B(const LgtAnimInf*, float);
    void envlgt_amb_color_Intensity(const LgtAnimInf*, float);
    void envlgt_amb_non(const LgtAnimInf*, float);
    void envlgt_dir_color_R(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_color_G(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_color_B(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_color_Intensity(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_spe_Intensity(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_non(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_texonoff(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_texofsX(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_texofsY(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_size(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_rotz(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_roty(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_dir_rotx(DrLightObjDir*, const LgtAnimInf*, float);
    void envlgt_pnt_color_R(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_color_G(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_color_B(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_color_Intensity(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_spe_Intensity(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_non(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_texonoff(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_texofsX(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_texofsY(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_size(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_rotz(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_roty(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_pnt_rotx(DrLightObjPnt*, const LgtAnimInf*, float);
    void envlgt_spt_color_R(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_color_G(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_color_B(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_color_Intensity(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_spe_Intensity(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_angle(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_texonoff(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_texofsX(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_texofsY(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_size(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_rotz(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_roty(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_spt_rotx(DrLightObjSpt*, const LgtAnimInf*, float);
    void envlgt_trans_posx(const LgtAnimInf*, float);
    void envlgt_trans_posy(const LgtAnimInf*, float);
    void envlgt_trans_posz(const LgtAnimInf*, float);
    void envfog_parm_color_R(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_color_G(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_color_B(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_color_sideR(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_color_sideG(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_color_sideB(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_near(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_far(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_str(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_pow(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_color_sunR(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_color_sunG(DrFogObjGbl*, const LgtAnimInf*, float);
    void envfog_parm_color_sunB(DrFogObjGbl*, const LgtAnimInf*, float);

    static void (DrEnvironmentAnim::*s_pCallAmb[13])(const LgtAnimInf*, float);
    static void (DrEnvironmentAnim::*s_pCallDir[13])(DrLightObjDir*, const LgtAnimInf*, float);
    static void (DrEnvironmentAnim::*s_pCallPnt[13])(DrLightObjPnt*, const LgtAnimInf*, float);
    static void (DrEnvironmentAnim::*s_pCallSpt[13])(DrLightObjSpt*, const LgtAnimInf*, float);
    static void (DrEnvironmentAnim::*s_pTransAnim[3])(const LgtAnimInf*, float);
    static void (DrEnvironmentAnim::*s_pFogAnim[13])(DrFogObjGbl*, const LgtAnimInf*, float);

    // DrEnvironmentObj embeds one at 0xE0; DrEnvironmentObjLgt::setFrame clamps the frame to each range's end into
    // m_rangeFrame (the names are not the original's)
    const EnvFrameRange* m_frameRange;  // 0x0
    // 0x8, the attribute runs; callback_Calc_Ambient walks them with s_pCallAmb (name inferred)
    const LgtAnimInf* m_animInf;
    const LgtAnimKey* m_hermiteKeys;  // 0x10, filled by setupAnim
    // 0x18, 0x20: DrEnvironmentObjLgt::changeMemCall points them into the resource's animation section (type and
    // names not known)
    const void* m_animData3;
    const void* m_animData4;
    int m_rangeNum;  // 0x28
    unsigned char pad_2c[0x4];
    float* m_rangeFrame;  // 0x30
    float m_color[3];  // 0x38
    float m_sideColor[3];  // 0x44
    float m_sunColor[3];  // 0x50
    float m_intensity;  // 0x5C
    float m_anmVal[3];  // 0x60, rotation or translation (setupAnmVal in 1.0.0 fills it)
};

}  // namespace ml

#endif
