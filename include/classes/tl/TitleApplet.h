#ifndef CLASSES_TL_TITLEAPPLET_H
#define CLASSES_TL_TITLEAPPLET_H

#include "classes/fw/Applet.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace tl {
// the title's applet: apps::FrameworkLauncher::create<TitleApplet> (tl::TitleApp::wkStandbyLogin) makes it. Table
// 0x7100B3FFB8; base at 0xB8 mm::mtl::PtrSingleton<tl::TitleApplet> (the constructor asserts get()==0 and registers it;
// new in 3.0.1, 1.0.0's TitleApplet has no second base)
class TitleApplet : public ::fw::Applet, public ::mm::mtl::PtrSingleton<TitleApplet> {
public:
    TitleApplet();
    virtual ~TitleApplet();  // slot 0
    // builds the game (gf::GfManager::build) and creates the title (TitleMain::create)
    virtual void initialize(const fw::Framework& framework);  // slot 9
    virtual void finalize(const fw::Framework& framework);  // slot 10
    virtual void update(const fw::UpdateInfo& info);  // slot 14
    // Placeholder name (fw::Applet's slot 15): see fw::Applet. Passes the update info to gf::GfManager::fn_710032A958
    virtual void fn_710014E704(const fw::UpdateInfo& info);  // slot 15
    virtual void postUpdate(const fw::UpdateInfo& info);  // slot 16
};
}  // namespace tl

#endif
