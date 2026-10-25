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

    static DrPixlPostParm* s_pIns;  // setInst

    bool m_toneMap;
    unsigned char pad_1[0x43];
    float m_borderBlmMul;  // 0x44
    unsigned char pad_48[0xC9];
    bool m_tmaa;  // 0x111, getTMAAOn
    unsigned char pad_112[0xB8];
    bool m_motBlur;  // 0x1CA
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
    unsigned char pad_248[0x22];
    bool m_colTbl;  // 0x26A, getColTblOn
    unsigned char pad_26B[0x35];
    float m_toonDirLightScale;  // 0x2A0, getToonDirLightScale when DrMan::m_toonDirLightScale is set
    unsigned char pad_2A4[0x20];
    // 0x2C4-0x2D0: DrMdoMat::matCall_OutLineVal's outline width and fade distances (names inferred)
    float m_outLineScale;
    unsigned char pad_2C8[0x4];
    float m_outLineFar;
    float m_outLineNear;
    unsigned char pad_2D4[0xE4];
    bool m_rainDrop;
    unsigned char pad_3B9[0xA7];
    bool m_shwRaytrace;  // 0x460, isShwRaytrace
    unsigned char pad_461[0x6F];
    bool m_glassBr;  // 0x4D0
    unsigned char pad_4D1[0x7];
    float m_glassBrParm[15];  // 0x4D8, setGlassBrk's values (their meanings are not known)
    unsigned char pad_514[0x4];
    stOverrideParm m_override[2];  // 0x518, by DrMan::s_nDblIdx
    unsigned char pad_F58[0x1A];
    bool m_blm2PassExtract;  // 0xF72, isBlm2PassExtract (with m_tmaa)
    unsigned char pad_F73[0x40];
    bool m_reduction;  // 0xFB3, calcReductionBuffer scales by m_reductionScale when set
    unsigned char pad_FB4[0xC];
    float m_reductionScale[2];  // 0xFC0, width, height
    unsigned int m_ofsRenderCheck;  // 0xFC8, calcOfsRenderCheck: x * 100 | y * 100 << 8
    unsigned char pad_FCC[0x58];
    bool m_shwRaytraceTemporal;  // 0x1024, isShwRaytraceTemporalWithOthers (with DrMan::isIBLHalfRes)
    unsigned char pad_1025[0x3C];
    bool m_iblSel;  // 0x1061, DrPixlMan::getSpecIBLObj/getDiffIBLObj pick the second IBL pair when set (name inferred)
    unsigned char pad_1062[0x22];
    int m_weather;  // 0x1084
    float m_weatherFrame[2];  // 0x1088, set by DrMan::s_nDblStockIdx, read by s_nDblIdx; reset to 60
    unsigned char pad_1090[0x75];
    bool m_resetScene[2];  // 0x1105, resetScene sets [DrMan::s_nDblStockIdx]
    unsigned char pad_1107[0x9];
};
}  // namespace ml

#endif
