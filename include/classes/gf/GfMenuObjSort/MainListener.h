#ifndef CLASSES_GF_GFMENUOBJSORT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJSORT_MAINLISTENER_H

namespace ui { class EventData; }

namespace gf { namespace GfMenuObjSort {
// table 0x7100B64A40
class MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}}  // namespace gf::GfMenuObjSort

#endif
