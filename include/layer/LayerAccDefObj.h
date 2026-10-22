#ifndef LAYER_LAYERACCDEFOBJ_H
#define LAYER_LAYERACCDEFOBJ_H

#include "layer/LayerAccObjBase.h"

namespace layer { class LayerBase; }

namespace layer {
// how a default object is drawn as a gauge (0: not one; UIImageObject's setExtType maps its types 1-4 to 3, 1, 4, 2)
enum LAYER_GAUGE : int {};

// access to a default (image) layer object: its icon (image) number and gauge
class LayerAccDefObj : public LayerAccObjBase {
public:
    LayerAccDefObj(LayerBase* layer);
    void setParm(float param);  // the gauge's value
    void setIconNum(unsigned short num);
    unsigned short getIconNum() const;
    unsigned short getIconMax() const;  // the last icon number (one less than the count)
    void setGauge(LAYER_GAUGE gauge);
    LAYER_GAUGE getGauge() const;
};
}  // namespace layer

#endif
