#ifndef CLASSES_GRLIB_CGLIBMANAGER_H
#define CLASSES_GRLIB_CGLIBMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "grlib/CGLibDeviceObj.h"

namespace grlib { class CGLibManager; }
namespace grlib { namespace context { class CGLibSystemContext; }}

namespace grlib {
// table 0x7100B79B50. The field names are not the original's.
// CGLibDeviceObj is a base (at 0x8): the constructor runs its constructor before storing the table, as for a base
class CGLibManager : public ::mm::mtl::PtrSingleton< ::grlib::CGLibManager>, public CGLibDeviceObj {
public:
    CGLibManager();
    virtual ~CGLibManager();  // slot 0

    // whether the system context is released (false while there is none)
    bool isRelease();
    // sets up the GPU memory, the device and the system context; true when the device came up
    bool deviceInit();
    // releases the system context, the device and the GPU memory
    bool deviceRelease();
    static bool isReleaseOk();
    void begin();
    void end();
    void swap();
    void tail();
    unsigned long getGpuTimeStamp() const;

    context::CGLibSystemContext* m_pSystemContext;  // 0x5028: deviceInit creates it

    // which of the double-buffered frame halves is current
    static int s_nDblNowIdx;
    // which of the two stacked halves is current (CGLibState::setPixelResidentArea keeps the old area there)
    static int s_nStkNowIdx;
    // which of the three triple-buffered thirds is current (begin advances it 0, 1, 2, 0, ...)
    static int s_nTriNowIdx;
    // set once the device is released (the destructor and deviceRelease set it, the constructor clears it)
    static bool s_nReleaseOk;
};
}  // namespace grlib

#endif
