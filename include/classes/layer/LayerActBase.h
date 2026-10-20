#ifndef CLASSES_LAYER_LAYERACTBASE_H
#define CLASSES_LAYER_LAYERACTBASE_H

namespace layer {
// table none (its derived classes')
class LayerActBase {
public:
    virtual ~LayerActBase();  // slot 0
    virtual void vf1() = 0;  // slot 1
    virtual void vf2() = 0;  // slot 2
    virtual void vf3() = 0;  // slot 3
    virtual void vf4() = 0;  // slot 4
    virtual void vf5() = 0;  // slot 5
    virtual void vf6() = 0;  // slot 6
    virtual void vf7() = 0;  // slot 7
    virtual void vf8() = 0;  // slot 8
    virtual void vf9() = 0;  // slot 9
    virtual void vf10() = 0;  // slot 10
};
}  // namespace layer

#endif
