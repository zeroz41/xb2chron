#ifndef CLASSES_ML_THREADVAL_H
#define CLASSES_ML_THREADVAL_H

namespace ml {
// a template: 6 instances in the module. A value kept twice: tvSwap copies the calculation thread's copy over
// the render thread's and swaps the two buffers (threadval<ScnObjCam::RENDER_INFO>::tvSwap)
template <typename T0>
class threadval {
public:
    virtual ~threadval();  // slot 0
    virtual void tvSwap();  // slot 2
    virtual void getCpuBank() const;  // slot 3
    virtual void setCpuBank(unsigned char);  // slot 4

    T0* m_render;  // what tvSwap copies m_cpu into (the name is not the original's)
    T0* m_cpu;     // what ScnObjCam::setLookAt writes (the name is not the original's)
};
}  // namespace ml

#endif
