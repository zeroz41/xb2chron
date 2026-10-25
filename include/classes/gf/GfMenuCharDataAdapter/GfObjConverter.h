#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_GFOBJCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_GFOBJCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B728
class GfMenuCharDataAdapter::GfObjConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    virtual GfObjConverter* fromGfObj() { return this; }  // slot 1
    GF_OBJ_HANDLE* m_handle;  // changeGfObj's (the name is not the original's)
};
}  // namespace gf

#endif
