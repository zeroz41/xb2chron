#ifndef CLASSES_GF_GFGAMELOAD_H
#define CLASSES_GF_GFGAMELOAD_H

#include "classes/ml/IWorkEvent.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfGameSave.h"

namespace gf { enum SAVESLOT : int; class SDataSave; class SDataOption; }
namespace ml { class FileHandleTh; }

namespace gf {
// table 0x7100B55EA0 (the symbols leave it unnamed; 1.0.0's GfGameLoad has the same slots: its OnFileEvent is the
// size of slot 7's 0x71002C1DAC): loads a save or option file in the background
class GfGameLoad : public ::ml::IWorkEvent {
public:
    virtual ~GfGameLoad();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh* event);  // slot 7
    // named by 1.0.0 (same table store, the slot at 0xC); 3.0.1's also stores fn_71002A9E68's answer at 8
    GfGameLoad(SAVESLOT slot);
    void getGameFileNameBin(mm::mtl::FixStr<256>& out);
    void getOptionFileNameBin(mm::mtl::FixStr<256>& out);
    // named by 1.0.0: call-site (1.0.0's OnFileEvent calls phaseBinData where 3.0.1's calls this)
    void phaseBinData();
    void execGameLoadWithMicroThread(SDataSave& save);

    // (the field names are not the original's)
    bool m_ira;            // GfGameManager::fn_71002A9E68 as it was made: the Torna ("ira") files' names are used
    SAVESLOT m_slot;
    mm::mtl::FixStr<256> m_fileName;  // a file to load instead of the slot's
    SDataSave* m_saveData;      // 0x118: from allocator 0 (execGameLoadWithMicroThread), freed by phaseBinData
    SDataOption* m_optionData;  // 0x120: from allocator 0, freed by phaseBinData
    int m_state;           // 1 while a read waits for OnFileEvent
    ml::FileHandleTh* m_fileHandle;  // the read's handle, none once it ended
    int m_fileKind;        // the end event's m_kind
    int m_fileResult;      // the end event's m_result, for kind 2 (-1 as made)
    void* m_dest;          // 0x140: the caller's SDataSave/SDataOption the load fills
    unsigned char pad_148[0x8];
    void* m_copyDest;      // 0x150: phaseBinData copies m_readSize bytes of m_readData there
    void* m_readData;
    unsigned long m_readSize;
    GfGameSaveCompress m_decompress;   // 0x168
    GfGameSaveCompress m_decompress2;  // 0x188
};
}  // namespace gf

#endif
