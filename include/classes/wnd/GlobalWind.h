#ifndef CLASSES_WND_GLOBALWIND_H
#define CLASSES_WND_GLOBALWIND_H

#include "classes/wnd/WindBlender.h"

namespace wnd { class UpdateInfo; }

namespace wnd {
// table 0x7100B81800; a blender (GlobalWindManager's constructor builds a WindBlender before storing this table,
// and update calls WindBlender::update on it): WindProbe::bindGlobalWind gives its blender this node
class GlobalWind : public WindBlender {
public:
    GlobalWind() : m_pWind(nullptr), m_pPrevWind(nullptr) {}
    virtual void update(wnd::UpdateInfo const&);  // slot 0
    // the node to blend to next (GlobalWindManager::setCurrentWind): the current one stays the previous while
    // they were the same; the name is not the original's
    void setWind(WindNode* pWind) {
        if (m_pWind == m_pPrevWind) {
            m_pPrevWind = m_pWind;
        }
        m_pWind = pWind;
    }

    WindNode* m_pWind;  // setWind's; update updates it; the name is not the original's
    WindNode* m_pPrevWind;  // update updates it first; the name is not the original's
};
}  // namespace wnd

#endif
