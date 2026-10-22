#ifndef GF_GFASSETUTIL_H
#define GF_GFASSETUTIL_H

namespace gf { class GF_ASSET_HANDLE; }

namespace gf {
// helpers on an asset handle's pack; its functions take no object
class GfAssetUtil {
public:
    static void addDestroyObject(GF_ASSET_HANDLE* handle, bool flag);
    static bool isObjectDestroy(GF_ASSET_HANDLE* handle);
    static bool isRetargetLoad(GF_ASSET_HANDLE* handle);
    static void setRetargetLoad(GF_ASSET_HANDLE* handle, bool retargetLoad);
};
}  // namespace gf

#endif
