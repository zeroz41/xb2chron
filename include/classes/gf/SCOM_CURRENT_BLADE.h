#ifndef CLASSES_GF_SCOM_CURRENT_BLADE_H
#define CLASSES_GF_SCOM_CURRENT_BLADE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AC28
class SCOM_CURRENT_BLADE : public ::gf::SCOM {
public:
    explicit SCOM_CURRENT_BLADE(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // 1.0.0's SCOM_CURRENT_BLADE::create (0x71005D2238), called by 1.0.0's pt setCurrentBlade with its argument
    static unsigned long create(unsigned int blade);

    // the name is not the original's: the blade exec makes current (1001/1002 also pick Pyra or Mythra)
    unsigned int m_value;
};
}  // namespace gf

#endif
