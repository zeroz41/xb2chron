#ifndef CLASSES_UI_UIEVENTCONDITION_H
#define CLASSES_UI_UIEVENTCONDITION_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace ui {
// table none (its derived classes')
class UIEventCondition : public ::mm::mtl::ReferenceObject {
public:
    UIEventCondition(unsigned int userValue0, unsigned int userValue1)
        : m_userValue0(userValue0), m_userValue1(userValue1) {
        m_RefCount = 1;  // its creator holds the first reference
    }
    virtual ~UIEventCondition() {}  // slot 0
    virtual int update() = 0;  // slot 2: the event the condition raises, 0 for none
    virtual int getArg() const { return 0; }  // slot 3
    // the creator's values, which UIEventManager::update passes on with each event the condition raises
    unsigned int m_userValue0;
    unsigned int m_userValue1;
    UIEventCondition* m_next;  // UIEventManager::addCondition links an object's conditions through it
};
}  // namespace ui

#endif
