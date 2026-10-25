#ifndef LAYER_LAYERRCEMANAGER_H
#define LAYER_LAYERRCEMANAGER_H

namespace layer {
class LayerManager;

// built from layer::LayerManager (its code shares LayerShdManager's file); the field names are not the original's
class LayerRceManager {
public:
    LayerRceManager(LayerManager* manager);
    ~LayerRceManager();
    void update();

    LayerManager* m_pManager;  // 0x00, the constructor's argument
    unsigned char pad_08[0x60];
};
}  // namespace layer

#endif
