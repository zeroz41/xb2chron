#ifndef CLASSES_SSD_STREAMBUFFER_H
#define CLASSES_SSD_STREAMBUFFER_H

namespace ssd {
// table 0x7100B82380
class StreamBuffer {
public:
    virtual void GetBufferSize() const;  // slot 0
    virtual void GetDataSize() const;  // slot 1
    virtual void GetFreeSize() const;  // slot 2
};
}  // namespace ssd

#endif
