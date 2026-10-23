#ifndef GF_SDATADRIVER_H
#define GF_SDATADRIVER_H

#include "gf/SDataBlade.h"

namespace gf {
// no table: a driver's data, 0x5A0 bytes (DataObjDriver::setupVirtualParam allocates one for its virtual settings;
// GfDataDriver::getSDataDriver returns one). The field names are not the original's.
class SDataDriver {
public:
    SDataIdea m_idea;  // DataObjDriver::getIdea returns the driver's data itself
    unsigned short m_dataType;  // DataObjDriver::getDataType
    unsigned short m_id;  // its row, 0 for none (DataObjDriver::isValid)
    short m_bladeSet;  // the slot of its engaged blade, -1 for none (DataObjDriver::setBladeSet)
    unsigned short m_blades[3];  // the blade in each slot (DataObjDriver::getBlade); the count is not known
    unsigned char pad_2c[0x574];
};

// a DLC driver's data, 0xDAC bytes: a driver's data and more (GfDataDriver::fn_7100241BB4 returns one;
// DataObjDriver::setupVirtualParam allocates one). The type and field names are not the original's.
struct SDataDriverDlc {
    SDataDriver m_driver;
    unsigned char pad_5a0[0x80C];
};
}  // namespace gf

#endif
