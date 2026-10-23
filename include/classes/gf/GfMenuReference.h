#ifndef CLASSES_GF_GFMENUREFERENCE_H
#define CLASSES_GF_GFMENUREFERENCE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIStr; }
namespace gf { class GfMenuReference; }
namespace gf { class GfMenuEnemyList; }
namespace gf { class GfMenuItemList; }

namespace gf {
// table 0x7100B5EF48
class GfMenuReference : public ::mm::mtl::PtrSingleton< ::gf::GfMenuReference> {
public:
    class REFLIST;
    // a route of the elemental combo the menu shows (8 bytes each, 7 of them; the names are not the original's)
    struct ElementComboRoot {
        unsigned int m_comboId;  // GfMenuElementComboAdapter::ReferenceRouteConverter's combo
        unsigned char pad_4[0x4];
    };
    virtual ~GfMenuReference();  // slot 0
    static void setReferenceString(ui::UIStr& text, unsigned short index);
    static unsigned int getReferenceDriverID(unsigned int index);
    static unsigned int getReferenceBladeID(unsigned int index);
    static unsigned int getReferenceZoneID();  // GfMenuZoneAdapter::ReferenceZoneConverter's zone
    static unsigned int getReferenceShopID();  // the shop the menu was opened for (GfMenuShopAdapter::ReferenceConverter)
    static unsigned int getReferenceWorldMapID();  // GfMenuWorldMapAdapter::ReferenceConverter's map
    // the number at an index, and its range (GfMenuGameAdapter::update_ReferenceNum)
    static int getReferenceNumber(unsigned int index);
    static int getReferenceNumberMin(unsigned int index);
    static int getReferenceNumberMax(unsigned int index);
    static const ElementComboRoot* getElementComboRootInfo(unsigned int route);  // a dummy past the 7th
    static int getElementComboRootCurrent();
    // the lists the link-jump menu shows (null without the singleton): its enemies and its items; clearLinkList
    // clears both (their slot 2)
    static void clearLinkList();
    static GfMenuEnemyList* getEnemyLinkList();
    static GfMenuItemList* getItemLinkList();  // the route the combo is on (GfMenuElementComboAdapter compares)
};
}  // namespace gf

#endif
