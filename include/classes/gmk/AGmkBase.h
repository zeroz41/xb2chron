#ifndef CLASSES_GMK_AGMKBASE_H
#define CLASSES_GMK_AGMKBASE_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }
namespace mm { class Mat44; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// a gimmick's kind (getGmkType's: 9 a treasure box, 0x20 a salvage locator, 0x3C an elevator; GfQuestUtil takes it)
enum GmkType : int {};
}  // namespace gmk

namespace gmk {
class IGmkList;
class LvlbInfo;
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
    // the gimmick's matrix (StateTalk turns its npc back to the gimmick's facing from row 2)
    void getMatrix(mm::Mat44& mtx, bool world) const;
    // whether pos lies inside the gimmick's shape (GfGameInsideBattleLock::isInside asks a battle lock's with 0)
    bool isInsideShape(const mm::Vec3& pos, float margin) const;  // the BDAT table of the gimmick's kind
    // the list holding it (TGmkList::createGmk stores the list there; isValid tests it, the destructor clears it;
    // the name is not the original's)
    IGmkList* m_list;
    // the gimmick's position: gf_field_locator's locators copy its x, y, z (LocatorTbox::update and its kin); the
    // name is not the original's
    const mm::Vec3* m_pos;
    // its INFO entry in the gimmick section, none when its list has none (TGmkList::createGmk; the destructor clears
    // it; the name is not the original's)
    const LvlbInfo* m_info;
    // the gimmick section's version: create copies it with m_data (one 8-byte copy of 0x20..0x27), dispose clears
    // it (the name is not the original's)
    unsigned int m_version;
    unsigned char pad_24[0x4];
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
// the player's position (GfFieldGimmick::update hands it to GfGameUtil::isPointSavable)
const mm::Vec3& getPlayerPos();
// the current map's FLD_maplist id (defined in GmkElevator.cpp's unit)
int getCurrentMapBdatId();
// show or hide the gimmicks of a type: all of them, the one of a BDAT row, the one of a gimmick set's index (defined
// in GmkElevator.cpp's unit; GfGameUtil's setDispByGmkType* forward to them)
void setDispByGmkType(GmkType type, bool disp);
void setDispByGmkTypeAndBdatId(GmkType type, int bdatId, bool disp);
void setDispByGmkTypeAndGmkIdx(int gmkSetId, GmkType type, unsigned int idx, bool disp);
// what create takes: the gimmick section's version, the gimmick's data in it, its BDAT row's BdatInfo and the row
// (TGmkList::createGmk builds it; AGmkBase::create keeps a copy; the names are not the original's)
class AGmkBase::CreateInfo {
public:
    CreateInfo() : m_data(nullptr), m_bdatInfo(nullptr), m_bdatId(-1) {}
    unsigned int m_version;
    const unsigned char* m_data;
    const void* m_bdatInfo;
    int m_bdatId;
};

}  // namespace gmk

#endif
