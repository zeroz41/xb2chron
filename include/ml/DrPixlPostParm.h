#ifndef ML_DRPIXLPOSTPARM_H
#define ML_DRPIXLPOSTPARM_H

namespace ml {
// a view's post-process parameters (DrMan::DrMan makes four, 0x1110 bytes each). Its setters write a block per
// DrMan::s_nDblIdx; ScnRenderDrSysParmAcc's getters read the fields below. The field names are not the original's:
// each is named after the ScnRenderDrSysParmAcc accessor that reads or writes it.
class DrPixlPostParm {
public:
    void resetScene();
    void setWeatherFrame(float frame);
    void setOverrideToneMap(float value);
    void setOverrideMotBlur(bool enable);
    void setOverrideDOF(bool enable);
    void setDOF(bool enable);
    void setDOFHlv(bool enable);
    void setDOFAutoFocus(bool enable);
    void setDoFPixlRatio(float ratio);
    void setDoFDistance(float distance);
    void setDoFRange(float range);
    void setDoFStrength(float strength);
    void setDoFLens(float lens);
    void setDoFBlend(float blend);
    void setDoFPixlLv(int level);
    void setDoFocusNum(int num);
    void setDofFocusMin(float min);
    void setOverrideColorFilter(bool enable);
    void setColorFilterNum(int num);
    void setColorFilterFrm(float frame);
    void setColorFilterFarNum(int num);
    void setGlassBrk(bool enable, unsigned int arg);

    bool m_toneMap;
    unsigned char pad_1[0x1C9];
    bool m_motBlur;
    unsigned char pad_1CB[0x4D];
    bool m_dofOverride;  // isDOF: either of these two
    bool m_dof;
    bool m_dofHLvMode;
    unsigned char pad_21B[0x1];
    bool m_dofAutoFocus;
    unsigned char pad_21D[0x3];
    float m_dofPixlRatio;
    float m_dofDistance;
    float m_dofRange;
    float m_dofStrength;
    float m_dofLens;
    float m_dofBlend;
    int m_dofPixlLv;
    int m_dofFocusNum;
    unsigned char pad_240[0x4];
    float m_dofFocusMin;
    unsigned char pad_248[0x7C];
    // 0x2C4-0x2D0: DrMdoMat::matCall_OutLineVal's outline width and fade distances (names inferred)
    float m_outLineScale;
    unsigned char pad_2C8[0x4];
    float m_outLineFar;
    float m_outLineNear;
    unsigned char pad_2D4[0xE4];
    bool m_rainDrop;
    unsigned char pad_3B9[0x117];
    bool m_glassBr;
    unsigned char pad_4D1[0xBB3];
    int m_weather;
    unsigned char pad_1088[0x88];
};
}  // namespace ml

#endif
