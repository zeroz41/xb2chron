#ifndef CLASSES_GF_SCOM_QUEST_GIMMICK_H
#define CLASSES_GF_SCOM_QUEST_GIMMICK_H

#include "classes/gf/SCOM.h"

namespace gmk { enum GmkType : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6B510
class SCOM_QUEST_GIMMICK : public ::gf::SCOM {
public:
    explicit SCOM_QUEST_GIMMICK(SCOM_TYPE type) : SCOM(type) {}
    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    static unsigned long createDoor(unsigned int id, float time);
    static unsigned long createElevator(unsigned int id, float time);
    static unsigned long createJump(unsigned int id, float time);
    static unsigned long createMapGimmick(unsigned int id, float time);
    static unsigned long createWarp(unsigned int id, float time);
    static unsigned long createSalvage(unsigned int id, float time);
    static unsigned long createTresure(unsigned int id, float time);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among the other
    // create functions in gf_req_scom and has their shape. What it does: like createTresure, for gimmick type 0x1C
    // (a collection point, GmkCollection::TYPE): with a positive time it calls GfPlayFactory::
    // createGimmickTaskComplete(0x1C, id, time), else it queues a SCOM_QUEST_GIMMICK request; GfFieldCollect's
    // seqWaitUIEnd, seqDo and seqWaitDrop call it with the collection point's bdat id.
    static unsigned long fn_710055F594(unsigned int id, float time);

    // the names are not the original's: what the create functions store (their arguments, in order)
    gmk::GmkType m_value;
    unsigned int m_value2;
    float m_value3;
};
}  // namespace gf

#endif
