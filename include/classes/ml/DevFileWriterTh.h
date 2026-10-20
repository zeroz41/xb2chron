#ifndef CLASSES_ML_DEVFILEWRITERTH_H
#define CLASSES_ML_DEVFILEWRITERTH_H

namespace ml {
// table none (its derived classes')
class DevFileWriterTh {
public:
    virtual ~DevFileWriterTh();  // slot 0
    virtual void asyncUpdate() = 0;  // slot 2
    virtual void getJobType() const;  // slot 3
};
}  // namespace ml

#endif
