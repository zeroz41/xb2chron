#ifndef WND_RESWIND_H
#define WND_RESWIND_H

#include "wnd/AABB.h"
#include "wnd/Array.h"

namespace wnd { class ResAreaWind; }

namespace wnd {
// a wind world's resource: what fw::WindManager::buildWorld builds a world from
class ResWind {
public:
    AABB aabb;  // the space the world covers (fw::WindFactory::createWindResource's corners)
    Array<ResAreaWind> areaWinds;  // buildWorld makes an AreaWind of each (0x40 bytes apiece)
};
}  // namespace wnd

#endif
