#ifndef CLASSES_LAYER_LAYERMANAGER_H
#define CLASSES_LAYER_LAYERMANAGER_H

#include "classes/ml/IDrDrawCallback.h"

#include "mtl/AllocHandle.h"

namespace ml { class IDrDrawWorkInfo; }
namespace ml { class Scn; }
namespace layer { class LayerObjManager; }
namespace layer { class LayerFontManager; }
#include "layer/LayerAccManager.h"

namespace layer {
// a base of layer::LayerManager no evidence names yet
class TUnk_B7F8F0 {
public:
    virtual ~TUnk_B7F8F0();
};
// table 0x7100B7F890; base at 0x8 unknown (TUnk_B7F8F0)
class LayerManager : public ::ml::IDrDrawCallback, public TUnk_B7F8F0 {
public:
    LayerManager(ml::Scn* scn, mtl::ALLOC_HANDLE handle, unsigned int size);
    virtual ~LayerManager();  // slot 0
    void tail();  // the end of a frame
    unsigned char pad_10[0x50];  // 0xB0 bytes: fw::LayerSetManager::initialize allocates that
    // The names follow LayerAccManager's functions that use them (not the original's).
    LayerObjManager* m_objManager;  // LayerAccManager's create functions
    LayerFontManager* m_fontManager;  // LayerAccManager's font create functions
    unsigned char pad_70[0x2C];
    LayerCoordinate m_coordinate;  // LayerAccManager::set/getCoordinate
    unsigned char pad_A0[0x10];
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
