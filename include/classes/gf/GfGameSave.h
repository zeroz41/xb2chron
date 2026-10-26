#ifndef CLASSES_GF_GFGAMESAVE_H
#define CLASSES_GF_GFGAMESAVE_H

#include "classes/ml/IWorkEvent.h"
#include "classes/gf/GfAllocator.h"
#include "gf/SDataSave.h"
#include "mm/mtl/FixStr.h"
#include "gf/SDataOption.h"

namespace ml { class EventFileTh; class FileHandleTh; }
namespace gf { enum SAVESLOT : int; class SDataOption; }

namespace gf {
// data a save writes, compressed on a thread named "CompressThread" (fn_71002C131C) when
// GfGameManager::fn_71002A9E68 says so (the name and the member names are not the original's)
struct GfGameSaveCompress {
    GfGameSaveCompress() : m_src(nullptr), m_srcSize(0), m_out(nullptr), m_outSize(0) {}
    ~GfGameSaveCompress() {
        unsigned char* out = m_out;
        m_out = nullptr;
        if (out != nullptr) {
            delete out;
        }
    }

    const void* m_src;
    unsigned long m_srcSize;
    unsigned char* m_out;  // the compressed bytes
    unsigned long m_outSize;
};

// table 0x7100B55E50
class GfGameSave : public ::ml::IWorkEvent {
public:
    virtual ~GfGameSave();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    static SDataSave* getGameSaveData();
    static SDataSave* getGameOptionData();  // 3.0.1's returns the save data, as getGameSaveData
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
            m_saveData->~SDataSave();
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
    SDataSave* m_saveData;  // createGameSaveData's copy, from allocator 0
    SDataOption* m_optionData;  // createOptionSaveData's, from allocator 0
    const void* m_writeData;
    unsigned long m_writeSize;
    bool m_flag30;
    bool m_flag31;
    bool m_flag32;
    GfGameSaveCompress m_compress;   // 0x38
    GfGameSaveCompress m_compress2;  // 0x58
    ml::FileHandleTh* m_fileHandle;  // 0x78: the write's handle, none once it ended
    int m_fileKind;                  // the end event's m_kind
};
}  // namespace gf

#endif
