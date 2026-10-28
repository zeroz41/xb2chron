#ifndef CLASSES_ML_DEVGRAPHCB_H
#define CLASSES_ML_DEVGRAPHCB_H

namespace ml {
// table 0x7100B75E00
class DevGraphCB {
public:
    // enters itself in DevGraph's callback list (m_cbList); the destructor removes it
    DevGraphCB();
    virtual ~DevGraphCB();  // slot 0
    virtual void viBeginFrame() {}  // slot 2
    // inline: 3.0.1 keeps fw/PadManager.cpp's copies (0x7100196B04 on)
    virtual void viBeforeDrawDone() {}  // slot 3
    virtual void viAfterDrawDone() {}  // slot 4
    virtual void viAfterSync() {}  // slot 5
    virtual void viAfterRenderCall() {}  // slot 6
};
}  // namespace ml

#endif
