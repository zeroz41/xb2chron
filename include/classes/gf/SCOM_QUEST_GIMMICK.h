#ifndef CLASSES_GF_SCOM_QUEST_GIMMICK_H
#define CLASSES_GF_SCOM_QUEST_GIMMICK_H

#include "classes/gf/SCOM.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B510
class SCOM_QUEST_GIMMICK : public ::gf::SCOM {
public:
    virtual ~SCOM_QUEST_GIMMICK();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
    static void createTresure(unsigned int gimmickId, float time);
    static void createSalvage(unsigned int gimmickId, float time);
};
}  // namespace gf

#endif
