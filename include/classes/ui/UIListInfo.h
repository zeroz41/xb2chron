#ifndef CLASSES_UI_UILISTINFO_H
#define CLASSES_UI_UILISTINFO_H

#include "classes/ui/UIListInfoBase.h"
#include "mm/mtl/Vector.h"
#include <algorithm>
#include <functional>

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
    void addContents(const T0& contents);
    // orders the list by a comparator (1.0.0 has it; GfMenuItemList::sort builds the comparators)
    void sort(std::function<bool(const T0&, const T0&)> compare);
    // the content at an index, m_dummy past the end; the name is not the original's (1.0.0 has addContents)
    T0& getContents(unsigned int index) {
        T0* contents = &m_dummy;
        if (index < m_list.size()) {
            contents = &m_list[index];
        }
        return *contents;
    }
    // the same on a const list (GfMenuObjCommonText::openGetItem copies a const list's contents)
    const T0& getContents(unsigned int index) const {
        const T0* contents = &m_dummy;
        if (index < m_list.size()) {
            contents = &m_list[index];
        }
        return *contents;
    }
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

template <typename T0>
void UIListInfo<T0>::addContents(const T0& contents) {
    m_list.push_back(contents);
    addSize(1);
    m_changed = true;
}

template <typename T0>
void UIListInfo<T0>::sort(std::function<bool(const T0&, const T0&)> compare) {
    if (m_list.size() == 0) {
        return;
    }
    std::sort(m_list.begin(), m_list.end(), compare);
    m_changed = true;
}

}  // namespace ui

#endif
