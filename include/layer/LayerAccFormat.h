#ifndef LAYER_LAYERACCFORMAT_H
#define LAYER_LAYERACCFORMAT_H

namespace layer {
// what a layer resource's header says it is (the constructor reads it); the names are not the original's
class LayerAccFormat {
public:
    LayerAccFormat(const void* data);
    unsigned int m_type;  // 0: none it knows; 1-4: by the header's magic
    bool m_hasData;       // its type 1 header names data (or type 3)
    bool m_flag;          // bit 5 of a type 1 header's flags: UIPolygonObject takes no texture with it set
    bool m_multi;         // a type 1 header with more than one entry
};
}  // namespace layer

#endif
