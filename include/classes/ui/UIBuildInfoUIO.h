#ifndef CLASSES_UI_UIBUILDINFOUIO_H
#define CLASSES_UI_UIBUILDINFOUIO_H

#include "classes/ui/UIBuildInfo.h"
#include "mm/mtl/Array.h"

namespace fw { class CommonResource; }

namespace ui {
class UIObjBuildData;

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

private:
    // the object at index of the file's build data as an ObjectData (a missing "type" or "name" leaves the rest
    // at its defaults); the name is the original's (symbol)
    void getObjectDataUIO(UIObjBuildData* buildData, unsigned int index, ui::UIBuildInfo::ObjectData& data) const;

public:
    // the names are not the original's
    const char* m_name;                                   // the UIO file's name (getName)
    fw::CommonResource* m_resource;                       // the requested file, released once read or found empty
    mm::mtl::Array<ui::UIBuildInfo::ObjectData> m_objects;  // the file's objects, read by update (0x30 in all)
};
}  // namespace ui

#endif
