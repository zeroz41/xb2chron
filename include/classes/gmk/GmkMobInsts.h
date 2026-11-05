#ifndef CLASSES_GMK_GMKMOBINSTS_H
#define CLASSES_GMK_GMKMOBINSTS_H

#include "mm/mtl/Vector.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/GmkSquad.h"

class CBdatWrapper;
namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }
namespace gmk {
class AGmkBase;
class GmkSquad;
// the game objects a mob gimmick spawns (GmkMob holds one at 0x48; GmkMob::create and GmkRoutedMob::create/dispose
// call its functions). No table: a plain class. Size 0xd0 (GmkMob's stride 0x118 minus 0x48).
class GmkMobInsts {
public:
    // where a mob gimmick's objects pop and what to do when they do (PopInfo::update takes one; GmkMob and
    // GmkRoutedMob each derive a PopXformFinder from it, tables 0x7100B6DD60 and 0x7100B6DE98: three slots, no
    // destructor)
    class IPopXformFinder {
    public:
        virtual bool findPosRot(mm::Vec3& pos, mm::Vec3& rot) const = 0;  // slot 0
        virtual void onPopGob(gf::GF_OBJ_HANDLE* handle) const = 0;  // slot 1
        virtual void onCreateGobInsts(unsigned int num) const = 0;  // slot 2
    };
    // a gimmick row's pop conditions (create 0x71005970BC reads them; 0x40 bytes: Vector<GmkMob>::resize zeroes
    // every field, its copy copies 0x0..0x1a as one run around the TimeCond). The field names are not the
    // original's: the columns create reads into them.
    class BdatInfo {
    public:
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCommonCondMatched(const AGmkBase& gmk) const;
        bool isPopDistCondMatched(const mm::Vec3& pos) const;
        unsigned short m_condition = 0;        // 0x0: "Condition"
        unsigned short m_group = 0;            // 0x2: "Group"
        unsigned short m_squadId = 0;          // 0x4: "squadId"
        unsigned short m_mot = 0;              // 0x6: "Mot"
        unsigned short m_collision = 0;        // 0x8: "Collision"
        unsigned short m_reactionRange = 0;    // 0xA: "ReactionRange"
        unsigned short m_reactionPercent = 0;  // 0xC: "ReactionPercent"
        unsigned short m_reactionMot = 0;      // 0xE: "ReactionMot"
        unsigned short m_battleReaction = 0;   // 0x10: "BattleReaction"
        ScenarioFlagCond m_scenarioFlag;       // 0x12: "ScenarioFlagMin"/"ScenarioFlagMax"
        QuestFlagCond m_questFlag;             // 0x16: "QuestFlag"/Min/Max
        TimeCond m_timeRange;                  // 0x20: "TimeRange"
        // squared "Visible_XZ"/"Visible_Y" and "Invisible_XZ"/"Invisible_Y" (each at least the visible one + 1)
        float m_visibleXZSq = 0.0f;    // 0x30
        float m_visibleYSq = 0.0f;     // 0x34
        float m_invisibleXZSq = 0.0f;  // 0x38
        float m_invisibleYSq = 0.0f;   // 0x3c
    };
    // how its objects pop (create 0x7100597488 reads the row; 0x48 bytes). The field names are not the
    // original's: the columns create reads into them.
    class PopInfo {
    public:
        void create(CBdatWrapper bdat, int row);
        void update(GmkMobInsts& insts, mm::mtl::Vector<gf::GF_OBJ_HANDLE*>& gobs, const IPopXformFinder& finder);
        unsigned char m_scaleMin = 100;     // 0x0: "ScaleMin"
        unsigned char m_scaleMax = 100;     // 0x1: "ScaleMax"
        unsigned char m_motSpeedMin = 100;  // 0x2: "MotSpeedMin"
        unsigned char m_motSpeedMax = 100;  // 0x3: "MotSpeedMax"
        unsigned short m_group = 0;         // 0x4: "Group"
        int m_memberNum = 0;                // 0x8: FLD_NpcGroupId's "memberNum" of the group
        unsigned short m_mot = 0;           // 0xC: "Mot"
        unsigned short m_mountPoint = 0;    // 0xE: "MountPoint"
        unsigned short m_mountObject = 0;   // 0x10: "MountObject"
        unsigned short m_mountPoint2 = 0;   // 0x12: "MountPoint2"
        unsigned short m_mountObject2 = 0;  // 0x14: "MountObject2"
        // 0x18: the mob ids: "MobID", or FLD_MobGroupList's ids of "MOBGroupID"
        mm::mtl::FixedVector<unsigned int, 8> m_mobIds;
        // 0x40: how many pop, random in "PopMin".."PopMax"; 1 makes the pop finders pop at the gimmick's own
        // position, else somewhere in its shape (GmkMob::PopXformFinder::findPosRot)
        int m_popNum = 0;
        bool m_hasSquad = false;  // 0x44: "squadId" is set
    };
    // what update and the sequence steps are given (GmkRoutedMob::update builds it on the stack; the names are not
    // the original's)
    class UpdateInfo {
    public:
        float m_dt;                       // 0x0
        const mm::Vec3* m_pos;            // 0x8
        const IPopXformFinder* m_finder;  // 0x10
    };
    // inline (no symbol in 1.0.0 or 3.0.1): GmkMob's destructor runs dispose again after its own dispose; the
    // members' destructors then empty m_popInfo's id list
    ~GmkMobInsts() {
        dispose();
    }
    void dispose();
    // shows or hides one of its objects by pad_a0 (display bit 8) when the object is bound to a gimmick
    void validateDisp(gf::GF_OBJ_HANDLE* handle) const;
    void disposeGobInsts(bool);
    // inline (no symbol; GmkMob::create and GmkRoutedMob::create): the row's conditions, an empty object list
    // (allocated at gmk_mob_impl.h line 513), the squad and the first sequence step (the name is not the original's)
    void create(AGmkBase* gmk, unsigned char* bdatFp, int bdatId);
    // inline (no symbol; GmkMob::onGobEvent and GmkRoutedMob::onGobEvent): drops a destroyed object from the list
    // (the name is not the original's)
    void removeGobInst(gf::GF_OBJ_HANDLE* handle) {
        if (m_gobInsts->size() != 0) {
            for (gf::GF_OBJ_HANDLE** it = m_gobInsts->begin(); it != m_gobInsts->end(); ++it) {
                if (*it == handle) {
                    m_gobInsts->erase(it);
                    break;
                }
            }
        }
    }
    void createSquad(unsigned short squadId);
    void seqUpdatePopDepop(const UpdateInfo& info);
    // inline (GmkMob::isValid, GmkRoutedMob::isValid and update): it has objects, and a squad that is valid when its
    // row names one (the name is not the original's)
    bool isValid() const {
        return m_gobInsts != nullptr &&
               (m_bdatInfo.m_squadId == 0 || (m_squad != nullptr && m_squad->isValid()));
    }
    // dispose clears these three; create sets them: the gimmick, its list's BDAT table and its row (the names are
    // not the original's)
    AGmkBase* m_gmk = nullptr;
    unsigned char* m_bdatFp = nullptr;
    int m_bdatId = -1;
    unsigned char pad_14[0x4];  // not set by the constructor; the copy copies it with pad_0..pad_10
    BdatInfo m_bdatInfo;  // 0x18 (the name is not the original's)
    PopInfo m_popInfo;    // 0x58 (the name is not the original's)
    bool pad_a0 = true;  // validateDisp(handle) shows the objects while it is set
    // 0xa8: GmkMob's game objects (the name is not the original's)
    mm::mtl::Vector<gf::GF_OBJ_HANDLE*>* m_gobInsts = nullptr;
    // 0xb0: the squad its objects join; the pop finders place the objects by it while it has room (the name is not
    // the original's)
    GmkSquad* m_squad = nullptr;
    // 0xb8: flag bits (dispose clears bits 0..2; the name is not the original's)
    unsigned long m_flags = 0;
    // 0xc0: the sequence step (seqUpdatePopDepop / seqWaitToFadeOutOfGobInst; GmkMob::create sets it; the name is
    // not the original's)
    void (GmkMobInsts::*m_seq)(const UpdateInfo&) = nullptr;
};
}  // namespace gmk

#endif
