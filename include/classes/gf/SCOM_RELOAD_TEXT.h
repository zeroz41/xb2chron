#ifndef CLASSES_GF_SCOM_RELOAD_TEXT_H
#define CLASSES_GF_SCOM_RELOAD_TEXT_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
namespace fw { enum LangType : unsigned int; }

namespace gf {
// table 0x7100B6B3F0
class SCOM_RELOAD_TEXT : public ::gf::SCOM {
public:
    // its table's slot 0 is SCOM's destructor: no destructor of its own; the request starts with state 2
    explicit SCOM_RELOAD_TEXT(SCOM_TYPE type) : SCOM(type, GfReqSmallCom::sys()->newHandle(), 2) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // selects the language and queues the request that reloads the BDAT tables and texts; -1 when it is selected
    static unsigned long create(fw::LangType lang);
};
}  // namespace gf

#endif
