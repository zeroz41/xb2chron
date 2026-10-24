#ifndef CLASSES_GMK_GMKCTRLVOLSE_H
#define CLASSES_GMK_GMKCTRLVOLSE_H

#include "mm/Vec3.h"

namespace fw { class SoundPack; enum SoundCategory : int; }

namespace gmk {
// table 0x7100B52528; 0x80 bytes (GfFieldMapGimmick holds five, 0x80 apart)
class GmkCtrlVolSe {
public:
    // create copies 0x1b bytes, m_pos and +0x30; the defaults are what GfFieldMapGimmick's constructions store first
    // (the field names are inferred, not the original's)
    class CreateInfo {
    public:
        CreateInfo()
            : m_pack(nullptr), m_seId(0), m_category(fw::SoundCategory(6)), m_minDist(0.0f), m_maxDist(10.0f),
              m_volume(0), pad_19(100), pad_1a(100), m_pos(mm::Vec3::zero), pad_30(-1) {}
        fw::SoundPack* m_pack;          // playSe's pack
        unsigned short m_seId;          // playSe's id
        fw::SoundCategory m_category;   // playSe's category
        float m_minDist;                // both set from a row's LOD size
        float m_maxDist;
        unsigned char m_volume;         // playSe's volume in percent
        unsigned char pad_19;
        unsigned char pad_1a;
        mm::Vec3 m_pos;                 // where it plays (the gimmick's position)
        long pad_30;
    };
    GmkCtrlVolSe();
    // inline: GfFieldMapGimmick's destructor stores this table and calls dispose() in place
    virtual ~GmkCtrlVolSe() {  // slot 0
        dispose();
    }
    void dispose();
    void createInst();
    void update(float dt);
    bool isPlayEnd() const;
    void create(const CreateInfo& info);
    unsigned char pad_8[0x78];
};
}  // namespace gmk

#endif
