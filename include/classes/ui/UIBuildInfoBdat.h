#ifndef CLASSES_UI_UIBUILDINFOBDAT_H
#define CLASSES_UI_UIBUILDINFOBDAT_H

#include "classes/ui/UIBuildInfo.h"

namespace ui {
// table 0x7100B74360
class UIBuildInfoBdat : public ::ui::UIBuildInfo {
public:
    virtual ~UIBuildInfoBdat();  // slot 0
    virtual void getObjectNum() const;  // slot 5
    virtual void getObjectData(unsigned int, ui::UIBuildInfo::ObjectData&) const;  // slot 6
    virtual void getName() const;  // slot 7
};
}  // namespace ui

#endif
