#ifndef LAYER_LAYERACCLAYOUTOBJ_H
#define LAYER_LAYERACCLAYOUTOBJ_H

namespace layer { class LayerBase; }
namespace grlib { class CGLibTextureBuffer; }

namespace layer {
// the layer memory type a memory object is made in (UIScreenObject::OnMemoryInfo's second byte)
enum LayerMemType {};

// access to a layout layer object: makes the objects under it (UIScreenObject::create and createOnMemory)
class LayerAccLayoutObj {
public:
    LayerAccLayoutObj(LayerBase* layer);
    LayerBase* createTexObj(const grlib::CGLibTextureBuffer& texture);  // the object made, or null
    LayerBase* createMemObj(unsigned int width, unsigned int height, LayerMemType type);  // the object made, or null

    LayerBase* m_layer;  // the constructor's
    unsigned char pad_08[0x8];  // 0x10 long: its users' frames keep 0x10 for it
};
}  // namespace layer

#endif
