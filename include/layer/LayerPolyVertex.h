#ifndef LAYER_LAYERPOLYVERTEX_H
#define LAYER_LAYERPOLYVERTEX_H

namespace layer {
// one vertex of a layer polygon, 0x14 bytes (UIShape::writeVertex copies them at that stride)
struct LayerPolyVertex {
    float x;
    float y;
    // its colour's bytes: UIShape::setupBuffer sets each to 0xFF (a, b, g, r in turn), UIShapeRing all four as one
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    float u;  // UIShapeRing's outer edge has v 0, its inner edge v 1
    float v;
};

}  // namespace layer

#endif
