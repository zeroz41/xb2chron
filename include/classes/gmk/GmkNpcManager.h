#ifndef CLASSES_GMK_GMKNPCMANAGER_H
#define CLASSES_GMK_GMKNPCMANAGER_H

#include "mm/mtl/Vector.h"
#include "mm/mtl/IntrusiveList.h"

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
    void update(float dt, bool flag);
    // out of line: GmkNpcManager::removeGmkNpc tail-calls it
    void removeGmkNpc(AGmkNpc* npc);
    void setActiveGmkNpc(AGmkNpc* npc);
    void createGobInst();
    // inline: unbinds and destroys its game object, then activates the first gimmick whose pop conditions hold
    // (dispose, removeGmkNpc and the NPC gimmicks' onGobEvent; the name is not the original's)
    void disposeGobInst();
    // an NPC id, its table and its gimmick list set (GmkNpcManager::update and addGmkNpc test these three; the name is
    // not the original's)
    bool isValid() const { return m_npcId != 0 && m_bdatFp != nullptr && m_gmks != nullptr; }
    // 0x0: the row's NpcID (addGmkNpc stores it; the name is not the original's)
    unsigned short m_npcId;
    unsigned char pad_2[0x6];
    unsigned char* m_bdatFp;  // 0x8: the first gimmick's BDAT table (addGmkNpc; the name is not the original's)
    // 0x10: the gimmicks of this NPC id, by BDAT row (addGmkNpc allocates it; the name is not the original's)
    ::mm::mtl::IntrusiveList<AGmkNpc>* m_gmks;
    AGmkNpc* m_gmk;  // 0x18: the NPC's gimmick (LocatorTalk_NpcID::update asks it for its pop position)
    unsigned char pad_20[0x10];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x30: the NPC's game object (LocatorTalk_NpcID::update reads its position)
};

// table 0x7100B6C210
class GmkNpcManager {
public:
    virtual ~GmkNpcManager();  // slot 0
    void dispose();
    // one entry per row of BDAT tables 0xA8, 0x88 and 0x8A
    void create();
    // GmkSet::update runs it each frame after its BDAT step
    void update(float dt);
    const GmkNpcIdInfo* getNpcIdInfoByNpcId(int npcId) const;
    static int getNpcIdInfoIdxFromNpcId(int npcId);
    // an NPC gimmick entered into / taken out of its NPC id's entry (GmkNpcList's and GmkRoutedNpcList's createGmk
    // and disposeGmk pass each gimmick's AGmkNpc base)
    void addGmkNpc(AGmkNpc* npc);
    void removeGmkNpc(AGmkNpc* npc);
    // FLD_NpcGroupId row's scenario, quest, time range and game conditions (GmkNpc's and GmkMobInsts'
    // BdatInfo::isPopCommonCondMatched call it)
    bool isGroupCondMatched(unsigned short groupId) const;
    // 0x8: its NPC ids' entries (the destructor destroys them; the name is not the original's)
    ::mm::mtl::Vector<GmkNpcIdInfo> m_npcIdInfos;
    int m_npcIdTop;  // 0x30: table 0xA8's first id (create; dispose clears it; the name is not the original's)
    // 0x34: how many entries update runs per frame outside a fade-out (min with the entry count; GmkSet::createGmkLists
    // sets 0x20; the name is not the original's)
    unsigned int m_updateNumPerFrame;
    unsigned int m_updateIdx;  // 0x38: the first entry update runs next (the name is not the original's)
    // 0x3c: passed to each entry's update (GmkSet::create stores the negation of its CreateInfo's m_flag; the name is
    // not the original's)
    bool m_flag;
};
}  // namespace gmk

#endif
