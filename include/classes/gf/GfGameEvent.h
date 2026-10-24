#ifndef CLASSES_GF_GFGAMEEVENT_H
#define CLASSES_GF_GFGAMEEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameEvent; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }

namespace fw { class UpdateInfo; }
namespace gf {
// table 0x7100B54448
class GfGameEvent : public ::mm::mtl::PtrSingleton< ::gf::GfGameEvent> {
public:
    static void postUpdate(const fw::UpdateInfo& info);
    static void finishNewGameWait();
    static void stop();
    static void gevPause(unsigned int, unsigned int);
    virtual ~GfGameEvent();  // slot 0
    static void setAfterEventStartID(int id);
    // GfEvtModel::destroy hands it the model first
    // the event playing now (GfEvtModelBlade::create asks)
    static int getPlayEventId();
    // the event's fade-in: the wait before it and its length, in seconds
    static float getFadeInWaitSec();
    static float getFadeInSec();
    static void destroyEvtModel(class GfEvtModel* model);
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    static void clear();
};
}  // namespace gf

#endif
