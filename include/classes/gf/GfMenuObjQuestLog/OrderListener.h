#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_ORDERLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_ORDERLISTENER_H

#include "classes/gf/GfMenuObjQuestLog.h"

namespace gf {
// table 0x7100B64538
class GfMenuObjQuestLog::OrderListener {
public:
    virtual ~OrderListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
