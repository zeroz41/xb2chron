#ifndef CLASSES_ML_DEVFILEREADERTH_H
#define CLASSES_ML_DEVFILEREADERTH_H

namespace ml {
// table 0x7100B773F0
class DevFileReaderTh {
public:
    virtual ~DevFileReaderTh();  // slot 0
    virtual void asyncUpdate();  // slot 2
    virtual void getJobType() const;  // slot 3
    virtual void getReader();  // slot 4
};
}  // namespace ml

#endif
