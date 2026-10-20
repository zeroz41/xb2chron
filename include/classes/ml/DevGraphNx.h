#ifndef CLASSES_ML_DEVGRAPHNX_H
#define CLASSES_ML_DEVGRAPHNX_H

#include "classes/ml/DevGraph.h"

namespace ml { enum FONT_STYLE : int; }
namespace mm { class Col4; }
namespace mm { class Mat44; }
namespace mm { template <typename> class Rect; }

namespace ml {
// table 0x7100B764C0
class DevGraphNx : public ::ml::DevGraph {
public:
    virtual ~DevGraphNx();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkRender();  // slot 10
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
    virtual void grSetViewportSys(mm::Rect<int> const&, int);  // slot 18
    virtual void grSetScissorSys(mm::Rect<int> const&);  // slot 19
    virtual void getPersSys(mm::Mat44&, float, float, float);  // slot 21
    virtual void getOrthoSys(mm::Mat44&);  // slot 22
    virtual void getRootWidthSys();  // slot 23
    virtual void getRootHeightSys();  // slot 24
    virtual void getScreenScaleWSys();  // slot 25
    virtual void getVSyncSecSys() const;  // slot 26
    virtual void renderBeginSys();  // slot 27
    virtual void renderEndSys();  // slot 28
    virtual void renderSyncSys();  // slot 29
    virtual void resetSizeSys(short, short);  // slot 30
    virtual void fontDrawSys(short, short, float, float, char const*, mm::Col4 const*, bool);  // slot 31
    virtual void fontGetWidthSys(char const*, ml::FONT_STYLE, float);  // slot 32
    virtual void fontGetHeightSys(ml::FONT_STYLE, float);  // slot 33
    virtual void getCostSys() const;  // slot 34
};
}  // namespace ml

#endif
