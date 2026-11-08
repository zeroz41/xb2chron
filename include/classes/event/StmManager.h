#ifndef CLASSES_EVENT_STMMANAGER_H
#define CLASSES_EVENT_STMMANAGER_H

#include "classes/event/IStmMemory.h"
#include "classes/event/StmPackMemory.h"
#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3C4C8
class StmManager {
public:
    virtual ~StmManager();  // slot 0 (the key function)
    // 1.0.0's StmManager::destroy (3.0.1 inlines it into MotstmManager::OnEventProc)
    inline void destroy();
    // news (from mem) the StmPackMemory with the handle and sets pad_8 bit 0 (inline: MotstmManager::create's copy
    // loads the handle after the memory manager's and before the allocation, as by-value parameters of an inlined
    // call; defined in CharaObj.cpp; the names are not the original's)
    inline void create(mtl::ALLOC_HANDLE mem, mtl::ALLOC_HANDLE handle);
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
    // 1.0.0's StmManager::stopStream and isBusy (0x71000A51C8, 0x71000A51E0; 3.0.1 inlines them)
    void stopStream() {
        if (m_stm != nullptr) {
            m_stm->pad_8 |= 4;
        }
    }
    bool isBusy() {
        if (m_stm == nullptr) {
            return false;
        }
        return m_stm->isBusy();
    }
    unsigned int pad_8;  // destroy zeroes it
    mm::mtl::FixStr<64> pad_c;  // the constructor's name (MotstmManager's: "streaming 1(eva lgt hkt)")
    // 0x50: MotstmManager::create stores a new StmPackMemory here; destroy and the destructor delete it (the
    // name is not the original's); a StmPackMemory: 1.0.0's stopStream and isBusy read its fields directly
    StmPackMemory* m_stm;
};
}  // namespace event

#endif
