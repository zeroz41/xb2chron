#ifndef CLASSES_GMK_TUNK_B6D418_H
#define CLASSES_GMK_TUNK_B6D418_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkPhantom.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gmk/GmkEnemyWaveExtension.h"

namespace gmk {
// 2.0.0's symbols name it. Element (0x4A0 bytes) of the list TGmkList<GmkEnemyWave, ..., 'ENEW', ...> (table
// 0x7100B6F140) that GmkEnemyList's member at 0x470 derives from. Inferred: the enemy wave gimmick gf_field_locator
// finds by "EnemyWaveID" (isPopCondMatched's notes below).
class GmkEnemyWaveGob;
class GmkEnemy;
class GmkSealedStone;

class alignas(16) GmkEnemyWave : public ::gmk::AGmkBase {
public:
    // weak (tail of the unit): emitted with the table, whose key function is create
    virtual ~GmkEnemyWave() { dispose(); }  // slot 0 (fn_71005BC2DC; D0 fn_71005BC3D0)
    virtual gmk::GmkType getGmkType() const { return TYPE; }  // slot 2 (fn_71005BC3F4)
    virtual bool isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }  // slot 3 (fn_71005BC3FC)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (fn_71005B3A50, 0x314)
    virtual void dispose();  // slot 5 (fn_71005B3FB0, 0x128; the destructor calls it out of line)
    virtual void update(float);  // slot 6 (fn_71005B49A4, 0x254)
    virtual void debugDraw() const;  // slot 7 (fn_71005B4DF0, empty)
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9 (fn_71005B514C, 0x188)
    // its row (0x40 bytes: TGmkList::createGmk's stride; the names are not the original's)
    class BdatInfo {
    public:
        // its row reader: out of line (create), called by initGmkBdatInfo (fn_7100634E2C) where the template
        // calls T1::create (so the name is the template's; the CBdatWrapper parameter as GmkElevator::BdatInfo's)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        unsigned char pad_0[0x2c];
        unsigned short m_mapGimmickId;  // 0x2C: the map gimmick (GmkType 0x21) seqWaitToValidLinkGmkList reaches with m_secondAcc
        unsigned char pad_2e[0x2];
        unsigned short pad_30;  // GmkBattleChallenge::seqWaveStart's timer (0: none)
        unsigned char pad_32[0xa];
        unsigned short m_sealedStoneIndex;  // 0x3C: from 1, the gimmick set's GmkSealedStoneList element seqWaitToValidLinkGmkList takes
        unsigned char pad_3e[0x2];
    };
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    static const gmk::GmkType TYPE = gmk::GmkType(0x3a);
    // its data (m_createInfo.m_data): the range of enemies (GmkEnemy, the gimmick set's enemy list) it holds, by
    // index (the names are not the original's)
    struct Data {
        unsigned char pad_0[0xc];
        unsigned int m_enemyBegin;  // 0xC
        unsigned int m_enemyEnd;    // 0x10
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // one entry of the array isPopCondMatched walks (0x18 bytes): one of its enemies; create sorts them by priority, then
    // index
    struct Entry {
        Entry() {}
        // the pop settings copied member by member (create's stores skip the WavePopInfo's padding byte)
        Entry(GmkEnemy* enemy, unsigned short index, const GmkEnemyWaveExtension::WavePopInfo& popInfo) : m_enemy(enemy), pad_8(0), m_index(index), pad_e(0) {
            m_popInfo.m_partyFlag = popInfo.m_partyFlag;
            m_popInfo.m_popPriority = popInfo.m_popPriority;
            m_popInfo.m_popNumCond = popInfo.m_popNumCond;
            m_popInfo.m_battleLockName = popInfo.m_battleLockName;
            m_popInfo.m_popTimerCond = popInfo.m_popTimerCond;
        }
        GmkEnemy* m_enemy;
        unsigned int pad_8;  // create and seqWaitToValidLinkGmkList clear it
        unsigned short m_index;  // 0xC: its index in the data's range (the name is not the original's)
        unsigned short pad_e;  // create and seqWaitToValidLinkGmkList clear it
        GmkEnemyWaveExtension::WavePopInfo m_popInfo;  // 0x10 (the name is not the original's)
    };
    // 2.0.0's symbols name the next three (defined in GmkElevator.cpp's unit).
    // What isPopCondMatched does: false unless every entry of m_entries holds a valid gimmick with data at 0x48/0x50, a
    // positive count at 0x58 and a set byte at 0xE2; then its flags at 0x142, or its BdatInfo's conditions
    // (GfGameManager event state, GfGameCond::isGameCond). gf_field_locator's LocatorGimmick, LocatorGimmickEnemyWave
    // and GfGmkLocator call it.
    bool isPopCondMatched() const;
    // What getBindedEnemyNum does: its data's m_enemyEnd minus m_enemyBegin: how many enemies getBindedEnemy can return
    unsigned int getBindedEnemyNum() const;
    // What getBindedEnemy does: the GmkEnemy (0x1D8-byte element) at its data's m_enemyBegin plus index in the enemy
    // list of its list's create info (0x1B8), none when that list is missing or shorter
    GmkEnemy* getBindedEnemy(unsigned int index);
    // 2.0.0's symbols name it.
    void seqWaitToValidLinkGmkList(float dt);
    // 2.0.0's symbols name them.
    void applyPopCondMatchedEnemies(bool);
    void reset();
    // 2.0.0's symbols name it.
    void seqWaitAccessing(float dt);
    gf::GF_OBJ_HANDLE* m_gob;  // 0x48: dispose destroys it unless it is -1 (the name is not the original's)
    float m_accessDistSq;  // 0x50: create squares the "0x7B" table's row 0 column 0x1E (the name is not the original's)
    unsigned char pad_54[0xc];
    GmkPhantom m_phantom;  // 0x60 (the name is not the original's)
    GmkAcc m_acc;  // 0xF0 (the name is not the original's)
    void (GmkEnemyWave::*m_seq)(float dt);  // 0x130: dispose clears it (the name is not the original's)
    bool m_isAccCounted;  // 0x140: create clears it after creating m_acc (the name is not the original's)
    // 0x141..0x145: flags the battle challenge (GmkBattleChallenge) reads and sets (the names are not the original's)
    bool m_isCleared;     // 0x141: seqWaveUpdate counts the waves up to the last one set
    bool m_isChallenge;   // 0x142: GmkBattleChallenge::create sets it
    bool m_isStarted;     // 0x143: GmkBattleChallenge::seqWaveStart sets it
    unsigned char pad_144;
    bool m_isPaused;      // 0x145: GmkBattleChallenge::suspendAll sets it
    unsigned char pad_146[0x2];
    mm::mtl::FixedVector<Entry, 32> m_entries;  // 0x148, size at 0x448 (the name is not the original's)
    // 0x450: the gimmick set's sealed stone its row names, taken by seqWaitToValidLinkGmkList (the name is not the original's)
    GmkSealedStone* m_sealedStone;
    GmkAcc m_secondAcc;  // 0x458 (the name is not the original's)
};
}  // namespace gmk

#endif
