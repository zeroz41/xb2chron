#ifndef CLASSES_UI_UIBUILDINFOUIO_H
#define CLASSES_UI_UIBUILDINFOUIO_H

#include "classes/ui/UIBuildInfo.h"

namespace ui {
// table 0x7100B743B0
class UIBuildInfoUIO {
public:
    virtual ~UIBuildInfoUIO();  // slot 0
    virtual void update();  // slot 2
    virtual void isReady() const;  // slot 3
    virtual void isValid() const;  // slot 4
    virtual void getObjectNum() const;  // slot 5
    virtual void getObjectData(unsigned int, ui::UIBuildInfo::ObjectData&) const;  // slot 6
    virtual void getName() const;  // slot 7
};
}  // namespace ui

#endif
