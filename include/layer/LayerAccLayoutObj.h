#ifndef LAYER_LAYERACCLAYOUTOBJ_H
#define LAYER_LAYERACCLAYOUTOBJ_H

namespace layer { class LayerBase; }
namespace grlib { class CGLibTextureBuffer; }

namespace layer {
// the layer memory type a memory object is made in (UIScreenObject::OnMemoryInfo's second byte)
enum LayerMemType {};
// the primitives a polygon object draws (UIPolygonObject makes its objects with 0)
enum LayerPrimitiveType {};
// how a layout anchors its objects (UILayoutObject::create sets 2)
enum LAYER_ANCHOR {};

// access to a layout layer object: makes the objects under it (UIScreenObject::create and createOnMemory)
class LayerAccLayoutObj {
public:
    LayerAccLayoutObj(LayerBase* layer);
    void setViewPortMode(bool enable);
    void setViewPort(float x, float y, float width, float height);
    void createPriorityTbl(unsigned int count);
    void setAutoAnchorMode(LAYER_ANCHOR anchor);
    LayerBase* createObj(const void* resource);  // the objects made under it, or null
    LayerBase* createMaskObj(const void* resource);
    LayerBase* createFontObj();
    LayerBase* createLayoutObj();
    LayerBase* createTexObj(const grlib::CGLibTextureBuffer& texture);  // the object made, or null
    LayerBase* createMemObj(unsigned int width, unsigned int height, LayerMemType type);  // the object made, or null
    // a polygon object of vertexCount vertices and indexCount indices under it; null when it makes none
    LayerBase* createPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                             unsigned short indexCount, LayerPrimitiveType type);

    LayerBase* m_layer;  // the constructor's
    unsigned char pad_08[0x8];  // 0x10 long: its users' frames keep 0x10 for it
};
}  // namespace layer

#endif
