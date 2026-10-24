#ifndef CLASSES_GMK_GMKROUTEDNPCLIST_H
#define CLASSES_GMK_GMKROUTEDNPCLIST_H

#include "classes/gmk/GmkNpc.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkRouteGob; }
namespace gmk { class GmkRoutedNpc; }

namespace gmk {
// table 0x7100B6DCB8
class GmkRoutedNpcList : public ::gmk::TGmkList< ::gmk::GmkRoutedNpc, ::gmk::GmkNpc::BdatInfo, 1129336402u, 6u, ::gmk::GmkRouteGob> {
public:
    explicit GmkRoutedNpcList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
    virtual ~GmkRoutedNpcList();  // slot 0
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
    virtual void createGmk(void*);  // slot 16
    virtual void disposeGmk();  // slot 17
};
}  // namespace gmk

#endif
