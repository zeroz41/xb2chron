#ifndef CLASSES_ML__DSK_PROCDESKTOPBACKGROUND_H
#define CLASSES_ML__DSK_PROCDESKTOPBACKGROUND_H

#include "classes/ml/WinProc.h"

namespace ml { namespace _dsk {
// a base of ml::_dsk::ProcDesktopBackGround no evidence names yet
class TUnk_B78AC8 {
public:
    virtual ~TUnk_B78AC8();
};
// table 0x7100B78A30; base at 0x1F0 unknown (TUnk_B78AC8)
class ProcDesktopBackGround : public ::ml::WinProc, public TUnk_B78AC8 {
public:
    virtual ~ProcDesktopBackGround();  // slot 0
    virtual bool wkStandbyLogout();  // slot 15
};
}}  // namespace ml::_dsk

#endif
