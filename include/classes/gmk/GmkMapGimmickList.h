#ifndef CLASSES_GMK_GMKMAPGIMMICKLIST_H
#define CLASSES_GMK_GMKMAPGIMMICKLIST_H

#include "classes/gmk/GmkMapGimmick.h"
#include "classes/gmk/GmkTrigger.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkMapGimmick; }
namespace gmk { class GmkTriggerGob; }
namespace gmk { class GmkMapGimmickGob; }

namespace gmk {
// table 0x7100B6DF28
class GmkMapGimmickList : public ::gmk::TGmkList< ::gmk::GmkMapGimmick, ::gmk::GmkMapGimmick::BdatInfo, 1196441933u, 2u, ::gmk::GmkMapGimmickGob> {
public:
    // 0x71005783E8 (2.0.0's symbols name it): builds TGmkList<GmkMapGimmick> and m_triggerList
    explicit GmkMapGimmickList(unsigned int updateGmkNumPerFrame);
    virtual ~GmkMapGimmickList();  // slot 0
    virtual gmk::AGmkBase* getInst(unsigned int) const;  // slot 6
    virtual void setUpdateGmkNumPerFrame(unsigned int);  // slot 8
    virtual void dispose();  // slot 10
    virtual void update(float);  // slot 11
    virtual bool updateImmediate();  // slot 12
    virtual void debugUpdateMmf();  // slot 13
    virtual void debugDraw() const;  // slot 14
    virtual void createGmk(void*);  // slot 16
    // the triggers of the map gimmicks, disposed and updated with them (the name is not the original's)
    TGmkList<GmkTrigger, GmkTrigger::BdatInfo, 1380405844u, 2u, GmkTriggerGob> m_triggerList;  // 0x230
};
}  // namespace gmk

#endif
