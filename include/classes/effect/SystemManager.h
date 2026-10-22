#ifndef CLASSES_EFFECT_SYSTEMMANAGER_H
#define CLASSES_EFFECT_SYSTEMMANAGER_H

namespace effect {
// table 0x7100B80770
class SystemManager {
public:
    virtual ~SystemManager();  // slot 0
    static SystemManager*& getPtr();  // the system's manager, null while there is none
    // registers effect resource `data` (`size` bytes); null when it cannot
    void* es_regist(void* data, unsigned int size);
    void es_free(void* handle);

    unsigned char pad_8[0x87245];
    // the stream renderers lock and unlock the second half of their double buffer while set (the name is not the
    // original's)
    bool m_secondBuffer;
};
}  // namespace effect

#endif
