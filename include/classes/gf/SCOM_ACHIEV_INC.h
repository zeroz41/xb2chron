#ifndef CLASSES_GF_SCOM_ACHIEV_INC_H
#define CLASSES_GF_SCOM_ACHIEV_INC_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6AA60
class SCOM_ACHIEV_INC : public ::gf::SCOM {
public:
    explicit SCOM_ACHIEV_INC(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // queues a request that adds value to achievement counter type (type 0x22 also counts salvage-shop requests)
    static unsigned long create(unsigned int type, int value, unsigned int);
    static void addTotalCount(unsigned int type, unsigned int value);

    // the names are not the original's: what the create functions store (their arguments, in order)
    unsigned int m_value;
    int m_value2;
    unsigned char pad_24[0x4];
    unsigned int m_value3;
    unsigned char pad_2c[0x34c];
    unsigned long m_value4;
};
}  // namespace gf

#endif
