#ifndef CLASSES_GF_GFBDATUNIQUEMOTION_H
#define CLASSES_GF_GFBDATUNIQUEMOTION_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedQueue.h"

namespace gf { class GfBdatUniqueMotion; }

namespace gf {
// table 0x7100B47F28; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatUniqueMotion : public ::mm::mtl::PtrSingleton< ::gf::GfBdatUniqueMotion>, public ::gf::IDataBdat, public ::fw::MessageObject {
public:
    GfBdatUniqueMotion();
    virtual ~GfBdatUniqueMotion();  // slot 0
    virtual void bdatRefresh();  // slot 2

    // a set of party characters, by chara id, sorted, 0 for none (GfGamePlayerUniqueScheduler fills one from its first
    // six members and std::sorts it)
    struct PresetKey {
        // inline (3.0.1's callers load every id before they store the first; the form is not known)
        PresetKey(unsigned short id0, unsigned short id1, unsigned short id2, unsigned short id3, unsigned short id4,
                  unsigned short id5) {
            m_ids[0] = id0;
            m_ids[1] = id1;
            m_ids[2] = id2;
            m_ids[3] = id3;
            m_ids[4] = id4;
            m_ids[5] = id5;
        }
        // whether every non-zero id of this key is in key, in order (the ids of both are sorted)
        bool isContain(const PresetKey& key) const;
        unsigned short m_ids[6];  // the name is not the original's
    };
    // one preset: a weight to draw it by, the motion each character of it plays and after how long, and the
    // characters it needs (GfGamePlayerUniqueScheduler::judge draws one from queryPreset's; the field names are
    // not the original's)
    struct PresetInfo {
        struct Entry {
            unsigned short m_charaId;
            unsigned short m_motion;
            float m_wait;
        };
        unsigned short m_weight;
        unsigned char pad_2[0x2];
        Entry m_entries[6];
        PresetKey m_key;
    };
    // a character's own unique motion: how likely it plays one, the wait before it does, and the weights of its
    // three motions (GfGamePlayerUniqueScheduler::judge reads them; the type and field names are not the original's)
    struct CharaInfo {
        unsigned char pad_0[0x2];
        unsigned short m_rate;  // percent
        float m_waitMin;
        float m_waitMax;
        unsigned short m_weights[3];
    };
    // the presets whose key the party's key contains
    static void queryPreset(mm::mtl::FixedQueue<const PresetInfo*, 32>* presets, const PresetKey& key);
    static const CharaInfo* getCharaInfo(unsigned short charaId);
    unsigned char pad_28[0x8];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
