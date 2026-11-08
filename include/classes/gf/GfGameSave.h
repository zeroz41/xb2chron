#ifndef CLASSES_GF_GFGAMESAVE_H
#define CLASSES_GF_GFGAMESAVE_H

#include "classes/ml/IWorkEvent.h"
#include "classes/gf/GfAllocator.h"
#include "gf/SDataSaveIra.h"
#include "mm/mtl/FixStr.h"
#include "gf/SDataOption.h"
#include "classes/gf/GfDataZlib.h"

namespace ml { class EventFileTh; class FileHandleTh; }
namespace gf { enum SAVESLOT : int; class SDataOption; }

namespace gf {
// table 0x7100B55E50
class GfGameSave : public ::ml::IWorkEvent {
public:
    virtual ~GfGameSave();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    static SDataSaveIra* getGameSaveData();
    static SDataSaveIra* getIraGameSaveData();  // 2.0.0's symbols name it; returns the save data, as getGameSaveData
    static void makeNewGameSaveData();

    // 1.0.0's took the slot only; 3.0.1's adds three flags (stored at 0x30-0x32, each masked to a bool)
    GfGameSave(SAVESLOT slot, bool, bool, bool);
    void execGameSaveWithMicroThread();
    void execOptionSaveWithMicroThread();
    void createGameSaveData(mm::mtl::FixStr<256>& name);
    void createOptionSaveData(mm::mtl::FixStr<256>& name);

    // named by 1.0.0 (inline in 3.0.1: the destructor and OnFileEvent carry its code)
    void destroySaveData() {
        m_writeData = nullptr;
        m_writeSize = 0;
        if (m_saveData != nullptr) {
            m_saveData->~SDataSaveIra();
            getAllocator(ALLOCATOR(0))->deallocate(m_saveData);
            m_saveData = nullptr;
        }
        if (m_optionData != nullptr) {
            getAllocator(ALLOCATOR(0))->deallocate(m_optionData);
            m_optionData = nullptr;
        }
    }

    // (the field names are not the original's)
    int m_state;  // 1 while a write waits for OnFileEvent
    SAVESLOT m_slot;
    SDataSaveIra* m_saveData;  // createGameSaveData's copy, from allocator 0
    SDataOption* m_optionData;  // createOptionSaveData's, from allocator 0
    const void* m_writeData;
    unsigned long m_writeSize;
    bool m_flag30;
    bool m_flag31;
    bool m_flag32;
    GfDataZlib m_zlib;               // 0x38: compresses the save when GfGameManager::isGameTypeIra says so
    ml::FileHandleTh* m_fileHandle;  // 0x78: the write's handle, none once it ended
    int m_fileKind;                  // the end event's m_kind
};
}  // namespace gf

#endif
