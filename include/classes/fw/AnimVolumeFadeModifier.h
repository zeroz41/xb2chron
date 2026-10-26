#ifndef CLASSES_FW_ANIMVOLUMEFADEMODIFIER_H
#define CLASSES_FW_ANIMVOLUMEFADEMODIFIER_H

namespace fw {
// table 0x7100B40B48
class AnimVolumeFadeModifier {
public:
    AnimVolumeFadeModifier();
    virtual ~AnimVolumeFadeModifier();  // slot 0
    virtual void apply();  // slot 2
    unsigned char pad_8[0x18];
    // each gf::VFPARTS's opacity: GfVolumeFade::applyFadeRatio stores 1 - the part's fade ratio (the name is not
    // the original's)
    float m_partsAlpha[6];
    unsigned char pad_38[0x40];  // 0x78 bytes: GfComModel holds one at 0x10c8, its vectors follow at 0x1140
};
}  // namespace fw

#endif
