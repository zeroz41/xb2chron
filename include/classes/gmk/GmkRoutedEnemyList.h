#ifndef CLASSES_GMK_GMKROUTEDENEMYLIST_H
#define CLASSES_GMK_GMKROUTEDENEMYLIST_H

#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkTrigger.h"
#include "classes/gmk/GmkEnemyList.h"

namespace gmk { class GmkRoutedEnemy; }
namespace gmk { class GmkRoutedEnemyGobCustom; }
namespace gmk { class GmkTriggerGob; }

namespace gmk {
// table 0x7100B6C168
class GmkRoutedEnemyList : public ::gmk::TGmkList< ::gmk::GmkRoutedEnemy, ::gmk::GmkEnemy::BdatInfo, 1296975186u, 8u, ::gmk::GmkRoutedEnemyGobCustom> {
public:
    explicit GmkRoutedEnemyList(unsigned int updateGmkNumPerFrame);
    virtual ~GmkRoutedEnemyList();  // slot 0
    virtual void setUpdateGmkNumPerFrame(unsigned int);  // slot 8
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
    virtual void dispose();  // slot 10
    virtual void update(float);  // slot 11
    virtual bool updateImmediate();  // slot 12
    virtual void debugUpdateMmf();  // slot 13
    virtual void debugDraw() const;  // slot 14
    virtual void createGmk(void*);  // slot 16

    GmkEnemyList::BdatInfo m_bdatInfo;  // 0x228: create needs its create() (the name is not the original's)
    unsigned char pad_234[0xc];
    // 0x240: dispose and the dtor dispose and destroy it (the name is not the original's)
    TGmkList<GmkTrigger, GmkTrigger::BdatInfo, 1380405844u, 2u, GmkTriggerGob> m_triggerList;
};
}  // namespace gmk

#endif
