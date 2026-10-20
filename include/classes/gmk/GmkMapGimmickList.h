#ifndef CLASSES_GMK_GMKMAPGIMMICKLIST_H
#define CLASSES_GMK_GMKMAPGIMMICKLIST_H

#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkMapGimmick; }
namespace gmk { class GmkMapGimmickGob; }

namespace gmk {
// table 0x7100B6DF28
class GmkMapGimmickList : public ::gmk::TGmkList<gmk::GmkMapGimmick, gmk::GmkMapGimmick::BdatInfo, 1196441933u, 2u, gmk::GmkMapGimmickGob> {
public:
    virtual ~GmkMapGimmickList();  // slot 0
    virtual void getInst(unsigned int) const;  // slot 6
    virtual void setUpdateGmkNumPerFrame(unsigned int);  // slot 8
    virtual void dispose();  // slot 10
    virtual void update(float);  // slot 11
    virtual void updateImmediate();  // slot 12
    virtual void debugUpdateMmf();  // slot 13
    virtual void debugDraw() const;  // slot 14
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
