#include "ui/UIStr.h"
#include "ui/UIUtil.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UITextManager.h"
#include "classes/ui/UITransform.h"
#include "classes/ui/UIUioLibrary.h"
#include "classes/fw/CommonResource.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Hash.h"
#include "string.h"
#include "mm/mtl/Vector.h"

namespace ui {

UIStr::UIStr() {
    init();
}

UIStr::UIStr(const UIStr& other) {
    init();
    copy(other);
}

// copy (0x7100694F68) is not here yet: identical once isValid is (it inlines it)

UIStr::UIStr(unsigned char* bdat, unsigned int id) {
    m_bufferSize = 0;
    m_text = nullptr;
    m_type = TYPE_NONE;
    m_ownerId = 0;
    if (bdat != nullptr && id != 0) {
        m_mstxt.m_file = UITextManager::sys()->registTextFile(bdat);
        m_mstxt.m_msgId = id;
        m_type = TYPE_MSTXT;
    }
}

void UIStr::setupMstxt(unsigned char* bdat, unsigned int id) {
    release();
    if (bdat != nullptr && id != 0) {
        m_mstxt.m_file = UITextManager::sys()->registTextFile(bdat);
        m_mstxt.m_msgId = id;
        m_type = TYPE_MSTXT;
    }
}

UIStr::UIStr(const char* text, bool allocated) {
    init();
    if (text == nullptr || *text == '\0') {
        return;
    }
    if (!allocated) {
        setupReference(text);
        return;
    }
    setupAllocated(text);
}

void UIStr::setupAllocated(const char* text) {
    allocate(text);
}

UIStr::~UIStr() {
    release();
}

void UIStr::release() {
    if (m_type == TYPE_ALLOCATED && m_text != nullptr && m_bufferSize != 0) {
        UIUtil::getProgAllocator()->deallocate(const_cast<char*>(m_text));
    }
    if (m_type == TYPE_MSTXT && m_mstxt.m_file != 0) {
        UITextManager::sys()->unregistTextFile(m_mstxt.m_file);
    }
    init();
}

const char* UIStr::c_str() const {
    if (m_type == TYPE_MSTXT) {
        if (isValidMstxt(m_mstxt)) {
            return UITextManager::sys()->getText(m_mstxt.m_file, m_mstxt.m_msgId);
        }
        return nullptr;
    } else if (m_type == TYPE_REFERENCE) {
        return m_text;
    } else if (m_type == TYPE_ALLOCATED) {
        return m_text != nullptr && m_bufferSize != 0 ? m_text : nullptr;
    }
    return nullptr;
}

// isValid (0x7100695434) is not here yet: 1 instruction apart (its TYPE_MSTXT answer goes through w8)

// size (0x710069549C) is not here yet: identical once isValid is (it inlines it)

// allocate (0x71006955B8) is not here yet: 4 words apart (release's stores are scheduled differently);
// deepcopy (0x71006956B0), identical when allocate and isValid are in this file to inline, waits for them

// compare (0x7100695760) is not here yet: identical once isValid is (it inlines it)

unsigned short UIStr::getStyle() const {
    if (m_type == TYPE_MSTXT && isValidMstxt(m_mstxt)) {
        return UITextManager::sys()->getStyle(m_mstxt.m_file, m_mstxt.m_msgId);
    }
    return 0;
}

unsigned char* UIStr::getMsgFP() const {
    if (m_type == TYPE_MSTXT) {
        return UITextManager::sys()->getTextFile(m_mstxt.m_file);
    }
    return nullptr;
}

unsigned int UIStr::getMsgID() const {
    if (m_type == TYPE_MSTXT) {
        return m_mstxt.m_msgId;
    }
    return 0;
}

UITransform::UITransform() {
    m_pos.x = 0;
    m_pos.y = 0;
    m_scale.x = 1.0f;
    m_scale.y = 1.0f;
    m_rotation = 0.0f;
    m_changed = false;
}

UITransform::~UITransform() {
    ;  // the original stores the table; clang drops the store for an empty body
}

void UITransform::syncParent() {}

void UITransform::setPos(short x, short y) {
    if (m_pos.x != x || m_pos.y != y) {
        m_changed = true;
    }
    m_pos.x = x;
    m_pos.y = y;
}

void UITransform::setScale(float x, float y) {
    if (m_scale.x != x || m_scale.y != y) {
        m_changed = true;
    }
    m_scale.x = x;
    m_scale.y = y;
}

UIUioLibrary::UIUioLibrary() {}

UIUioLibrary::~UIUioLibrary() {
    reset();
}
}  // namespace ui

// instantiated for ui::UIUioLibrary::update (not written yet)
template mm::mtl::Vector<ui::UIUioLibrary::UioInfo>::iterator mm::mtl::Vector<ui::UIUioLibrary::UioInfo>::erase(ui::UIUioLibrary::UioInfo*);

namespace ui {

void UIUioLibrary::reset() {
    if (m_uios.capacity() != 0) {
        for (mm::mtl::Vector<UioInfo>::iterator it = m_uios.begin(); it != m_uios.end(); ++it) {
            if (it->m_resource != nullptr) {
                it->m_resource->release();
                it->m_resource = nullptr;
            }
        }
        m_uios.destroy();
    }
}

// update (0x7100695DF0) is not here yet: 6 words apart (the latch's ++it is placed differently)

bool UIUioLibrary::add(const char* name) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    if (m_uios.capacity() == 0) {
        m_uios.setAllocator(UIUtil::getProgAllocator());
        m_uios.reserve(8, 8);
    } else {
        for (mm::mtl::Vector<UioInfo>::iterator it = m_uios.begin(); it != m_uios.end(); ++it) {
            if (it->m_hash == hash) {
                return true;
            }
        }
    }
    mm::mtl::FixStr<128> path;
    UIUtil::makeMenuUIOFileName(path, name);
    UioInfo info;
    info.m_hash = mm::mtl::hashStrCrc(name);
    info.m_resource = fw::CommonResource::request(UIUtil::getResourceAllocator(), path.m_str, 10, false);
    if (info.m_resource != nullptr) {
        m_uios.push_back(info);
    }
    return true;
}

}  // namespace ui
