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
    // the collection points' map row: GmkCollectionList::create reads it (BDAT 0x5D, the current map's row) before
    // anything else (the field names are not the original's; "m_repoptime" is the column it reads)
    class BdatInfo {
    public:
        BdatInfo() : m_mapId(-1), m_repopTime(1) {}
        bool create();
        int m_mapId;  // the map's row, -1 when it has none
        unsigned char m_repopTime;  // its "m_repoptime"
    };
    explicit GmkCollectionList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
    virtual ~GmkCollectionList();  // slot 0
    virtual void create(gmk::IGmkList::CreateInfo const&);  // slot 9
    BdatInfo m_bdatInfo;  // 0x228 (the name is not the original's)
};
}  // namespace gmk

#endif
