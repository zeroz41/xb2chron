#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_HEADERLISTENER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_HEADERLISTENER_H

#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62128
class GfMenuObjEvTheater::HeaderListener : public ::ui::UIObjectListener {
public:
    virtual ~HeaderListener() {}  // slot 0
    // slot 2: fades the header in on 0x21 and out on 0x22 (once each, by m_shown); 0x103 shows the selected list
    // entry's text in TXT_header_item, 0x104 hides it
    virtual void reciveEvent(ui::EventData const&, unsigned int);
    // the names of the fields are not the original's
    int m_shown;  // 1 once the header faded in, 0 after it faded out or on event 1
    unsigned char pad_10[0x10];
    GfMenuObjEvTheater* m_owner;
};
}  // namespace gf

#endif
