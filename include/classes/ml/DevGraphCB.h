#ifndef CLASSES_ML_DEVGRAPHCB_H
#define CLASSES_ML_DEVGRAPHCB_H

namespace ml {
// table 0x7100B75E00
class DevGraphCB {
public:
    virtual ~DevGraphCB();  // slot 0
    virtual void viBeginFrame();  // slot 2
    virtual void viBeforeDrawDone();  // slot 3
    virtual void viAfterDrawDone();  // slot 4
    virtual void viAfterSync();  // slot 5
    virtual void viAfterRenderCall();  // slot 6
};
}  // namespace ml

#endif
