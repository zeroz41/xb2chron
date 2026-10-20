#ifndef CLASSES_FW_SOUNDRESOURCE_H
#define CLASSES_FW_SOUNDRESOURCE_H

namespace fw {
// table 0x7100B42B48
class SoundResource {
public:
    virtual ~SoundResource();  // slot 0
    virtual void update();  // slot 2
    virtual void valid() const;  // slot 3
};
}  // namespace fw

#endif
