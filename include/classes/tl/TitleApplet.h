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
    // 2.0.0's symbols name it. Passes the update info to gf::GfManager::updateAfterLayer
    virtual void updateAfterLayer(const fw::UpdateInfo& info);  // slot 15
    virtual void postUpdate(const fw::UpdateInfo& info);  // slot 16

    // 2.0.0's symbols name it (defined in TitleApp's unit). TitleApp::execute() clears it, execute and the regional
    // execute()s set it; initialize hands it to gf::GfSetupParam's m_dlcCameraParam
    static bool s_bGameTypeIra;
};
}  // namespace tl

#endif
