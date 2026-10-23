#ifndef CLASSES_UI_UIBUILDINFOBDAT_H
#define CLASSES_UI_UIBUILDINFOBDAT_H

#include "classes/ui/UIBuildInfo.h"

namespace ui {
// table 0x7100B74360
class UIBuildInfoBdat : public ::ui::UIBuildInfo {
public:
    // the build information of a BDAT table of that name (UIFontManager::loadFontSet builds its resource so)
    UIBuildInfoBdat(const char* name);
    virtual ~UIBuildInfoBdat();  // slot 0
    virtual void getObjectNum() const;  // slot 5
    virtual void getObjectData(unsigned int, ui::UIBuildInfo::ObjectData&) const;  // slot 6
    virtual void getName() const;  // slot 7
    unsigned char pad_08[0x8];  // a 0x10-byte object: UIFontManager::loadFontSet's frame holds one so
};
}  // namespace ui

#endif
