#ifndef CLASSES_GF_GFGAMETARGET_H
#define CLASSES_GF_GFGAMETARGET_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a base of gf::GfGameTarget no evidence names yet
class TUnk_B56700 {
public:
    virtual ~TUnk_B56700();
    virtual void recieveMessage(fw::MessageObject*, fw::Message&) = 0;
    virtual void gevChangeLeader(gf::GF_OBJ_HANDLE*) = 0;
    virtual void gevSwapFormation(unsigned int, unsigned int) = 0;
};
// table 0x7100B56700; base at 0x0 unknown (TUnk_B56700)
class GfGameTarget : public TUnk_B56700, public ::fw::MessageObject, public ::gf::IGfEvent {
public:
    class StateAutoTarget;
    class StateBattleTarget;
    class StateDriverNotActive;
    class StateEnemyTarget;
    virtual ~GfGameTarget();  // slot 0
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevChangeLeader(gf::GF_OBJ_HANDLE*);  // slot 3
    virtual void gevSwapFormation(unsigned int, unsigned int);  // slot 4
};
}  // namespace gf

#endif
