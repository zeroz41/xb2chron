#ifndef CLASSES_ML_SCNDEBUGMANIPUOBJ_H
#define CLASSES_ML_SCNDEBUGMANIPUOBJ_H

namespace ml {
// table 0x7100B78270
class ScnDebugManipuObj {
public:
    enum RENDER_INFO : int;
    virtual ~ScnDebugManipuObj();  // slot 0
    virtual void vf2() = 0;  // slot 2
    virtual void vf3() = 0;  // slot 3
    virtual void vf4() = 0;  // slot 4
    virtual void vf5() = 0;  // slot 5
    virtual void vf6() = 0;  // slot 6
    virtual void vf7() = 0;  // slot 7
};
}  // namespace ml

#endif
