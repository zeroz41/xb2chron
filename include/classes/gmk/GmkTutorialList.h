#ifndef CLASSES_GMK_GMKTUTORIALLIST_H
#define CLASSES_GMK_GMKTUTORIALLIST_H

#include "classes/gmk/GmkTutorial.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkTutorial; }
namespace gmk { class GmkTutorialGob; }

namespace gmk {
// table 0x7100B6D370
class GmkTutorialList : public ::gmk::TGmkList<gmk::GmkTutorial, gmk::GmkTutorial::BdatInfo, 1330926932u, 4u, gmk::GmkTutorialGob> {
public:
    virtual ~GmkTutorialList();  // slot 0
};
}  // namespace gmk

#endif
