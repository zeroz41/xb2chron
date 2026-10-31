#ifndef CLASSES_GMK_GMKNPCMANAGER_H
#define CLASSES_GMK_GMKNPCMANAGER_H

#include "mm/mtl/Vector.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gmk { class AGmkNpc; }

namespace gmk {
// what the manager keeps per NPC id: an element of its vector (0x38 bytes; getNpcIdInfoByNpcId indexes it by
// getNpcIdInfoIdxFromNpcId(npcId)). The class name is the symbols' (gmk::GmkNpcIdInfo::dispose)
class GmkNpcIdInfo {
public:
    // inline: ~GmkNpcManager's vector destructor calls dispose() per element in place
    ~GmkNpcIdInfo() { dispose(); }
    void dispose();
    unsigned char pad_0[0x18];
    AGmkNpc* m_gmk;  // 0x18: the NPC's gimmick (LocatorTalk_NpcID::update asks it for its pop position)
    unsigned char pad_20[0x10];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x30: the NPC's game object (LocatorTalk_NpcID::update reads its position)
};

// table 0x7100B6C210
class GmkNpcManager {
public:
    virtual ~GmkNpcManager();  // slot 0
    void dispose();
    // GmkSet::update runs it each frame after its BDAT step
    void update(float dt);
    const GmkNpcIdInfo* getNpcIdInfoByNpcId(int npcId) const;
    static int getNpcIdInfoIdxFromNpcId(int npcId);
    // 0x8: its NPC ids' entries (the destructor destroys them; the name is not the original's)
    ::mm::mtl::Vector<GmkNpcIdInfo> m_npcIdInfos;
};
}  // namespace gmk

#endif
