#ifndef LAYER_LAYERACCACTION_H
#define LAYER_LAYERACCACTION_H

namespace layer { class LayerBase; }

namespace layer {
// access to a layer object's actions (animations): UIImageObject starts, stops and reads them
class LayerAccAction {
public:
    LayerAccAction(LayerBase* layer);
    bool isActionData() const;  // it has actions
    bool isRunning() const;
    unsigned int getRunningActIdx() const;
    void setRunningActSec(float sec);
    unsigned int getActionMax() const;
    float getActionSec(unsigned int index) const;  // the action's length in seconds
    void actionIdx(unsigned int index);  // starts the action
    void actionID(unsigned int id);
    void actionName(const char* name);
    void actionEnd();

    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
