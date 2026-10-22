#include "classes/ui/UITextManager.h"
#include "classes/ui/UITextFile.h"
#include "plugin/Bdat.h"
#include "mm/mtl/Hash.h"
#include "ui/UIUtil.h"

namespace ui {

UITextManager::UITextManager() {
    m_textFiles.reserve(UIUtil::getProgAllocator(), 0x100);
}

UITextManager::~UITextManager() {
    for (FileInfo* it = m_files.begin(); it != m_files.end(); ++it) {
        UITextFile* file = static_cast<UITextFile*>(m_textFiles.getPtr(it->m_handle));
        if (file != nullptr) {
            delete file;
        }
    }
    m_files.clear();
}

unsigned int UITextManager::registTextFile(unsigned char* data) {
    unsigned int hash = mm::mtl::hashStrCrc(Bdat::getSheetName(data));
    for (FileInfo* it = m_files.begin(); it != m_files.end(); ++it) {
        if (it->m_hash == hash) {
            it->m_count++;
            return it->m_handle;
        }
    }
    unsigned int handle = m_textFiles.regist(UITextFile::create(data));
    if (handle != 0) {
        FileInfo info;
        info.m_hash = hash;
        info.m_handle = handle;
        info.m_count = 1;
        m_files.push_back(info);
    }
    return handle;
}

// unregistTextFile (0x710068B38C) is not written yet: the candidate is not identical (two instructions in
// the inlined FixedVector::erase are scheduled the other way round; see the worker report)

void UITextManager::reloadAll() {
    for (FileInfo* it = m_files.begin(); it != m_files.end(); ++it) {
        UITextFile* file = static_cast<UITextFile*>(m_textFiles.getPtr(it->m_handle));
        if (file != nullptr) {
            file->reload();
        }
    }
}

const char* UITextManager::getText(unsigned int handle, unsigned int id) const {
    UITextFile* file = static_cast<UITextFile*>(m_textFiles.getPtr(handle));
    if (file != nullptr) {
        return file->getText(id);
    }
    return nullptr;
}

unsigned short UITextManager::getStyle(unsigned int handle, unsigned int id) const {
    UITextFile* file = static_cast<UITextFile*>(m_textFiles.getPtr(handle));
    if (file != nullptr) {
        return file->getStyle(id);
    }
    return 0;
}

unsigned char* UITextManager::getTextFile(unsigned int handle) const {
    UITextFile* file = static_cast<UITextFile*>(m_textFiles.getPtr(handle));
    if (file != nullptr) {
        return file->m_data;
    }
    return nullptr;
}

}  // namespace ui
