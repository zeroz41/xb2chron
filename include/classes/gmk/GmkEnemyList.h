#ifndef CLASSES_GMK_GMKENEMYLIST_H
#define CLASSES_GMK_GMKENEMYLIST_H

#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkEnemy; }
namespace gmk { class GmkEnemyGob; }

namespace gmk {
// table 0x7100B6C050
class GmkEnemyList : public ::gmk::TGmkList< ::gmk::GmkEnemy, ::gmk::GmkEnemy::BdatInfo, 1296387653u, 5u, ::gmk::GmkEnemyGob> {
public:
    virtual ~GmkEnemyList();  // slot 0
    virtual void getInst(unsigned int) const;  // slot 6
    virtual void setUpdateGmkNumPerFrame(unsigned int);  // slot 8
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
    virtual void dispose();  // slot 10
    virtual void update(float);  // slot 11
    virtual void updateImmediate();  // slot 12
    virtual void debugUpdateMmf();  // slot 13
    virtual void debugDraw() const;  // slot 14
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
