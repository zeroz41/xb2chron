#ifndef CLASSES_GF_GFGAMETARGET_H
#define CLASSES_GF_GFGAMETARGET_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameTarget; }

namespace gf {
// table 0x7100B56700
class GfGameTarget : public ::mm::mtl::PtrSingleton< ::gf::GfGameTarget>, public ::fw::MessageObject, public ::gf::IGfEvent {
public:
    class StateAutoTarget;
    class StateBattleTarget;
    class StateDriverNotActive;
    class StateEnemyTarget;
    virtual ~GfGameTarget();  // slot 0
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 2
    virtual void gevChangeLeader(gf::GF_OBJ_HANDLE*);  // slot 3
    virtual void gevSwapFormation(unsigned int, unsigned int);  // slot 4
};
}  // namespace gf

#endif
