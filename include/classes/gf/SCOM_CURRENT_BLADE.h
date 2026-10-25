#ifndef CLASSES_GF_SCOM_CURRENT_BLADE_H
#define CLASSES_GF_SCOM_CURRENT_BLADE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AC28
class SCOM_CURRENT_BLADE : public ::gf::SCOM {
public:
    virtual bool exec(fw::UpdateInfo const&);  // slot 2

    // the name is not the original's: the blade exec makes current (1001/1002 also pick Pyra or Mythra)
    unsigned int m_value;
};
}  // namespace gf

#endif
