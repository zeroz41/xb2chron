#ifndef CLASSES_GF_EVTBGMTASKVOLUME_H
#define CLASSES_GF_EVTBGMTASKVOLUME_H

#include "classes/gf/EvtBgmTask.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfEvtBgm; }

namespace gf {
// table 0x7100B53B80
class EvtBgmTaskVolume : public ::gf::EvtBgmTask {
public:
    virtual ~EvtBgmTaskVolume();  // slot 0
    virtual void isVolumeTask() const;  // slot 2
    virtual void start(gf::GfEvtBgm*);  // slot 4
    virtual void update(gf::GfEvtBgm*, fw::UpdateInfo const&);  // slot 5
    virtual void cancel(gf::GfEvtBgm*);  // slot 6
};
}  // namespace gf

#endif
