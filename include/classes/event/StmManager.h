#ifndef CLASSES_EVENT_STMMANAGER_H
#define CLASSES_EVENT_STMMANAGER_H

namespace event { class IStmMemory; }

namespace event {
// table 0x7100B3C4C8
class StmManager {
public:
    virtual ~StmManager();  // slot 0 (the key function)
    // 1.0.0's StmManager::destroy (3.0.1 inlines it into MotstmManager::OnEventProc)
    inline void destroy();
    unsigned int pad_8;  // destroy zeroes it
    unsigned char pad_c[0x44];
    // 0x50: MotstmManager::create stores a new StmPackMemory here; destroy and the destructor delete it (the
    // name is not the original's)
    IStmMemory* m_stm;
};
}  // namespace event

#endif
