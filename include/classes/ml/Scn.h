#ifndef CLASSES_ML_SCN_H
#define CLASSES_ML_SCN_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class ScnObjCam; }
namespace ml { class ScnObj; }
namespace ml { class ScnObjModel; }
namespace ml { class ScnObjIBL; }
namespace ml { class ScnRenderDrSys; }
namespace ml { class ScnPoolObj; }
namespace ml { class ScnCamMan; }
namespace ml { class WinView; }

namespace ml {
// a base of ml::Scn no evidence names yet
class TUnk_B77B18 {
public:
    virtual ~TUnk_B77B18();
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of ml::Scn no evidence names yet
class TUnk_B77B38 {
public:
    virtual ~TUnk_B77B38();
};
// table 0x7100B77AC8; base at 0x8 unknown (TUnk_B77B18), base at 0x18 unknown (TUnk_B77B38)
class Scn : public ::ml::IWorkEvent, public TUnk_B77B18, public TUnk_B77B38 {
public:
    virtual ~Scn();  // slot 0
    // a camera by index; -1 the current view's (fw::NaviManager::update's)
    ScnObjCam* getCam(int index);
    // a light or image-based light made from a resource, by the scene's renderer (gf::MapLIBL and MapGIBL keep
    // them), and an item given back
    ScnObj* createLgt(const void* resource, int arg);
    ScnObjIBL* createIBL(const void* resource, int arg);
    void releaseItem(ScnObj* item);
    void setView(WinView* view, int index);
    // a view by index; -1 the current one (event::BouManager detaches itself from it)
    WinView* getView(int index);
    // a model made from a resource (fw::ModelObject::create's)
    ScnObjModel* createMdl(const void* resource, const char* name, int arg);
    ScnPoolObj* m_pool;  // 0x20 releaseItem gives items back to it (the name is not the original's)
    ScnCamMan* m_camMan;  // 0x28 setView's (the name is not the original's)
    unsigned char pad_30[0x8];
    ScnRenderDrSys* m_renderDrSys;  // what UIScreenObject gives ScnRenderDrSysParmAcc (the name is not the original's)
    unsigned char pad_40[0x6C];
    // 0xAC createMdl passes its negation to each new model's setAlwaysTexStm (the name is not the original's)
    bool m_noAlwaysTexStm;
};
}  // namespace ml

#endif
