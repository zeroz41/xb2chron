#ifndef CLASSES_GMK_GMKENEMYLIST_H
#define CLASSES_GMK_GMKENEMYLIST_H

#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkTrigger.h"
#include "classes/gmk/GmkEnemyWaveList.h"

namespace gmk { class GmkEnemy; }
namespace gmk { class GmkEnemyGob; }
namespace gmk { class GmkTriggerGob; }

namespace gmk {
// table 0x7100B6C050
class GmkEnemyList : public ::gmk::TGmkList< ::gmk::GmkEnemy, ::gmk::GmkEnemy::BdatInfo, 1296387653u, 5u, ::gmk::GmkEnemyGob> {
public:
    // the map's enemy display settings (1.0.0 names create); the field names are not the original's: the columns
    // create reads into them
    class BdatInfo {
    public:
        // out of line (0x7100587350): reads the current map's row; false when the map has none
        // the constructor's defaults (GmkEnemyList's constructor stores them)
        BdatInfo() : m_row(-1), m_dispR(100), m_dispH(50), m_releaseR(10), m_releaseH(5), m_repopTime(3) {}
        bool create();
        int m_row;  // 0x0
        unsigned char m_dispR;  // 0x4: "ene_disp_r"
        unsigned char m_dispH;  // 0x5: "ene_disp_h"
        unsigned char m_releaseR;  // 0x6: "ene_release_r"
        unsigned char m_releaseH;  // 0x7: "ene_release_h"
        unsigned char m_repopTime;  // 0x8: "e_repoptime"
    };
    explicit GmkEnemyList(unsigned int);
    virtual ~GmkEnemyList();  // slot 0
    // slot 6: weak, the same body as TGmkList's (index * sizeof(GmkEnemy) 0x1d8)
    virtual gmk::AGmkBase* getInst(unsigned int index) const { return TGmkList::getInst(index); }
    virtual void setUpdateGmkNumPerFrame(unsigned int);  // slot 8
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
    virtual void dispose();  // slot 10
    virtual void update(float);  // slot 11
    virtual bool updateImmediate();  // slot 12
    virtual void debugUpdateMmf();  // slot 13
    virtual void debugDraw() const;  // slot 14
    virtual void createGmk(void*);  // slot 16
    BdatInfo m_bdatInfo;  // 0x228 (the name is not the original's)
    unsigned char pad_234[0xc];
    // the destructor's TGmkList<GmkTrigger> D2 at 0x240 (the name is not the original's)
    TGmkList<GmkTrigger, GmkTrigger::BdatInfo, 1380405844u, 2u, GmkTriggerGob> m_triggerList;
    GmkEnemyWaveList m_waveList;  // 0x470: the constructor builds it with -1 (the name is not the original's)
    void* pad_8d0;  // 0x8d0: the constructor clears it (sizeof 0x8e0: GmkSet::createGmkLists's new)
};
}  // namespace gmk

#endif
