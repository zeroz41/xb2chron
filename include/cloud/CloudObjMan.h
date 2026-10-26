#ifndef CLOUD_CLOUDOBJMAN_H
#define CLOUD_CLOUDOBJMAN_H



namespace ml { class IDrDrawWorkInfo; }

namespace cloud {
class CloudObjReduction;
class CloudCalcParams;

// CloudMan's object manager (0x70, no class table: CloudMan's destructor calls its destructor directly). Field
// names are not the original's.
class CloudObjMan {
public:
    CloudObjMan();
    ~CloudObjMan();
    void creataFastSetup();
    bool update(const ml::IDrDrawWorkInfo* info);
    bool isRender() const;
    void alphaRender(const ml::IDrDrawWorkInfo* info);

    unsigned char pad_0[0x38];
    CloudCalcParams* m_pCalcParams;    // 0x38
    CloudObjReduction* m_pReduction;   // 0x40
    unsigned char pad_48[0x11];
    bool m_planeOn;                    // 0x59, CloudMan::planeOn
    bool m_planeSideOn;                // 0x5A, CloudMan::planeSideOn
    unsigned char pad_5B[0x1];
    bool m_skyOn;                      // 0x5C, CloudMan::skyOn
    unsigned char pad_5D[0x4];
    bool m_mdlOn;                      // 0x61, CloudMan::mdlOn
    unsigned char pad_62[0x4];
    bool m_isHole;                     // 0x66, CloudMan::isHole
    unsigned char pad_67[0x9];
};
}  // namespace cloud

#endif
