#ifndef CLASSES_GF_GFMENUOBJCOMPASS_H
#define CLASSES_GF_GFMENUOBJCOMPASS_H

#include "classes/gf/GfMenuObject.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B61680
class GfMenuObjCompass : public ::gf::GfMenuObject {
public:
    class MainListener;
    // what addLocator is given (8 bytes, copied into the icon as one); the names are not the original's
    struct LocatorParam {
        unsigned short m_id;    // GfMenuLocation::getLocatorData's first argument; also lowers the icon's priority
        unsigned short m_type;  // its second (update shows type 4 with IMG_icon_npc, types 0-1 also behind)
        int m_count;            // update shows the icon while it is 0 or not below its locator's count
    };
    // an icon addLocator duplicates from LAY_icon (0x10 bytes); the names are not the original's
    struct IconObj {
        unsigned int m_handle;  // the duplicated LAY_icon
        LocatorParam m_param;
        int m_lostFrames;       // 2 when found; update hides the icon once its locator stays lost that long
    };
    GfMenuObjCompass(unsigned int handle);
    virtual ~GfMenuObjCompass();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // the open (0x21) and close (0x22) events for the compass attached under 0x42
    static void open();
    static void close();
    static mm::mtl::FixedVector<IconObj, 32> m_IconObjList;
};
}  // namespace gf

#endif
