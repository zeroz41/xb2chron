#ifndef CLASSES_GMK_AGMKNPC_H
#define CLASSES_GMK_AGMKNPC_H

#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/GmkNpcManager.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B719F8
// its links (+0x8..+0x18) are a base, not a member: its copy constructor copies them apart from pad_18 (a base copy
// is not merged with the member copies), as GmkNpc's and GmkRoutedNpc's copy loops do
class AGmkNpc : public mm::mtl::IntrusiveListNodeBase {
public:
    virtual ~AGmkNpc() {}  // slot 0
    virtual bool isPopCondMatched() const = 0;  // slot 2
    virtual bool isDepopCondMatched() const = 0;  // slot 3
    virtual void vf4() = 0;  // slot 4
    virtual void vf5() = 0;  // slot 5
    virtual unsigned char* getBindedBdatFp() const = 0;  // slot 6: its list's BDAT table
    virtual int getBindedBdatId() const = 0;  // slot 7: its BDAT row
    // true when it found them (GmkNpc's returns 1; LocatorTalk_NpcID::update tests it)
    virtual bool findPopPosRot(mm::Vec3& pos, mm::Vec3& rot) const = 0;  // slot 8
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const = 0;  // slot 9
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const = 0;  // slot 10
    virtual void validateDisp() const = 0;  // slot 11
    virtual void debugUpdate(float) {}  // slot 12
    // GmkNpc's (base at 0x48) and GmkRoutedNpc's (base at 0x50) Vector<T>::resize store it at the base's +0x18
    // 0x18: its NPC id's entry in the set's GmkNpcManager; GmkRoutedNpc::isPopCondMatchedExceptDist tests that the
    // entry names this gimmick and getGobInst reads the entry's game object (the name is not the original's)
    const GmkNpcManager::NpcIdInfo* m_npcIdInfo = nullptr;
};
}  // namespace gmk

#endif
