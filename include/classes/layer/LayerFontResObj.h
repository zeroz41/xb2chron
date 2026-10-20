#ifndef CLASSES_LAYER_LAYERFONTRESOBJ_H
#define CLASSES_LAYER_LAYERFONTRESOBJ_H

namespace layer {
// table 0x7100B80670
class LayerFontResObj {
public:
    virtual ~LayerFontResObj();  // slot 0
    virtual void release();  // slot 2
    virtual void setupResource();  // slot 3
};
}  // namespace layer

#endif
