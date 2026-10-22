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
};
}  // namespace effect

#endif
