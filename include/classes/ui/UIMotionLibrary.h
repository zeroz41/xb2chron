#ifndef CLASSES_UI_UIMOTIONLIBRARY_H
#define CLASSES_UI_UIMOTIONLIBRARY_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Vector.h"

namespace ui { class UIMotionLibrary; }
namespace ui { class UIMotionData; }
namespace fw { class CommonResource; }
namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74D90; the menu motion files add requested, by their name's hash, and their data once loaded
class UIMotionLibrary : public ::mm::mtl::PtrSingleton< ::ui::UIMotionLibrary> {
public:
    // one motion file (1.0.0's name; the field names are not the original's)
    struct MotionInfo {
        unsigned int m_hash;            // mm::mtl::hashStrCrc of the name add was given
        fw::CommonResource* m_resource; // the requested file, released once loaded (or found empty)
        UIMotionData* m_data;           // update's, from the loaded file
    };
    UIMotionLibrary();
    virtual ~UIMotionLibrary();  // slot 0
    void reset();  // every motion released and the list freed
    void update(const fw::UpdateInfo& info);
    bool add(const char* name);  // requests the motion file of a name (once); always true
    UIMotionData* find(const char* name);  // the loaded data of a name's file, none
    mm::mtl::Vector<MotionInfo> m_motions;
};
}  // namespace ui

#endif
