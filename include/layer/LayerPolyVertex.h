#ifndef LAYER_LAYERPOLYVERTEX_H
#define LAYER_LAYERPOLYVERTEX_H

namespace layer {
// one vertex of a layer polygon, 0x14 bytes (UIShape::writeVertex copies them at that stride)
struct LayerPolyVertex {
    float x;
    float y;
    unsigned int color;  // UIShapeRing writes 0xFFFFFFFF
    float u;             // UIShapeRing's outer edge has v 0, its inner edge v 1
    float v;
};
}  // namespace layer

#endif
