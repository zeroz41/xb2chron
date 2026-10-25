#ifndef GF_GFDATASOUND_H
#define GF_GFDATASOUND_H

namespace mm { namespace mtl { template <int> class FixStr; }}

namespace gf {
class GfDataSound {
public:
    // "sound/se/<name>.xsp"
    static void getFullPath(mm::mtl::FixStr<128>& path, const char* name);
    static const char* getSeFileByWeaponType(unsigned int type);
};
}  // namespace gf

#endif
