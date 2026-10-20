#ifndef CLASSES_GF_GFMENUOBJTARGETINFO_SYMBOLLISTENER_H
#define CLASSES_GF_GFMENUOBJTARGETINFO_SYMBOLLISTENER_H

#include "classes/gf/GfMenuObjTargetInfo.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64C70
class GfMenuObjTargetInfo::SymbolListener {
public:
    virtual ~SymbolListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
