#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_DRIVERLISTCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_DRIVERLISTCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuDriverList.h"

namespace gf {
// table 0x7100B5B7B8
class GfMenuCharDataAdapter::DriverListConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // a driver list's entry; index -1: the list's selected one
    DriverListConverter(const GfMenuDriverList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuDriverList* m_list;
    int m_index;
};
}  // namespace gf

#endif
