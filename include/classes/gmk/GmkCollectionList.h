#ifndef CLASSES_GMK_GMKCOLLECTIONLIST_H
#define CLASSES_GMK_GMKCOLLECTIONLIST_H

#include "classes/gmk/GmkCollection.h"
#include "classes/gmk/IGmkList.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkCollection; }
namespace gmk { class GmkCollectionGob; }

namespace gmk {
// table 0x7100B6C8E8
class GmkCollectionList : public ::gmk::TGmkList< ::gmk::GmkCollection, ::gmk::GmkCollection::BdatInfo, 1413696579u, 5u, ::gmk::GmkCollectionGob> {
public:
    virtual ~GmkCollectionList();  // slot 0
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
};
}  // namespace gmk

#endif
