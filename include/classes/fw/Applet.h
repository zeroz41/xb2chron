#ifndef CLASSES_FW_APPLET_H
#define CLASSES_FW_APPLET_H

#include "classes/ml/IWorkEvent.h"
#include "classes/fw/Framework.h"
#include "mm/mtl/FixStr.h"

namespace fw { class UpdateInfo; }

namespace fw {
// what fw::Framework runs (Framework::getApplet's object at its 0x8). 1.0.0 names fw::Applet::initializeResource,
// isInitialized and enter, and its tl::TitleApplet derives from it. tl::TitleApplet's table (0x7100B3FFC8) holds
// ml::IWorkEvent's functions in slots 2-7, so the applet is an ml::IWorkEvent: apps::LauncherApp hands its
// events on through those slots (OnSystemPause slot 2, OnShutdownForce 3, OnPauseTrigger 5, OnViewResize 6,
// OnFileEvent 7)
class Applet : public ::ml::IWorkEvent {
public:
    // the constructor and every virtual are inline: tl::TitleApplet's unit holds this table and its slots (weak), and
    // tl::TitleApplet's constructor stores the table (0x7100B40078)
    Applet() : m_closed(false), pad_C(), m_env() {}
    virtual ~Applet() {}  // slot 0
    virtual void initializeResource(const Framework& framework) {}  // slot 8 (1.0.0's name for an empty base slot)
    virtual void initialize(const Framework& framework) {}  // slot 9 (tl::TitleApplet::initialize)
    virtual void finalize(const Framework& framework) {}  // slot 10 (tl::TitleApplet::finalize)
    virtual bool isInitialized() { return true; }  // slot 11 (1.0.0's name; the launcher waits for it after initialize)
    virtual void enter() {}  // slot 12 (1.0.0's name; the launcher calls it once the applet is initialized)
    // the framework's frame (Framework::preUpdate, update, postUpdate, tail pass its update info); 1.0.0 names
    // fw::Applet::preUpdate, postUpdate and tail, tl::TitleApplet::update and postUpdate
    virtual void preUpdate(const UpdateInfo& info) {}  // slot 13
    virtual void update(const UpdateInfo& info) = 0;  // slot 14 (empty in the base table)
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (the base table's empty slot 15 at
    // 0x710014E704). tl::TitleApplet's (fn_710014E6CC) passes the update info to GfManager::fn_710032A958
    virtual void fn_710014E704(const UpdateInfo& info) {}  // slot 15
    virtual void postUpdate(const UpdateInfo& info) {}  // slot 16
    virtual void tail(const UpdateInfo& info) {}  // slot 17

    bool m_closed;  // Framework::isAppletClosed reads it (the name is not the original's)
    mm::mtl::FixStr<128> pad_C;  // 0x0C the constructor empties it; no known code reads it
    // 0x90 apps::FrameworkLauncher::create<T> copies the framework's environment (Framework 0x50-0x70) into it one
    // field at a time; tl::TitleApplet::initialize hands its fields to gf::GfManager::build (the name is not the original's)
    FrameworkEnv m_env;
};
}  // namespace fw

#endif
