#ifndef CLASSES_GF_SCOM_FIELD_VOICE_H
#define CLASSES_GF_SCOM_FIELD_VOICE_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }
namespace gf { enum CV_FIELD : int; enum CV_PRIO : int; }  // the field voice's kind and priority

namespace gf {
// table 0x7100B6B690
class SCOM_FIELD_VOICE : public ::gf::SCOM {
public:
    virtual ~SCOM_FIELD_VOICE();  // slot 0
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static void create(CV_FIELD field, CV_PRIO prio);
};
}  // namespace gf

#endif
