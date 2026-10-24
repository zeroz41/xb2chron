#ifndef CLASSES_GMK_AGMKBASE_H
#define CLASSES_GMK_AGMKBASE_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// a gimmick's kind (getGmkType's: 9 a treasure box, 0x20 a salvage locator, 0x3C an elevator; GfQuestUtil takes it)
enum GmkType : int {};
}  // namespace gmk

namespace gmk {
// table 0x7100B6BE18
class AGmkBase {
public:
    class CreateInfo;
    virtual ~AGmkBase();  // slot 0
    virtual gmk::GmkType getGmkType() const = 0;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}  // slot 9
    virtual void debugUpdateMmf() {}  // slot 10
    unsigned char* getBindedBdatFp() const;
    // whether pos lies inside the gimmick's shape (GfGameInsideBattleLock::isInside asks a battle lock's with 0)
    bool isInsideShape(const mm::Vec3& pos, float margin) const;  // the BDAT table of the gimmick's kind
    unsigned char pad_8[0x8];
    // the gimmick's position: gf_field_locator's locators copy its x, y, z (LocatorTbox::update and its kin); the
    // name is not the original's
    const mm::Vec3* m_pos;
    unsigned char pad_18[0x10];
    // data the gimmick keeps; GfComBehaviorGmk tests a salvage locator's (kind 0x20) first byte against 2 to
    // answer the PC's access query (the name is not the original's)
    const unsigned char* m_data;
    // its row's BdatInfo, of the derived class's type: GmkTbox::BdatInfo::isPopCondMatchedExceptDist and
    // GmkPrecious::BdatInfo::isPopCondMatched are called on it (gf_field_locator); the name is not the original's
    const void* m_bdatInfo;
    // the gimmick's row in that table (GfFieldTbox reads its RSC_ID by it, and passes it as the quest gimmick id; the
    // name is not the original's)
    unsigned int m_bdatId;
    unsigned char pad_3c[0xc];  // fields: size from its derived classes
};
// the gimmick bound to an object, null for none
AGmkBase* getBindedGmkInst(gf::GF_OBJ_HANDLE* handle);
// whether the player's object exists (defined in GmkElevator.cpp's unit; StateFieldHome::isCondMatch is its tail
// call)
bool isPlayerExist();
}  // namespace gmk

#endif
