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
    // what create takes: the gimmick section's version, the gimmick's data in it, its BDAT row's BdatInfo and the
    // row (TGmkList::createGmk builds it; AGmkBase::create keeps a copy in m_createInfo; the names are not the
    // original's). Its constructor clears all four: the gimmicks' inline constructors store them in that order.
    class CreateInfo {
    public:
        CreateInfo() : m_version(0), m_data(nullptr), m_bdatInfo(nullptr), m_bdatId(-1) {}
        unsigned int m_version;
        const unsigned char* m_data;
        const void* m_bdatInfo;
        int m_bdatId;
    };
    // inline (1.0.0 has an out-of-line copy; 3.0.1's Vector<T>::resize loops inline its stores)
    AGmkBase() : m_list(nullptr), m_pos(nullptr), m_info(nullptr), pad_40(nullptr) {}
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
    // what create got (AGmkBase::create copies all four; dispose clears the version, the data and the BdatInfo; the
    // name is not the original's). m_createInfo.m_data: data the gimmick keeps (GfComBehaviorGmk tests a salvage
    // locator's (kind 0x20) first byte against 2 to answer the PC's access query); m_createInfo.m_bdatInfo: its row's
    // BdatInfo, of the derived class's type (GmkTbox::BdatInfo::isPopCondMatchedExceptDist and
    // GmkPrecious::BdatInfo::isPopCondMatched are called on it, gf_field_locator); m_createInfo.m_bdatId: the
    // gimmick's row in that table (GfFieldTbox reads its RSC_ID by it, and passes it as the quest gimmick id)
    CreateInfo m_createInfo;
    // cleared by the constructor, meaning not known
    const void* pad_40;
};
// the gimmick bound to an object, null for none
AGmkBase* getBindedGmkInst(gf::GF_OBJ_HANDLE* handle);
class GmkEnemy;
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions because their gimmick's class
// (GmkType 0x3A, the one gf_field_locator's enemy wave locator finds by its "EnemyWaveID") is not known yet; all three
// are defined in GmkElevator.cpp's unit and take that gimmick.
// What fn_71005B38EC does: false unless every entry of its array at 0x148 (0x18 bytes each, count at 0x448) holds a
// valid gimmick with data at 0x48/0x50, a positive count at 0x58 and a set byte at 0xE2; then its flags at 0x142, or
// its BdatInfo's conditions (GfGameManager event state, GfGameCond::isGameCond). LocatorGimmick and GfGmkLocator call
// it too.
bool fn_71005B38EC(const AGmkBase* gmk);
// What fn_71005B3814 does: its data's (m_createInfo.m_data) u32 at 0x10 minus its u32 at 0xC: how many enemies
// fn_71005B3824 can return
unsigned int fn_71005B3814(const AGmkBase* gmk);
// What fn_71005B3824 does: the GmkEnemy (0x1D8-byte element) at its data's u32 at 0xC plus index in the enemy list of
// its list's create info (0x1B8), none when that list is missing or shorter
const GmkEnemy* fn_71005B3824(const AGmkBase* gmk, unsigned int index);
// whether the player's object exists (defined in GmkElevator.cpp's unit; StateFieldHome::isCondMatch is its tail
// call)
bool isPlayerExist();
// a gimmick's BDAT row and sheet names for debug output: "(null)" in this build
const char* debugGetGmkBdatRowName(const AGmkBase& gmk);
const char* debugGetGmkBdatSheetName(const AGmkBase& gmk);
// the player's position (GfFieldGimmick::update hands it to GfGameUtil::isPointSavable)
const mm::Vec3& getPlayerPos();
// the current map's FLD_maplist id (defined in GmkElevator.cpp's unit)
int getCurrentMapBdatId();
// show or hide the gimmicks of a type: all of them, the one of a BDAT row, the one of a gimmick set's index (defined
// in GmkElevator.cpp's unit; GfGameUtil's setDispByGmkType* forward to them)
void setDispByGmkType(GmkType type, bool disp);
void setDispByGmkTypeAndBdatId(GmkType type, int bdatId, bool disp);
void setDispByGmkTypeAndGmkIdx(int gmkSetId, GmkType type, unsigned int idx, bool disp);
}  // namespace gmk

#endif
