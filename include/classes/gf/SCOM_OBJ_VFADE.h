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
    // the fade's length with key frames: the last key's time (0 with fewer than two keys); 1.0.0 has it out of
    // line, 3.0.1 has no copy
    float getKeyFrameSec() const { return m_keys.size() < 2 ? 0.0f : m_keys[m_keys.size() - 1].m_time; }

    // queues a fade of obj to ratio over time. 1.0.0 has it out of line,
    // 3.0.1 has no copy (createBattle and createParts inline it)
    static unsigned long create(GF_OBJ_HANDLE* obj, float time, float ratio, VFPARTS parts, VFACC acc, VFEFF effect);
    // the same with obj's attribute (DataParamAcc::getAttribute) as the effect type
    static unsigned long createParts(GF_OBJ_HANDLE* obj, float time, float ratio, VFPARTS parts, VFACC acc);
    // the same, setting the other parts' ratios to 0
    static unsigned long createPartsWithSingle(GF_OBJ_HANDLE* obj, float time, float ratio, VFPARTS parts, VFACC acc);
    // the key-frame fade for a dead object (when it has a volume fade): returns its length
    static float createDead(GF_OBJ_HANDLE* obj, unsigned int effect);
    static unsigned long createBattle(GF_OBJ_HANDLE* obj, float ratio, unsigned int effect);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it builds an
    // SCOM_OBJ_VFADE (its table, its constructor). What it does: like createBattle (ratio 0, all parts, acc 4) but
    // never queues the request: updates the fade once with a one-frame UpdateInfo (GfInfo::m_fSecPerFrame), then
    // deletes it. Caller: GfGameParty::fn_71002BC46C.
    static void fn_710055E1A4(GF_OBJ_HANDLE* obj, float ratio, unsigned int effect);
    // createParts (acc 4) for an enemy blade or blade 0x451, else createPartsWithSingle (part 0 for other blades)
    static unsigned long createBattleParts(GF_OBJ_HANDLE* obj, float time, float ratio, unsigned int, VFPARTS parts);

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
    bool pad_71;             // cleared by the constructor, set by createDead
};
}  // namespace gf
#endif
