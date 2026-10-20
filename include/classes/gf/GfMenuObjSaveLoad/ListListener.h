#ifndef CLASSES_GF_GFMENUOBJSAVELOAD_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJSAVELOAD_LISTLISTENER_H

namespace ui { class EventData; }

namespace gf { namespace GfMenuObjSaveLoad {
// table 0x7100B646A0
class ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}}  // namespace gf::GfMenuObjSaveLoad

#endif
