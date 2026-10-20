#ifndef CLASSES_ML_DEVGRAPH_H
#define CLASSES_ML_DEVGRAPH_H

#include "classes/ml/WorkObj.h"

namespace ml { enum FONT_STYLE : int; }
namespace mm { class Col4; }
namespace mm { class Mat44; }
namespace mm { template <typename> class Rect; }

namespace ml {
// between ml::DevGraph and ml::WorkObj: fields, no virtuals of its own
class TUnk_B75C48 : public ::ml::WorkObj {
public:
    unsigned char pad_1A8[0x8];  // fields: size from its derived classes
};
// a base of ml::DevGraph no evidence names yet
class TUnk_B75DE0 {
public:
    virtual ~TUnk_B75DE0();
};
// table 0x7100B75C48; base at 0x0 unknown (TUnk_B75C48), base at 0x1B0 unknown (TUnk_B75DE0)
class DevGraph : public TUnk_B75C48, public TUnk_B75DE0 {
public:
    virtual ~DevGraph();  // slot 0
    virtual void wkStandby();  // slot 8
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
    virtual void cmdAddDisplayListFast(void*, unsigned int, unsigned int);  // slot 17
    virtual void grSetViewportSys(mm::Rect<int> const&, int) = 0;  // slot 18
    virtual void grSetScissorSys(mm::Rect<int> const&) = 0;  // slot 19
    virtual void grInitContextSys();  // slot 20
    virtual void getPersSys(mm::Mat44&, float, float, float) = 0;  // slot 21
    virtual void getOrthoSys(mm::Mat44&) = 0;  // slot 22
    virtual void getRootWidthSys() = 0;  // slot 23
    virtual void getRootHeightSys() = 0;  // slot 24
    virtual void getScreenScaleWSys() = 0;  // slot 25
    virtual void getVSyncSecSys() const = 0;  // slot 26
    virtual void renderBeginSys() = 0;  // slot 27
    virtual void renderEndSys() = 0;  // slot 28
    virtual void renderSyncSys() = 0;  // slot 29
    virtual void resetSizeSys(short, short) = 0;  // slot 30
    virtual void fontDrawSys(short, short, float, float, char const*, mm::Col4 const*, bool) = 0;  // slot 31
    virtual void fontGetWidthSys(char const*, ml::FONT_STYLE, float) = 0;  // slot 32
    virtual void fontGetHeightSys(ml::FONT_STYLE, float) = 0;  // slot 33
    virtual void getCostSys() const = 0;  // slot 34
    virtual void cmdExecDisplayListSys();  // slot 35
    virtual void cmdAddDisplayListSys(void*, unsigned int, unsigned int);  // slot 36
    virtual void cmdSetupDisplayListSys();  // slot 37
    virtual void cmdTermDisplayListSys();  // slot 38
    virtual void cmdOpenDisplayListSys(unsigned int, bool, bool);  // slot 39
    virtual void cmdCloseDisplayListSys(bool);  // slot 40
    virtual void cmdAddCreatedListSys(void*, unsigned int);  // slot 41
    virtual void cmdSuspendDisplayListSys(bool, bool);  // slot 42
    virtual void cmdGetCurrentAdrSys();  // slot 43
    virtual void cmdGetRemainSizeSys() const;  // slot 44
    virtual void cmdAllocSys(unsigned int, unsigned int);  // slot 45
    virtual void cmdAlignSys(unsigned int);  // slot 46
    virtual void cmdAddOfsSys(unsigned int);  // slot 47
    virtual void cmdIsOpenDisplayListSys() const;  // slot 48
};
}  // namespace ml

#endif
