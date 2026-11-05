#ifndef ML_DRPIXLPOSTPARM_H
#define ML_DRPIXLPOSTPARM_H

namespace ml {
// a view's post-process parameters (DrMan::DrMan makes four, 0x1110 bytes each). Its setters write a block per
// DrMan::s_nDblIdx; ScnRenderDrSysParmAcc's getters read the fields below. The field names are not the original's:
// each is named after the ScnRenderDrSysParmAcc accessor that reads or writes it.
class DrPixlPostParm {
public:
    // a block of override settings per DrMan::s_nDblIdx (the setOverride*/setDoF*/setColorFilter* setters write the
    // current one). The type and field names are not the original's: each field is named after its setter.
    struct stOverrideParm {
        bool m_overrideToneMap;  // 0x0
        unsigned char pad_1[0x3];
        float m_toneMap;  // 0x4
        unsigned char pad_8[0x1F8];
        bool m_overrideMotBlur;  // 0x200
        unsigned char pad_201[0x1B];
        bool m_overrideDOF;  // 0x21C
        bool m_dof;
        unsigned char pad_21E[0x1];
        bool m_dofHlv;  // 0x21F
        unsigned char pad_220[0x1];
        bool m_dofAutoFocus;  // 0x221
        unsigned char pad_222[0x2];
        float m_dofPixlRatio;  // 0x224
        float m_dofDistance;
        float m_dofRange;
        float m_dofStrength;
        float m_dofLens;
        float m_dofBlend;
        int m_dofPixlLv;  // 0x23C
        int m_dofFocusNum;
        unsigned char pad_244[0x4];
        float m_dofFocusMin;  // 0x248
        unsigned char pad_24C[0x22];
        bool m_overrideColorFilter;  // 0x26E
        unsigned char pad_26F[0x1];
        int m_colorFilterNum;  // 0x270
        float m_colorFilterFrm;
        unsigned char pad_278[0x4];
        int m_colorFilterFarNum;  // 0x27C
        unsigned char pad_280[0x2A0];
    };

    DrPixlPostParm();
    ~DrPixlPostParm();
    DrPixlPostParm& operator=(const DrPixlPostParm& other);
    void reset();
    void setInst();
    bool isShwRaytrace() const;
    bool isShwRaytraceTemporalWithOthers() const;
    bool getTMAAOn() const;
    bool getToneMapOn() const;
    bool getColTblOn() const;
    float getBorderBlmMul() const;
    bool getRainDropOn() const;
    bool isBlm2PassExtract() const;
    bool getSSRWithTrans() const;
    bool getSSROn() const;
    float getToonDirLightScale() const;
    void calcOfsRenderCheck(float x, float y);
    void calcReductionBuffer(int& width, int& height);
    float getWeatherFrame() const;
    void resetWeatherFrame();
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
    // one rain drop layer's values (the field names are not the original's: m_param3 is the table's fifth row)
    struct stRainDropLayerInfo {
        float m_param0;
        float m_param1;
        float m_param2;
        float m_param3;
        float m_param4;
    };
    void getRanDropLayerInfo(unsigned int layer, stRainDropLayerInfo& info) const;
    float getTMAASharpness(unsigned int type) const;

    static DrPixlPostParm* s_pIns;  // setInst

