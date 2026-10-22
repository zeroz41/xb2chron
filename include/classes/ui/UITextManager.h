#ifndef CLASSES_UI_UITEXTMANAGER_H
#define CLASSES_UI_UITEXTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/fw/PointerMap.h"
#include "mm/mtl/FixedVector.h"

namespace ui { class UITextManager; }

namespace ui {
// table 0x7100B75558; the message tables the UI reads its texts from, each registered once by its sheet's name and
// counted
class UITextManager : public ::mm::mtl::PtrSingleton< ::ui::UITextManager> {
public:
    // one registered table (0xC bytes; the names are not the original's)
    struct FileInfo {
        unsigned int m_hash;    // mm::mtl::hashStrCrc of its sheet's name
        unsigned int m_handle;  // its UITextFile's in m_textFiles
        unsigned int m_count;   // the registrations unregistTextFile has not undone
    };
    UITextManager();
    virtual ~UITextManager();  // slot 0
    // the handle of the table's UITextFile (another registration of a table already in counts it); 0 when the map
    // is full
    unsigned int registTextFile(unsigned char* data);
    void unregistTextFile(unsigned int handle);  // the file goes with its last registration
    void reloadAll();
    const char* getText(unsigned int handle, unsigned int id) const;  // null for an unknown file
    unsigned short getStyle(unsigned int handle, unsigned int id) const;  // 0 for an unknown file
    unsigned char* getTextFile(unsigned int handle) const;  // the file's table, null for an unknown file

    mm::mtl::FixedVector<FileInfo, 256> m_files;  // the name is not the original's
    fw::PointerMap m_textFiles;  // the UITextFiles, by handle (the name is not the original's)
};
}  // namespace ui

#endif
