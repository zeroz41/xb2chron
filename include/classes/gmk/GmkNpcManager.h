#ifndef CLASSES_GMK_GMKNPCMANAGER_H
#define CLASSES_GMK_GMKNPCMANAGER_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gmk { class AGmkNpc; }

namespace gmk {
// table 0x7100B6C210
class GmkNpcManager {
public:
    virtual ~GmkNpcManager();  // slot 0
    void dispose();
    // what the manager keeps per NPC id: an entry of a vector of 0x38-byte elements (getNpcIdInfoByNpcId indexes it
    // by getNpcIdInfoIdxFromNpcId(npcId)); the name follows getNpcIdInfoByNpcId, not the original's
    struct NpcIdInfo {
        unsigned char pad_0[0x18];
        AGmkNpc* m_gmk;  // 0x18: the NPC's gimmick (LocatorTalk_NpcID::update asks it for its pop position)
        unsigned char pad_20[0x10];
        gf::GF_OBJ_HANDLE* m_handle;  // 0x30: the NPC's game object (LocatorTalk_NpcID::update reads its position)
    };
    const NpcIdInfo* getNpcIdInfoByNpcId(int npcId) const;
};
}  // namespace gmk

#endif
