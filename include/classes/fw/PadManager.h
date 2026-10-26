#ifndef CLASSES_FW_PADMANAGER_H
#define CLASSES_FW_PADMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/fw/PadResEventManager.h"
#include "classes/ml/DevGraphCB.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "ml/PadVibrationInfo.h"
#include "fw/PadData.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B42678; its base at 0x10 is its singleton (the destructor stores PtrSingleton<fw::PadManager>'s table
// there and clears its instance), the one at 0x18 ml::DevGraphCB
class PadManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::PadManager>,
                   public ::ml::DevGraphCB {
public:
    virtual ~PadManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    // inline: emitted with the table, after initVibData (0x7100196AF8)
    virtual const char* getName() const { return "PadManager"; }  // slot 5
    virtual bool isInitialized() const;  // slot 6
    virtual void debugDraw(int, int);  // slot 8
    virtual void update(fw::UpdateInfo const&);  // slot 9
    virtual void viBeginFrame();  // slot 10
    static void initVibData();  // static: Framework::initializeManager calls it with no object
    static void playVibration(const ml::PadVibrationInfo& info);
    // the control pad's data of pad padNo for this frame (m_nullPad's without a manager)
    static const PadData& getControlPadData(int padNo);

    // what getControlPadData returns without a manager (0x7100B42630)
    static PadData m_nullPad;

    unsigned char pad_20[0x2B20];
    // the control pads' data for this frame (getControlPadData); the first one's pad gets the vibrations. The name
    // is not the original's; the count is not proven (the constructor initializes 24 PadData from here on)
    PadData m_controlPads[12];
    unsigned char pad_2EA0[0x870];
    // its destructor runs from ~PadManager (the name is not the original's)
    PadResEventManager m_padResEventManager;
};
}  // namespace fw

#endif
