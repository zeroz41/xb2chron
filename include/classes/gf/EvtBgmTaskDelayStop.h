#ifndef CLASSES_GF_EVTBGMTASKDELAYSTOP_H
#define CLASSES_GF_EVTBGMTASKDELAYSTOP_H

#include "classes/gf/EvtBgmTask.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfEvtBgm; }

namespace gf {
// table 0x7100B53B38
class EvtBgmTaskDelayStop : public ::gf::EvtBgmTask {
public:
    virtual ~EvtBgmTaskDelayStop();  // slot 0
    virtual void start(gf::GfEvtBgm*);  // slot 4
    virtual void update(gf::GfEvtBgm*, fw::UpdateInfo const&);  // slot 5
    virtual void cancel(gf::GfEvtBgm*);  // slot 6
};
}  // namespace gf

#endif
