#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_TARGETENEMYCONVERTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_TARGETENEMYCONVERTER_H

#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter/IConverter.h"
#include "classes/gf/GfMenuManager.h"

namespace gf {
// table 0x7100B5C750
class GfMenuGfObjAdapter::TargetEnemyConverter : public ::gf::GfMenuGfObjAdapter::IConverter {
public:
    virtual GF_OBJ_HANDLE* getGfObjHandle() { return GfMenuManager::getTargetObjHandle(); }  // slot 0
};
}  // namespace gf

#endif
