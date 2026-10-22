#ifndef CLASSES_UI_UILISTINFO_H
#define CLASSES_UI_UILISTINFO_H

#include "classes/ui/UIListInfoBase.h"
#include "mm/mtl/Vector.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace ui {
// a template: 11 instances in the module
template <typename T0>
class UIListInfo : public ::ui::UIListInfoBase {
public:
    UIListInfo() : m_list(), m_dummy(), m_changed(false) {}
    virtual ~UIListInfo();  // slot 0
    virtual void clear();  // slot 2
    virtual void setup(mm::mtl::IAllocator* allocator, const ui::UIListInfoBase::SetupParam& param);  // slot 4
    mm::mtl::Vector<T0> m_list;
    // what a read past the end gets (GfMenuCharDataAdapter::createFromEnemyList); the name is not the original's
    T0 m_dummy;
    bool m_changed;  // set by addContents and sort (1.0.0 has them); the name is not the original's
};

template <typename T0>
UIListInfo<T0>::~UIListInfo() {
    if (m_list.capacity() != 0) {
        m_list.destroy();
    }
}

template <typename T0>
void UIListInfo<T0>::clear() {
    m_list.clear();
    UIListInfoBase::clear();
}

template <typename T0>
void UIListInfo<T0>::setup(mm::mtl::IAllocator* allocator, const ui::UIListInfoBase::SetupParam& param) {
    UIListInfoBase::setup(param);
    if (!isValid()) {
        return;
    }
    if (m_list.size() != 0) {
        m_list.destroy();
    }
    unsigned int count = getPageColumnSize() * getPageRowSize();
    if (count < 8) {
        count = 8;
    }
    m_list.setAllocator(allocator);
    m_list.reserve(count, 8);  // setup's allocation asks for 8
}
}  // namespace ui

#endif
