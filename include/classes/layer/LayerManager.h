#ifndef CLASSES_LAYER_LAYERMANAGER_H
#define CLASSES_LAYER_LAYERMANAGER_H

#include "classes/ml/IDrDrawCallback.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/layer/LayerHandleAllocator.h"
#include "classes/layer/LayerMemHandleAllocator.h"

#include "mtl/AllocHandle.h"

namespace ml { class IDrDrawWorkInfo; }
namespace ml { class Scn; }
namespace layer { class LayerObjManager; }
namespace layer { class LayerFontManager; }
namespace layer { class LayerShdManager; }
namespace layer { class LayerRceManager; }
#include "layer/LayerAccManager.h"

namespace layer {
// table 0x7100B7F890 (the PtrSingleton base's part at +0x70); 0xB0 bytes: fw::LayerSetManager::initialize allocates that.
// The field names are not the original's: each says what the constructor, destructor and frame functions do with it.
class LayerManager : public ::ml::IDrDrawCallback, public ::mm::mtl::PtrSingleton<LayerManager> {
public:
    LayerManager(ml::Scn* scn, mtl::ALLOC_HANDLE handle, unsigned int size);
    virtual ~LayerManager();  // slot 0
    void beginFastSetup();  // the first setup step: reads the shaders, then waits in loadWait
    void loadWait();  // waits for the shaders, then sets up every frame with defSetup
    void defSetup();  // the setup a frame does once loading is done
    void tail();  // the end of a frame
    float getScreenDivWidth() const;
    float getScreenCalcSclWidth() const;
    float getScreenCalcSclHeight() const;
    float getScreenCalcPosWidth() const;
    float getScreenCalcPosHeight() const;
    // the m_flags / m_params entry objects write this frame, and the one they read back (LayerObj's accessors;
    // the constructor sets 1 and 0)
    static int s_nStkIdx;
    static int s_nDebIdx;
    static int s_nTriIdx;
    enum {
        FLAG_LOADING = 1 << 0,  // set until the shaders are ready: begin..finalRender skip their work
    };
    void (LayerManager::*m_setupFunc)();  // 0x10: what begin calls (beginFastSetup, loadWait, then defSetup)
    mtl::ALLOC_HANDLE m_topHandle;   // 0x20: "LayerTop", from the constructor's handle
    mtl::ALLOC_HANDLE m_dataHandle;  // 0x24: "LayerData", from m_topHandle
    mtl::ALLOC_HANDLE m_workHandle;  // 0x28: "LayerWork", from m_topHandle
    mtl::ALLOC_HANDLE m_gxHandle;    // 0x2C: "LayerGx", from m_topHandle
    LayerHandleAllocator m_workAllocator;  // 0x30: over m_workHandle
    LayerHandleAllocator m_gxAllocator;    // 0x40: over m_gxHandle
    ml::Scn* m_scn;  // 0x50: the constructor's scene (its render system calls this back)
    LayerShdManager* m_shdManager;  // 0x58
    // The names follow LayerAccManager's functions that use them (not the original's).
    LayerObjManager* m_objManager;  // LayerAccManager's create functions
    LayerFontManager* m_fontManager;  // LayerAccManager's font create functions
    LayerRceManager* m_rceManager;  // 0x70
    unsigned int m_flags;  // 0x78: FLAG_
    float m_frameRate;  // 0x7C: 30 (the name is not the original's)
    float m_frameTime;  // 0x80: 1/30 (the name is not the original's)
    float m_timeScale;  // 0x84: 1, set last by the constructor (the name is not the original's)
    // 0x88: 1, 1 and 1, 1, each pair set by one doubleword store (as m_frameRate; the names are not the original's)
    float m_baseColor[4];  // 0x88: 1, 1, 1, 1 (the name is not the original's)
    float m_pixelScale;  // 0x98: 0.003125 = 1/320 (the name is not the original's)
    LayerCoordinate m_coordinate;  // LayerAccManager::set/getCoordinate
    LayerMemHandleAllocator m_allocator;  // 0xA0: over m_workHandle
    virtual void begin();  // slot 2
    virtual void end();  // slot 3
    virtual void apply(ml::IDrDrawWorkInfo const*);  // slot 4
    virtual void opacityRender(ml::IDrDrawWorkInfo const*) {}  // slot 5
    virtual void alphaRender(ml::IDrDrawWorkInfo const*) {}  // slot 6
    virtual void lastRender(ml::IDrDrawWorkInfo const*) {}  // slot 7
    virtual void finalRender(ml::IDrDrawWorkInfo const*);  // slot 9
};
}  // namespace layer

#endif
