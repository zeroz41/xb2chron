#ifndef CLASSES_ML_ERRVIEWER_H
#define CLASSES_ML_ERRVIEWER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/IWorkBackground.h"
#include "classes/ml/ICBError.h"
#include "mm/mtl/FixedList.h"
#include "ml/CriticalSection.h"
#include "ml/WorkRoot.h"

namespace ml { class ErrViewer; }
namespace ml { class CERR_STRUCT; }

namespace ml {
// when ErrViewer::callbackError asks the current error's listener (the enumerator names are not the original's: each
// is named after the one function that passes it)
enum ERR_CALL : int {
    ERR_CALL_STANDBY = 0,
    ERR_CALL_UPDATE = 1,
    ERR_CALL_TAIL = 2,
    ERR_CALL_RENDER = 3,
};

// table 0x7100B77A30; IWorkBackground at 0x8 (the constructor hands it to WorkCpu::addBackgroundListener)
class ErrViewer : public ::mm::mtl::PtrSingleton< ::ml::ErrViewer>, public ::ml::IWorkBackground {
public:
    // one requested error (1.0.0's FixedList<ml::ErrViewer::ERRINFO*, 32>; reqError builds it in 0xD0 bytes from
    // WorkUtil::getWorkMem)
    struct ERRINFO {
        unsigned int m_code;  // 0x0 reqError's first argument (the name is not the original's)
        ERR_CALL m_call;  // 0x4 when its listener is asked (the name is not the original's)
        ICBError* m_listener;  // 0x8 (the name is not the original's)
        CERR_STRUCT* m_handle;  // 0x10 createHandle's number, what reqError returns (the name is not the original's)
        void* m_mem;  // 0x18 given back to MemManager before the error is deleted (the name is not the original's)
        unsigned char pad_20[0xAC - 0x20];
        int m_dispTime;  // 0xAC set from m_dispTimeInit when the listener lets the error go on (the name is not the original's)
        int m_dispTimeInit;  // 0xB0 reqError's last argument (the name is not the original's)
        unsigned char pad_B4[0xD0 - 0xB4];
    };

    ErrViewer();
    virtual ~ErrViewer();  // slot 0
    virtual void setup();  // slot 2
    virtual void term();  // slot 3
    virtual void upErrViewer();  // slot 4
    virtual void bkgHomeMenu(bool);  // slot 5
    virtual void bkgHomeMenuDenied();  // slot 6

    static ErrViewer* create();
    // asks the viewer to end; true once it is gone (or was never made)
    static bool destroy();
    static void standby();
    static void fnRender();
    static void tail();
    static void update();

    // whether an error waits (1.0.0's isExistError: none while the work root restarts)
    bool isExistError() const {
        if (WorkRoot::isRestart()) {
            return false;
        }
        CS lock(*m_cs);
        return m_errList.begin() != m_errList.end();
    }
    // asks the current error's listener when its call comes
    void callbackError(ERR_CALL call);

    static int s_nHandle;

    CriticalSection* m_cs;  // 0x10 (the name is not the original's)
    mm::mtl::FixedList<ERRINFO*, 32> m_errList;  // 0x18 (the name is not the original's)
    int m_state;  // 0x258 standby's step; 1.0.0's isInitialized is m_state == 1 (the name is not the original's)
    long m_deniedClock;  // 0x260 when the home menu was denied (the name is not the original's)
    bool m_active;  // 0x268 between setup and term; 1.0.0's reqError takes errors only then (the name is not the original's)
    bool m_destroyRequest;  // 0x269 destroy sets it, standby then deletes the errors (the name is not the original's)
    bool m_terminated;  // 0x26A set after term; destroy deletes the viewer then (the name is not the original's)
    bool m_errorDisp;  // 0x26B 1.0.0's isErrorDisp reads it (the name is not the original's)
    bool m_homeMenuDenied;  // 0x26C for three seconds after bkgHomeMenuDenied (the name is not the original's)
    unsigned char pad_26D[0x270 - 0x26D];
    int m_ownedMemSize;  // 0x270 only the constructor writes it (the name is not the original's)
    void* m_ownedMem;  // 0x278 term gives it back to MemManager (the name is not the original's)
};
}  // namespace ml

#endif
