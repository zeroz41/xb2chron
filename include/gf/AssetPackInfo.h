#ifndef GF_ASSETPACKINFO_H
#define GF_ASSETPACKINFO_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// one loaded asset pack: GfAssetManager keeps them 0x98 apart (getAssetPackInfo)
class AssetPackInfo {
public:
    unsigned char pad_0[0x38];
    GF_OBJ_HANDLE* m_objHandle;  // the object GfAssetUtil::addDestroyObject destroys for the pack
    unsigned char pad_40[0x26];
    bool m_retargetLoad;  // GfAssetUtil::setRetargetLoad sets it, isRetargetLoad reads it
    unsigned char pad_67[0x31];
};
}  // namespace gf

#endif
