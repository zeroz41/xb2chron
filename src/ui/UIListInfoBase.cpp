#include "classes/ui/UIListInfoBase.h"

namespace ui {

UIListInfoBase::UIListInfoBase()
    : m_param(), m_size(0), m_index(0), m_rowOffset(0), m_columnOffset(0), m_changed(false) {}

UIListInfoBase::~UIListInfoBase() {
    ;  // stores the table (a statement the build compiles away)
}

void UIListInfoBase::setup(const SetupParam& param) {
    m_param = param;
    if (m_param.m_columnSize == 0) {
        m_param.m_columnSize = m_param.m_pageColumnSize;
    }
    clear();
    setIndex(param.m_index);
}

// setIndex (0x710067BF90) is not written yet: the candidate is not identical (see the worker report)

void UIListInfoBase::clear() {
    m_changed = false;
    m_size = 0;
    m_index = 0;
    m_rowOffset = 0;
    m_columnOffset = 0;
}

bool UIListInfoBase::isValid() const {
    return m_param.m_pageColumnSize != 0 && m_param.m_pageRowSize != 0;
}

int UIListInfoBase::getSize() const {
    return m_size;
}

unsigned int UIListInfoBase::getColumnSize() const {
    if (m_size == 0) {
        return 0;
    }
    return m_param.m_columnSize;
}

unsigned int UIListInfoBase::getPageRowSize() const {
    if (!isValid()) {
        return 0;
    }
    return m_param.m_pageRowSize;
}

unsigned int UIListInfoBase::getPageColumnSize() const {
    if (!isValid()) {
        return 0;
    }
    return m_param.m_pageColumnSize;
}

void UIListInfoBase::update() {
    m_changed = false;
}

void UIListInfoBase::addSize(unsigned int count) {
    m_size += count;
}

void UIListInfoBase::subSize(unsigned int count) {
    if (count == 0 || m_size == 0) {
        return;
    }
    int size = m_size - count;
    if (size < 0) {
        size = 0;
    }
    m_size = size;
    if (size == 0 || size <= (int)getPageSize()) {
        m_rowOffset = 0;
        m_columnOffset = 0;
    } else {
        if (m_rowOffset != 0 && getRowSize() > getPageRowSize()) {
            unsigned int last = (m_size - 1) / getPageColumnSize() - (getPageRowSize() - 1);
            if (m_rowOffset > last) {
                m_rowOffset = last;
            }
        }
        if (m_columnOffset != 0 && m_param.m_columnSize > getPageColumnSize()) {
            unsigned int last = (m_size - 1) / getPageRowSize() - (getPageColumnSize() - 1);
            if (m_columnOffset > last) {
                m_columnOffset = last;
            }
        }
    }
    if (m_index >= m_size) {
        setIndex(m_size - 1);
    }
}

unsigned int UIListInfoBase::getPageSize() const {
    return isValid() ? m_param.m_pageRowSize * m_param.m_pageColumnSize : 0;
}

unsigned int UIListInfoBase::getRowSize() const {
    if (m_size == 0) {
        return 0;
    }
    unsigned int rows = m_size / m_param.m_columnSize;
    if (m_size % m_param.m_columnSize != 0) {
        rows++;
    }
    return rows;
}

unsigned int UIListInfoBase::getIndex(bool page) const {
    if (m_size == 0) {
        return 0;
    }
    if (!page) {
        return m_index;
    }
    return m_index - (m_columnOffset + m_rowOffset * m_param.m_pageColumnSize);
}

unsigned int UIListInfoBase::getPageIndex(unsigned int index) const {
    if (!isValid() || m_size == 0) {
        return 0;
    }
    unsigned int columns = getPageColumnSize();
    unsigned int row = index / columns;
    unsigned int top = m_rowOffset + row;
    return index % columns + m_columnOffset + top * columns;
}

unsigned int UIListInfoBase::getRowOffset() const {
    if (!isValid() || m_size == 0) {
        return 0;
    }
    return m_rowOffset;
}

}  // namespace ui
