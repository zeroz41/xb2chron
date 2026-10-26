#ifndef CLASSES_GRLIB_CGLIBSHDLISTDATA_H
#define CLASSES_GRLIB_CGLIBSHDLISTDATA_H

#include "classes/grlib/CGLibShdListBase.h"
#include "grlib/CGLibDecShader.h"

namespace grlib {
// table 0x7100B7A430
class CGLibShdListData : public ::grlib::CGLibShdListBase< ::grlib::CGLibDecShader> {
public:
    virtual ~CGLibShdListData() { release(); }  // slot 0
};
}  // namespace grlib

#endif
