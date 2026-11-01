#ifndef CLASSES_GMK_GMKSALVAGE_H
#define CLASSES_GMK_GMKSALVAGE_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "mm/mtl/FixedVector.h"
#include <bitset>

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
class GmkSalvageLocator;
// table 0x7100B6C990
class GmkSalvage : public ::gmk::AGmkBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x710063195C (zero-filled); initGmkBdatInfo fills it
    class BdatInfo {
    public:
        // inline: TGmkList::initGmkBdatInfo has no call of it
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
        }
        bool isCondMatched() const;
        unsigned short m_condition;  // the row's "Condition" (a GfGameCond id; 0: none)
    };
    // what m_createInfo.m_data points at for a salvage gimmick (getGmkFormPc reads it; the struct and field names
    // are not the original's)
    struct Data {
        unsigned char pad_0[8];
        int m_formPcIdx;  // 0x8: its formation's element in the TGmkFormPc list
        int pad_c;        // 0xc: getGmkFormPc gives none unless it exceeds m_formPcIdx
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // what the last raffle drew (createRaffle fills it, disposeRaffle resets it; GfGameSalvage::getRaffleResult reads
    // it); the field names are not the original's
    class RaffleResult {
    public:
        // an enemy the raffle drew: its id (0: none) and its level offset (isPowerfullEnemyExist adds it to the id's
        // ChrEnArrange level)
        class Enemy {
        public:
            Enemy() : m_id(0), pad_2(0) {}
            unsigned short m_id;
            unsigned char pad_2;
            signed char m_lvOffset;
        };
        RaffleResult() {
            m_dropIds[0] = -1;
            m_dropIds[1] = -1;
            m_dropIds[2] = -1;
            m_tboxIds[0] = -1;
            m_tboxIds[1] = -1;
            m_tboxIds[2] = -1;
            m_enemyIds[0] = -1;
            m_enemyIds[1] = -1;
            m_enemyIds[2] = -1;
        }
        bool isPowerfullEnemyExist() const;

        // which of the three locators of each kind (m_dropLocators, m_tboxLocators, m_enemyLocators) the raffle
        // drew, and what for each (seqUpdatePopDepop tests m_enemyDrawn's bit for each enemy locator)
        std::bitset<3> m_dropDrawn;
        int m_dropIds[3];
        std::bitset<3> m_tboxDrawn;
        int m_tboxIds[3];
        std::bitset<3> m_enemyDrawn;
        int m_enemyIds[3];
        Enemy m_enemies[3];
    };
    // the stores Vector<GmkSalvage>::resize (construct_n) makes in each element
    GmkSalvage()
        : m_seq(nullptr), m_gob(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_popDistSq(0.0f), pad_64(0.0f), m_eventLocator(nullptr),
          pad_d0(false), pad_d1(false), pad_128(1), pad_129(0) {}
    virtual ~GmkSalvage();  // slot 0
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its kind (TGmkList<GmkSalvage>::getGmkType returns 31; GmkSet::createGmkLists puts GmkSalvageList at index 31; the
    // name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(31);
    // its party formation gimmick: the GmkSet's TGmkFormPc list's element at the data's index (GfGameSalvage::applyPartyForm)
    gmk::AGmkBase* getGmkFormPc() const;
    // pops the treasures the salvage's raffle drew (GfGameSalvage::execPop)
    void popByRaffleResult();
    // ends what the last raffle placed (createRaffle and dispose call it)
    void disposeRaffle(bool);
    // the step create installs
    void seqValidateGmkSalvageLocatorDetails(float);

    // 0x48: the sequence step update runs (create installs seqValidateGmkSalvageLocatorDetails, dispose clears it)
    void (GmkSalvage::*m_seq)(float);
    // 0x58: its object (dispose destroys it unless it is -1; seqUpdatePopDepop creates it within m_popDistSq)
    gf::GF_OBJ_HANDLE* m_gob;
    float m_popDistSq;  // 0x60: Bdat 0x7B's column 0x1E squared (create)
    float pad_64;       // 0x64: Bdat 0x7B's column 0x3A squared (create)
    // 0x68, 0x88, 0xB0: the locators the raffle placed, by kind: disposeRaffle clears the first's elements' byte
    // 0x58 and disposes their drop item emitters, clears the second's m_isAccessed and disposes their objects,
    // disposes the third's objects (the names are not the original's)
    mm::mtl::FixedVector<GmkSalvageLocator*, 3> m_dropLocators;
    mm::mtl::FixedVector<GmkSalvageLocator*, 3> m_tboxLocators;
    // 0xA8: the locator the salvage's event happens at (seqValidateGmkSalvageLocatorDetails keeps the first of its
    // kind; GfGameSalvage::getEventOrigin reads its matrix; dispose clears it; the name is not the original's)
    GmkSalvageLocator* m_eventLocator;
    mm::mtl::FixedVector<GmkSalvageLocator*, 3> m_enemyLocators;
    bool pad_d0;  // disposeRaffle does its work only when it is set, then clears it and pad_d1
    bool pad_d1;  // seqUpdatePopDepop goes through m_enemyLocators only when it is set
    RaffleResult m_raffleResult;  // 0xD8
    unsigned char pad_128;  // 1 when constructed
    // GmkSalvageLocator::syncDepopTboxes sets it to 1, its dispose sets it too; update then disposes the objects of
    // m_tboxLocators and clears it
    unsigned char pad_129;
    // 0x12A..0x130: tail padding (the copy constructor copies up to 0x12A); size 0x130: TGmkList<GmkSalvage>::getInst's
    // stride
};
}  // namespace gmk

#endif
