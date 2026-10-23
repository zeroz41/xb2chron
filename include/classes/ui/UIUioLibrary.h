#ifndef CLASSES_UI_UIUIOLIBRARY_H
#define CLASSES_UI_UIUIOLIBRARY_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Vector.h"

namespace ui { class UIUioLibrary; }
namespace fw { class CommonResource; }
namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B75838; the menu UIO files add requested, by their name's hash (UIMotionLibrary's twin)
class UIUioLibrary : public ::mm::mtl::PtrSingleton< ::ui::UIUioLibrary> {
public:
    // one UIO file (3.0.1's name; the field names are not the original's)
    struct UioInfo {
        unsigned int m_hash;             // mm::mtl::hashStrCrc of the name add was given
        fw::CommonResource* m_resource;  // the requested file (update drops one that loads empty)
    };
    UIUioLibrary();
    virtual ~UIUioLibrary();  // slot 0
    void reset();  // every file released and the list freed
    void update(const fw::UpdateInfo& info);
    bool add(const char* name);  // requests the UIO file of a name (once); always true
    mm::mtl::Vector<UioInfo> m_uios;
};
}  // namespace ui

#endif
