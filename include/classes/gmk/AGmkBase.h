#ifndef CLASSES_GMK_AGMKBASE_H
#define CLASSES_GMK_AGMKBASE_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }
namespace mm { class Mat44; }
namespace fw { struct ColiCheckConfig; }
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
    // the length of a ray snapping it on the ground, by its shape's scale (StateFieldAreaWalk::seqInitGoalPos)
    float getYSnapRayLength() const;
    // a position inside the gimmick's shape (out of line, 0x71005798CC; returns pos; the pop finders of GmkMob and
    // GmkEnemy call it with false when the gimmick does not pop at its own position)
    mm::Vec3& getPositionInShape(mm::Vec3& pos, bool) const;
    // whether pos snapped onto the ground (out of line, 0x710057A4FC; StateAreaMove<GfComBehaviorMob>::seqInitGoalPos
    // passes the same vector twice and true)
    bool getPositionAppliedYSnap(mm::Vec3& out, const mm::Vec3& from, bool) const;
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
// whether a gimmick's game object is in view (GmkSet::isGmkInstValidView's test for the kinds with one object)
bool isValidView(gf::GF_OBJ_HANDLE* handle);
// whether a gimmick of kind T with game objects not bound to it is in view (symbols:
// isGmkValidViewUnbound<GmkEnemy>, <GmkRoutedEnemy>, <GmkMob>, <GmkRoutedMob>; GmkSet::isGmkInstValidView calls them)
template <class T>
bool isGmkValidViewUnbound(const AGmkBase& gmk);
class GmkEnemy;
// whether the player's object exists (defined in GmkElevator.cpp's unit; StateFieldHome::isCondMatch is its tail
// call)
bool isPlayerExist();
// sends SCOM_DESTROY_GAME_OBJ for handle's object after time seconds unless it is gone, being destroyed or has flag
// 17 (0x710057C080; GfMobSlotManager::update and createMobInfos call it)
void disposeGobInst(gf::GF_OBJ_HANDLE* handle, float time);
// snaps a point on the ground below from: a line test (fw::ColiCheck::testLineChara) from from down by length with
// config; out takes the nearest hit whose y is not negative. False when nothing was hit (0x710057B63C; the pop
// finders, GmkEffect::applyEffectParam and the gimmicks' validateIconPos call it)
bool getYSnapPos(mm::Vec3& out, const mm::Vec3& from, float length, const fw::ColiCheckConfig& config);
// the water surface height at pos: a line test (testLineChara, flags 9, all groups) range long centred on pos whose
// first hit has material 1; false otherwise (PopPosSafeCond::isMatch and GmkEnemyInsts::PopInfo::validatePopPos)
bool getWaterHeight(float& height, const mm::Vec3& pos, float range);
// whether the navigation mesh has a point near pos (fw::NaviUtil::testNaviColi with 2, 2)
bool isNaviMeshExist(const mm::Vec3& pos);
// a gimmick's BDAT row and sheet names for debug output: "(null)" in this build
const char* debugGetGmkBdatRowName(const AGmkBase& gmk);
const char* debugGetGmkBdatSheetName(const AGmkBase& gmk);
// the player's position (GfFieldGimmick::update hands it to GfGameUtil::isPointSavable)
const mm::Vec3& getPlayerPos();
// whether getInterestPos has a position to give: the scene's camera (no GmkManager, or its mode at 0x198 is 1), the
// player (mode 0); none in any other mode
bool isInterestPosExist();
// the position the gimmicks measure against: the camera's global position (no GmkManager, or mode 1), the player's
// (mode 0), else mm::Vec3::zero
const mm::Vec3& getInterestPos();
// the current map's FLD_maplist id (defined in GmkElevator.cpp's unit)
int getCurrentMapBdatId();
// show or hide the gimmicks of a type: all of them, the one of a BDAT row, the one of a gimmick set's index (defined
// in GmkElevator.cpp's unit; GfGameUtil's setDispByGmkType* forward to them)
void setDispByGmkType(GmkType type, bool disp);
void setDispByGmkTypeAndBdatId(GmkType type, int bdatId, bool disp);
void setDispByGmkTypeAndGmkIdx(int gmkSetId, GmkType type, unsigned int idx, bool disp);
// shows or hides one gimmick (GmkInstDispTraverserByBdatId::onTraverse and setDispByGmkTypeAndGmkIdx call it; no
// symbol: placeholder name)
void fn_71005D3C54(const AGmkBase& gmk, bool, bool disp);
// whether the gimmick's npc motion blinks (its row's Mot names a FLD_NpcMobMotionId row without notEyeBlink);
// GfComBehaviorMob::setup and GfComBehaviorNpc::setup call it (defined in GmkElevator.cpp's unit)
bool hasEyeBlink(const AGmkBase& gmk);
// the gimmick's BDAT row "FSID" (u16) for gimmick types 0x21, 0x25 and 0x26; a treasure box (9) whose BdatInfo byte 2
// is set reads "FSID2" while its progress flag is clear; 0 for any other type (GfGmkLocatorAtlas::seqWaitToCreateGmkSet
// and GfGameUtil::getUiInfoIconBdatId call it)
int getBindedFsId(const AGmkBase& gmk);
// whether a squad member's object may pop: not waiting, transform valid, not destroyed, no flag 17, and its enemy
// behaviour not in state 13 (GmkEnemyInsts::PopInfo::update calls it)
bool canPopSquadMember(gf::GF_OBJ_HANDLE* handle);
}  // namespace gmk

#endif
