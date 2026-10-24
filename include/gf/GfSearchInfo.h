#ifndef GF_GFSEARCHINFO_H
#define GF_GFSEARCHINFO_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// an object a search found (GfGameSearchObj::getObj's list holds them). The names are not the original's.
class GfSearchInfo {
public:
    gf::GF_OBJ_HANDLE* m_handle;
    unsigned char pad_8[0x1C];
    float m_height;  // GfGameTarget::setTargetNearest skips one whose magnitude passes its parameter's
    unsigned char pad_28[0x4];
    bool m_visible : 1;  // GfGameTarget::setTargetNearest takes only one with it set (bit 0: it tests the bit)
};

}  // namespace gf

#endif
