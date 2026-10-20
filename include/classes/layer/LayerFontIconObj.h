#ifndef CLASSES_LAYER_LAYERFONTICONOBJ_H
#define CLASSES_LAYER_LAYERFONTICONOBJ_H

namespace layer {
// table 0x7100B80640
class LayerFontIconObj {
public:
    virtual ~LayerFontIconObj();  // slot 0
    virtual void release();  // slot 2
    virtual void setupResource();  // slot 3
};
}  // namespace layer

#endif
