#ifndef CLASSES_GMK_GMKCTRLVOLSE_H
#define CLASSES_GMK_GMKCTRLVOLSE_H

#include "mm/Vec3.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class SoundPack; enum SoundCategory : int; }

namespace gmk {
// table 0x7100B52528; 0x80 bytes (GfFieldMapGimmick holds five, 0x80 apart). Linked (its node at 0x8) into
// GmkCtrlVolSeManager's list while it plays: createInst links it, dispose unlinks it
class GmkCtrlVolSe : public ::mm::mtl::IntrusiveListNodeBase {
public:
    // create copies 0x1b bytes, m_pos and +0x30; the defaults are what GfFieldMapGimmick's constructions store first
    // (the field names are inferred, not the original's)
    class CreateInfo {
    public:
        CreateInfo()
            : m_pack(nullptr), m_seId(0), m_category(fw::SoundCategory(6)), m_minDist(0.0f), m_maxDist(10.0f),
              m_volume(0), m_nearVolume(100), m_roomVolume(100), m_pos(mm::Vec3::zero), m_gob(-1) {}
        fw::SoundPack* m_pack;          // playSe's pack
        unsigned short m_seId;          // playSe's id
        fw::SoundCategory m_category;   // playSe's category
        float m_minDist;                // both set from a row's LOD size
        float m_maxDist;
        unsigned char m_volume;         // playSe's volume in percent; update's at m_minDist and beyond
        unsigned char m_nearVolume;     // update's volume in percent at m_maxDist and nearer
        unsigned char m_roomVolume;     // update scales the volume by it (percent) in a room
        mm::Vec3 m_pos;                 // where it plays (the gimmick's position)
        long m_gob;                     // update follows this object's position unless -1 (a GF_OBJ_HANDLE*)
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
    unsigned char pad_18[0x8];
    CreateInfo m_info;          // 0x20: what create was given (dispose resets it)
    unsigned int m_seHandle;    // 0x60: the playing sound (0: none)
    float m_dist;               // 0x64: update's distance from the player
    bool m_isPaused;            // 0x68: update leaves the volume alone while set
    mm::Vec3 m_curPos;          // 0x70: where it plays now (m_pos, then m_gob's position)
    // (the field names are inferred, not the original's)
};
}  // namespace gmk

#endif
