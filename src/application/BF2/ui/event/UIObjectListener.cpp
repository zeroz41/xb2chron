#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIGameListener.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UIEventCondition.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectListener.h"
#include "fw/UpdateInfo.h"
#include "ui/UIUtil.h"

namespace ui {

void UIObjectListener::reciveEvent(const EventData& event, unsigned int handle) {
    if (event.m_type == 2) {
        UIUtil::getObject(handle)->setTerm();
    }
}

}  // namespace ui
