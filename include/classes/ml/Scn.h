#ifndef CLASSES_ML_SCN_H
#define CLASSES_ML_SCN_H

#include "classes/ml/IWorkEvent.h"
#include "mtl/AllocHandle.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixedQueue.h"

namespace ml { class FileResTh; }
namespace ml { class ScnObjCam; }
namespace ml { class ScnDebug; }
namespace ml { class CriticalSection; }
namespace ml { class ScnObj; }
namespace ml { class ScnObjModel; }
namespace ml { class ScnObjIBL; }
namespace ml { class ScnRenderDrSys; }
namespace ml { class ScnPoolObj; }
namespace ml { class ScnCamMan; }
namespace ml { class WinView; }
namespace ml { class IScnRender; }
namespace ml { class ScnSetup; }
namespace ml { enum SCNCAM : int; }
namespace ml { enum SCNPRIO_CB : int; }

namespace ml {
// table 0x7100B77AC8; the destructor stores mm::mtl::PtrSingleton<ml::Scn>'s table at 0x18 and clears its
// instance; the constructor stores mm::mtl::ReferenceObject's table at 0x8
class Scn : public ::ml::IWorkEvent, public ::mm::mtl::ReferenceObject, public ::mm::mtl::PtrSingleton< ::ml::Scn> {
public:
    virtual ~Scn();  // slot 0
    void term();
    // the frame's tail and drawing (FrameworkLauncher::wkTail and drawTask call them on the launcher's scene)
    void tail();
    // the entry resource of the file (DrShdLgtMan::reloadShader takes its shader package from it)
    FileResTh* allocEntryRes(const char* path);
    void draw();
    // a camera by index; -1 the current view's (fw::NaviManager::update's)
    ScnObjCam* getCam(int index);
    // a light or image-based light made from a resource, by the scene's renderer (gf::MapLIBL and MapGIBL keep
    // them), and an item given back
    ScnObj* createLgt(const void* resource, int arg);
    ScnObjIBL* createIBL(const void* resource, int arg);
    void releaseItem(ScnObj* item);
    void setView(WinView* view, int index);
    void move();
    // a view by index; -1 the current one (event::BouManager detaches itself from it)
    WinView* getView(int index);
    // a model made from a resource (fw::ModelObject::create's)
    ScnObjModel* createMdl(const void* resource, const char* name, int arg);
    void setDebDraw(SCNCAM cam, SCNPRIO_CB prio);
    void renderStop();
    // a job thread's function (WorkCpu::entryJobThread's type): deletes the scene's renderer
    static unsigned int thRenderKillTerminate(void* scn, void* arg);
    // a job thread's function: calls cbRenderAfter of every render callback added with the after flag, at the
    // callback's DebDraw priority
    static unsigned int thUpAfter(void* scn, void* arg);
    // a render callback queued for the next tail (the array takes it there); full at 64
    void addRenderCB(IScnRender* render, SCNPRIO_CB prio, bool after, bool flag);
    // on the scene the singleton holds: queues the callback's removal and marks its entry removed
    static void removeRenderCB(IScnRender* render);
    // a scene in the work memory, from the setup (a default one when none), with one reference taken
    static Scn* create(const ScnSetup* setup);
    explicit Scn(const ScnSetup* setup);

    // one per camera: the priority the debug drawing renders at (the struct and its names are not the original's)
    struct DEBDRAW {
        SCNPRIO_CB m_prio;  // setDebDraw's
        int pad_4;          // the constructor numbers them 1 to 9
    };
    // one render callback (the struct and its names are not the original's)
    struct RENDER_CB {
        IScnRender* m_render;
        SCNPRIO_CB m_prio;  // thUpAfter sets it as the DebDraw priority around the call
        bool pad_c;         // addRenderCB's last argument
        bool m_after;       // thUpAfter calls cbRenderAfter only for these
        bool m_removed;     // removeRenderCB sets it; move skips these
    };

    ScnPoolObj* m_pool;  // 0x20 releaseItem gives items back to it (the name is not the original's)
    ScnCamMan* m_camMan;  // 0x28 setView's (the name is not the original's)
    ScnDebug* m_debug;  // 0x30 init news it, term deletes it (the name is not the original's)
    ScnRenderDrSys* m_renderDrSys;  // what UIScreenObject gives ScnRenderDrSysParmAcc (the name is not the original's)
    unsigned char pad_40[0x24];
    // 0x64 ScnObjModelDrSysStandard::create news the model from it (the name is not the original's)
    mtl::ALLOC_HANDLE m_allocHandle;
    unsigned char pad_68[0x44];
    // 0xAC createMdl passes its negation to each new model's setAlwaysTexStm (the name is not the original's)
    bool m_noAlwaysTexStm;
    unsigned char pad_AD[0x7];
    // 0xB4 the job group the constructor creates and entryAutoExecGrp's; term removes and releases it (the name is
    // not the original's)
    int m_grpHandle;
    // 0xB8 the render callbacks (the names are not the original's)
    RENDER_CB m_renderCB[64];
    int m_renderCBNum;  // 0x4B8
    unsigned char pad_4BC[0x4];
    mm::mtl::FixedQueue<RENDER_CB, 64> m_addRenderCB;     // 0x4C0 addRenderCB's (the name is not the original's)
    mm::mtl::FixedQueue<RENDER_CB, 64> m_removeRenderCB;  // 0x8D0 removeRenderCB's (the name is not the original's)
    // 0xCE0, 0xCE8 the constructor news both; allocEntryRes locks the second (the names are not the original's)
    CriticalSection* m_cs;
    CriticalSection* m_entryResCs;
    // 0xCF0 the entry resources: term releases each, allocEntryRes finds one by file name (the name is not the
    // original's)
    mm::mtl::FixedVector<FileResTh*, 32> m_entryRes;
    unsigned char pad_DF8[0x1];
    bool m_renderStop;  // 0xDF9 renderStop sets it (the name is not the original's)
    unsigned char pad_DFA[0x6];
    DEBDRAW m_debDraw[9];  // 0xE00 setDebDraw's (the name is not the original's)
    unsigned char pad_E48[0x8];
};
}  // namespace ml

#endif
