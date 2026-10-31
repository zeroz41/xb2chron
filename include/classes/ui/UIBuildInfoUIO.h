#ifndef CLASSES_UI_UIBUILDINFOUIO_H
#define CLASSES_UI_UIBUILDINFOUIO_H

#include "classes/ui/UIBuildInfo.h"

namespace ui {
// table 0x7100B743B0
class UIBuildInfoUIO : public ::ui::UIBuildInfo {
public:
    // the build information of a UIO file of that name (UIObjFactory's order and registPreloadResource make one,
    // 0x30 bytes, for kind 1)
    UIBuildInfoUIO(const char* name);
    virtual ~UIBuildInfoUIO();  // slot 0
    virtual void update();  // slot 2
    virtual bool isReady() const;  // slot 3
    virtual bool isValid() const;  // slot 4
    virtual unsigned int getObjectNum() const;  // slot 5
    virtual void getObjectData(unsigned int, ui::UIBuildInfo::ObjectData&) const;  // slot 6
    virtual const char* getName() const;  // slot 7

    unsigned char pad_08[0x28];  // 0x30 bytes in all (UIObjFactory::order allocates so)
};
}  // namespace ui

#endif
