#ifndef CLASSES_GF_SCOM_QUEST_REACH_H
#define CLASSES_GF_SCOM_QUEST_REACH_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B4B0
class SCOM_QUEST_REACH : public ::gf::SCOM {
public:
    virtual ~SCOM_QUEST_REACH();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
