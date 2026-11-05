#ifndef LAYER_LAYERVIEWPORT_H
#define LAYER_LAYERVIEWPORT_H

namespace layer {
// a viewport rectangle LayerObjUtil::calcLayerRenderView offsets by a matrix's translation (the field names are not
// the original's)
class LayerViewPort {
public:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
};
}  // namespace layer

#endif
