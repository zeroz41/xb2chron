#ifndef CLASSES_ML__DSK_PROCDESKTOPEXCEPTION_H
#define CLASSES_ML__DSK_PROCDESKTOPEXCEPTION_H

#include "classes/ml/WinProc.h"

namespace ml { namespace _dsk {
// a base of ml::_dsk::ProcDesktopException no evidence names yet
class TUnk_B78BA0 {
public:
    virtual ~TUnk_B78BA0();
};
// table 0x7100B78B08; base at 0x1F0 unknown (TUnk_B78BA0)
class ProcDesktopException : public ::ml::WinProc, public TUnk_B78BA0 {
public:
    virtual ~ProcDesktopException();  // slot 0
    virtual bool wkStandbyLogout();  // slot 15
};
}}  // namespace ml::_dsk

#endif
