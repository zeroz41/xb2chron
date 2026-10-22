#ifndef CLASSES_WND_WINDBLENDER_H
#define CLASSES_WND_WINDBLENDER_H

#include "classes/wnd/WindNode.h"

namespace wnd { class UpdateInfo; }

namespace wnd {
// table 0x7100B81850; its winds go from the previous node's to the current one's over the change's time
class WindBlender : public WindNode {
public:
    WindBlender();
    virtual void update(wnd::UpdateInfo const&);  // slot 0
    void changeNode(const WindNode* pNode, float time);
    void setNode(const WindNode* pNode);

    const WindNode* m_pNode;  // what changeNode and setNode set
    const WindNode* m_pPrevNode;  // the node changeNode leaves; update drops it once the change is done
    float m_rate;  // how far the change has gone: 0 to 1
    float m_time;  // changeNode's: how long the change takes
};
}  // namespace wnd

#endif
