#ifndef CLASSES_LAYER_LAYERMANAGER_H
#define CLASSES_LAYER_LAYERMANAGER_H

#include "classes/ml/IDrDrawCallback.h"

namespace ml { class IDrDrawWorkInfo; }

namespace layer {
// a base of layer::LayerManager no evidence names yet
class TUnk_B7F8F0 {
public:
    virtual ~TUnk_B7F8F0();
};
// table 0x7100B7F890; base at 0x8 unknown (TUnk_B7F8F0)
class LayerManager : public ::ml::IDrDrawCallback, public TUnk_B7F8F0 {
public:
    virtual ~LayerManager();  // slot 0
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
