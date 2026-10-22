#ifndef CLASSES_WND_GLOBALWIND_H
#define CLASSES_WND_GLOBALWIND_H

#include "classes/wnd/WindBlender.h"

namespace wnd { class UpdateInfo; }

namespace wnd {
// table 0x7100B81800; a blender (GlobalWindManager's constructor builds a WindBlender before storing this table,
// and update calls WindBlender::update on it): WindProbe::bindGlobalWind gives its blender this node
class GlobalWind : public WindBlender {
public:
    virtual void update(wnd::UpdateInfo const&);  // slot 0
};
}  // namespace wnd

#endif
