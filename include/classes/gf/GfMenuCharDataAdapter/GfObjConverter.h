#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_GFOBJCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_GFOBJCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B728
class GfMenuCharDataAdapter::GfObjConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    GfObjConverter(GF_OBJ_HANDLE* handle) : m_handle(handle) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    virtual GfObjConverter* fromGfObj();  // slot 1
    GF_OBJ_HANDLE* m_handle;  // changeGfObj's (the name is not the original's)
};
}  // namespace gf

#endif
