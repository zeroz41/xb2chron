#ifndef CLASSES_GMK_GMKNPCLIST_H
#define CLASSES_GMK_GMKNPCLIST_H

#include "classes/gmk/GmkNpc.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkNpc; }
namespace gmk { class GmkNpcGob; }

namespace gmk {
// table 0x7100B6C230
class GmkNpcList : public ::gmk::TGmkList< ::gmk::GmkNpc, ::gmk::GmkNpc::BdatInfo, 4411470u, 4u, ::gmk::GmkNpcGob> {
public:
    explicit GmkNpcList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
    virtual ~GmkNpcList();  // slot 0
    virtual void createGmk(void*);  // slot 16
    virtual void disposeGmk();  // slot 17
};
}  // namespace gmk

#endif
