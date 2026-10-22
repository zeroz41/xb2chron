#ifndef CLASSES_FW_SOUNDREFERENCEOBJECT_H
#define CLASSES_FW_SOUNDREFERENCEOBJECT_H

namespace fw {
// table none (its derived classes'): a sound object that counts its references (sound_ssd_drv.cpp's release
// asserts `m_RefCount > 0`, destroys the object through slot 0 and frees it with mtl::MemManager::deallocate
// when the count reaches 0)
class SoundReferenceObject {
public:
    SoundReferenceObject() : m_RefCount(0) {}
    virtual ~SoundReferenceObject() {}  // slot 0
    // one more reference (mm::mtl::IntrusivePtr's; the name is not the original's)
    void addRef() {
        ++m_RefCount;
    }
    int release();

    int m_RefCount;
};
}  // namespace fw

#endif
