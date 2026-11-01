#ifndef CLASSES_EVENT_STMMANAGER_H
#define CLASSES_EVENT_STMMANAGER_H

#include "classes/event/IStmMemory.h"
#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3C4C8
class StmManager {
public:
    virtual ~StmManager();  // slot 0 (the key function)
    // 1.0.0's StmManager::destroy (3.0.1 inlines it into MotstmManager::OnEventProc)
    inline void destroy();
    // 1.0.0's StmManager(const char*) (0x71000A4F7C, out of line there; 3.0.1 inlines it into
    // Singleton<MotstmManager>::getPtr)
    explicit StmManager(const char* name) : pad_8(0), pad_c(name), m_stm(nullptr) {}
    // 1.0.0's StmManager::adr and free (0x71000A52A4, 0x71000A52BC; 3.0.1 inlines them)
    void* adr(const char* name, unsigned long* size) {
        if (m_stm == nullptr) {
            return nullptr;
        }
        return m_stm->adr(name, size);
    }
    void free(void* p, int n) {
        if (m_stm != nullptr) {
            m_stm->free(p, n);
        }
    }
    unsigned int pad_8;  // destroy zeroes it
    mm::mtl::FixStr<64> pad_c;  // the constructor's name (MotstmManager's: "streaming 1(eva lgt hkt)")
    // 0x50: MotstmManager::create stores a new StmPackMemory here; destroy and the destructor delete it (the
    // name is not the original's)
    IStmMemory* m_stm;
};
}  // namespace event

#endif
