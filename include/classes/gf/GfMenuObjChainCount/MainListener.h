#ifndef CLASSES_GF_GFMENUOBJCHAINCOUNT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINCOUNT_MAINLISTENER_H

namespace ui { class EventData; }

namespace gf { namespace GfMenuObjChainCount {
// table 0x7100B60CF0
class MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}}  // namespace gf::GfMenuObjChainCount

#endif
