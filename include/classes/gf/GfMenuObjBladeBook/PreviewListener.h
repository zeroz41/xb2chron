#ifndef CLASSES_GF_GFMENUOBJBLADEBOOK_PREVIEWLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADEBOOK_PREVIEWLISTENER_H

#include "classes/gf/GfMenuObjBladeBook.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FE50
class GfMenuObjBladeBook::PreviewListener {
public:
    virtual ~PreviewListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
