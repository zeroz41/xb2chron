#ifndef CLASSES_GF_SCOM_OBJ_VFADE_H
#define CLASSES_GF_SCOM_OBJ_VFADE_H

#include "classes/gf/SCOM.h"
#include "gf/GfVolumeFade.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; class GF_SCOM_HANDLE; }

namespace gf {
// table 0x7100B6A9B0
class SCOM_OBJ_VFADE : public ::gf::SCOM {
public:
    SCOM_OBJ_VFADE(GF_SCOM_HANDLE* handle, GF_OBJ_HANDLE* obj, float time, float ratio, VFPARTS parts, VFACC acc,
                   VFEFF effect, bool useKeyFrame, bool isOtherPartsOff);
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    virtual unsigned long getObjHandle() const { return reinterpret_cast<unsigned long>(m_obj); }  // slot 3

    void applyPartsRatio(GfVolumeFade* fade, float ratio);
    bool updateFade(const fw::UpdateInfo& info);  // true once the fade is done
    // the ratio at sec on keys; true once sec is past the last key
    static bool getRatioBySec(float& ratio, const mm::mtl::FixedVector<VFKEYDATA, 4>& keys, float sec);

    // the names below are not the original's
    GF_OBJ_HANDLE* m_obj;
    float m_time;        // the fade's length (the last key's time with key frames)
    float m_elapsed;
    float m_ratio;       // the ratio to reach
    float m_startRatio;  // the ratio when the fade starts (read on the first update while negative)
    VFPARTS m_parts;
    VFACC m_acc;
    VFEFF m_effect;
    unsigned char pad_44[0x4];
    mm::mtl::FixedVector<VFKEYDATA, 4> m_keys;  // GfVolumeFade::setupKeyFrame's, when asked for
    bool m_isOtherPartsOff;  // applyPartsRatio sets the other parts' ratios to 0
    bool pad_71;             // cleared by the constructor
};
}  // namespace gf
#endif
