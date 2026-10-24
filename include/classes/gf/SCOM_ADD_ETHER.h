#ifndef CLASSES_GF_SCOM_ADD_ETHER_H
#define CLASSES_GF_SCOM_ADD_ETHER_H

#include "classes/gf/SCOM.h"

namespace gf {
// 1.0.0 has a table for it (_ZTVN2gf14SCOM_ADD_ETHERE); 3.0.1's create queues no request and adds the ether at once
class SCOM_ADD_ETHER : public ::gf::SCOM {
public:
    static unsigned long create(int);
};
}  // namespace gf

#endif
