#ifndef CLASSES_FW_APPLET_H
#define CLASSES_FW_APPLET_H

#include "classes/ml/IWorkEvent.h"

namespace fw { class Framework; }

namespace fw {
// what fw::Framework runs (Framework::getApplet's object at its 0x8). 1.0.0 names fw::Applet::initializeResource,
// isInitialized and enter, and its tl::TitleApplet derives from it. tl::TitleApplet's table (0x7100B3FFC8) holds
// ml::IWorkEvent's functions in slots 2-7, so the applet is an ml::IWorkEvent: apps::LauncherApp hands its
// events on through those slots (OnSystemPause slot 2, OnShutdownForce 3, OnPauseTrigger 5, OnViewResize 6,
// OnFileEvent 7)
class Applet : public ::ml::IWorkEvent {
public:
    virtual ~Applet();  // slot 0
    virtual void initializeResource(const Framework& framework);  // slot 8 (1.0.0's name for an empty base slot)
    virtual void initialize(const Framework& framework);  // slot 9 (tl::TitleApplet::initialize)
    virtual void finalize(const Framework& framework);  // slot 10 (tl::TitleApplet::finalize)
    virtual bool isInitialized();  // slot 11 (1.0.0's name; the launcher waits for it after initialize)
    virtual void enter();  // slot 12 (1.0.0's name; the launcher calls it once the applet is initialized)
};
}  // namespace fw

#endif
