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
    virtual unsigned int getObjectNum() const;  // slot 5
    virtual void getObjectData(unsigned int index, ui::UIBuildInfo::ObjectData& data) const;  // slot 6
    virtual const char* getName() const { return m_name; }  // slot 7
    const char* m_name;  // the BDAT table's name
};
}  // namespace ui

#endif