    bool m_toneMap;
    unsigned char pad_1[0x3B];
    bool m_godRay;  // 0x3C, DrPixlMan::setupGodRay clears the god ray target only when set (name inferred)
    unsigned char pad_3D[0x1];
    // 0x3E, DrPixlPostObjBloom::calculateGaussBlur adds the flare and lens flare only while set (name inferred)
    bool m_lensFlare;
    unsigned char pad_3F[0x5];
    float m_borderBlmMul;  // 0x44
    unsigned char pad_48[0xC9];
    bool m_tmaa;  // 0x111, getTMAAOn
    unsigned char pad_112[0x2];
    // by SHARPNESS_TYPE; getTMAASharpness reads m_tmaaSharpnessAlt while DrMan::m_qualityMode is 0 (names inferred)
    float m_tmaaSharpness[6];  // 0x114
    float m_tmaaSharpnessAlt[6];  // 0x12C
    unsigned char pad_144[0x14];
    // 0x158, DrPixlPostObjTMAA::render restarts the history (its flag 1) and clears it (the name is not the original's)
    bool m_tmaaReset;
    unsigned char pad_159[0x1B];
    bool m_ssao;  // 0x174, DrPixlPostObjTSSAO::render_beforeTemporal runs its passes only while set (name inferred)
    unsigned char pad_175[0x13];
    float m_ssaoBlurAfter;  // 0x188, DrPixlPostObjTSSAO::render_afterTemporal's passBlur_Sub value (name inferred)
    unsigned char pad_18C[0x3E];
    bool m_motBlur;  // 0x1CA
    unsigned char pad_1CB[0x2];
    // 0x1CD: DrPixlPostObjMotionBlur2::render runs calcVelocityBlur while it is set (the name is not the original's)
    bool m_velocityBlur;
    unsigned char pad_1CE[0x1E];
    // 0x1EC, DrPixlPostObjMotionBlur::render runs calcVelocityBlur only while it is above 0 (name inferred)
    float m_velocityBlurRate;
    unsigned char pad_1F0[0xC];
    // 0x1FC: ScnRenderDrSysParmAcc::setMotBlurDefault writes DrIniSys::m_postParm's (the name is not the original's)
    bool m_motBlurDefault;
    unsigned char pad_1FD[0x1B];
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
    unsigned char pad_248[0x21];
    // 0x269, DrPixlPostObjCubeMapMultiIBL::requestIBL refuses requests while it is clear
    // (the name is not the original's)
    bool m_multiIBL;
    bool m_colTbl;  // 0x26A, getColTblOn
    unsigned char pad_26B[0x35];
    float m_toonDirLightScale;  // 0x2A0, getToonDirLightScale when DrMan::m_toonDirLightScale is set
    unsigned char pad_2A4[0x4];
    // 0x2A8: DrIniSys::setupDlcIni sets it from lib_dlc_nx.ini's toonShadowAlphaDLC key, on DrIniSys::m_postParm and
    // DrMan::m_postParm[0] (name inferred from the key)
    float m_toonShadowAlpha;
    unsigned char pad_2AC[0x18];
    // 0x2C4-0x2D0: DrMdoMat::matCall_OutLineVal's outline width and fade distances (names inferred)
    float m_outLineScale;
    unsigned char pad_2C8[0x4];
    float m_outLineFar;
    float m_outLineNear;
    unsigned char pad_2D4[0xE4];
    bool m_rainDrop;
    unsigned char pad_3B9[0x53];
    // 0x40C, five values per rain drop layer (three layers); getRanDropLayerInfo copies one layer (name inferred)
    float m_rainDropLayer[5][3];
    unsigned char pad_448[0x18];
    bool m_shwRaytrace;  // 0x460, isShwRaytrace
    unsigned char pad_461[0x7];
    // DrLightMan::getSkyLuminance weighs its 0x120 colour by the first and its ambient colour by the second (the names
    // are not the original's)
    float m_skyLumColorRate;  // 0x468
    float m_skyLumAmbRate;  // 0x46C
    unsigned char pad_470[0x14];
    float m_illuminanceScale;  // 0x484, DrPixlMan::debugIlluminanceRender passes 1 / it to its shader (name inferred)
    bool m_dbgGBuff;  // 0x488, DrPixlMan::fastDeferredRender calls debugGBuffRender while set (name inferred)
    unsigned char pad_489[0x1];
    bool m_ssr;  // 0x48A, getSSROn (name inferred)
    unsigned char pad_48B[0x45];
    bool m_glassBr;  // 0x4D0
    unsigned char pad_4D1[0x7];
    float m_glassBrParm[15];  // 0x4D8, setGlassBrk's values (their meanings are not known)
    unsigned char pad_514[0x4];
    stOverrideParm m_override[2];  // 0x518, by DrMan::s_nDblIdx
    // 0xF58: DrPixlPostObjBloom::calcRender rebuilds its buffers when it changes, at a quarter scale for 1 and half
    // otherwise (the name is not the original's)
    int m_bloomType;
    unsigned char pad_F5C[0x16];
    bool m_blm2PassExtract;  // 0xF72, isBlm2PassExtract (with m_tmaa)
    unsigned char pad_F73[0x15];
    // 0xF88: DrPixlPostObjSSR::update fades it to 1 over m_ssrFadeTime * 30 frames (the names are not the original's)
    float m_ssrFade;
    float m_ssrFadeTime;  // 0xF8C
    unsigned char pad_F90[0x4];
    float m_ssaoBlur;  // 0xF94, DrPixlPostObjTSSAO::render_beforeTemporal's passBlur_Sub value (name inferred)
    unsigned char pad_F98[0x19];
    bool m_ssaoQuaterNormal;  // 0xFB1, render_beforeTemporal runs passQuaterNormal first while set (name inferred)
    bool m_hdrFilter;  // 0xFB2, DrPixlMan::gammaRender/toneMapRender sample the HDR buffer linearly while set (name inferred)
    bool m_reduction;  // 0xFB3, calcReductionBuffer scales by m_reductionScale when set
    unsigned char pad_FB4[0x4];
    // 0xFB8: DrPixlPostObjBloom::resetColorBuff's buffer scale while m_reduction is set (the names are not the original's)
    float m_bloomReductionScale[2];
    float m_reductionScale[2];  // 0xFC0, width, height
    unsigned int m_ofsRenderCheck;  // 0xFC8, calcOfsRenderCheck: x * 100 | y * 100 << 8
    // 0xFCC: the width and height whose aspect DrPixlPostObjBloom::resetColorBuff keeps when DrMan::m_qualityMode is 0
    // (the name is not the original's)
    float m_bloomAspect[2];
    unsigned char pad_FD4[0x10];
    // 0xFE4, DrShdLgtGlobalIBL::resetColorBuff resets the view's IBL colour buffer only when it is 3 (the name is not
    // the original's)
    int m_iblColorMode;
    unsigned char pad_FE8[0x3C];
    bool m_shwRaytraceTemporal;  // 0x1024, isShwRaytraceTemporalWithOthers (with DrMan::isIBLHalfRes)
    // 0x1025..0x1028: the debug views DrPixlMan::lastRender draws (names inferred): the shadow map
    // (DrPixlShadowMan::shadowRender), the deferred buffers, the shadow caches (only without the shadow map view)
    bool m_dbgShadow;
    unsigned char pad_1026[0x1];
    bool m_dbgDeferred;  // 0x1027
    bool m_dbgShadowCache;  // 0x1028
    unsigned char pad_1029[0x3];
    // 0x102C: DrPixlShadowCacheMan::debugShadowCacheRender draws the work table this selects, from 1 (the name is
    // not the original's)
    float m_dbgShadowCacheLevel;
    unsigned char pad_1030[0xE];
    bool m_shadowAddObjPos;  // 0x103E, DrPixlShadowMan::setAddObjPos forwards only when set (name inferred)
    unsigned char pad_103F[0x22];
    bool m_iblSel;  // 0x1061, DrPixlMan::getSpecIBLObj/getDiffIBLObj pick the second IBL pair when set (name inferred)
    unsigned char pad_1062[0x1A];
    int m_weatherNum;  // 0x107C, DrEnvironmentObjLgt::update passes setWeatherNum whether it changed (name inferred)
    unsigned char pad_1080[0x4];
    int m_weather;  // 0x1084
    float m_weatherFrame[2];  // 0x1088, set by DrMan::s_nDblStockIdx, read by s_nDblIdx; reset to 60
    unsigned char pad_1090[0xC];
    // 0x109C: the wetness value DrIniSys::getWetnessSetting returns without a table row or column 3, read from
    // DrIniSys::m_postParm (the name is not the original's)
    float m_wetDefault;
    unsigned char pad_10A0[0x5C];
    // 0x10FC: DrPixlPostMan::update clears it each frame when set (name inferred)
    unsigned char m_frameReq;
    unsigned char pad_10FD[0x1];
    bool m_dbgReduction;  // 0x10FE, DrPixlMan::lastRender then draws debugReductionRender (name inferred)
    unsigned char pad_10FF[0x5];
    // 0x1104, getSSROn is false while set and DrCalcViewWork::m_gpuCheckAllVisible is (name inferred)
    bool m_ssrGpuCheckOff;
    bool m_resetScene[2];  // 0x1105, resetScene sets [DrMan::s_nDblStockIdx]
    unsigned char pad_1107[0x9];
};
}  // namespace ml

#endif
