#ifndef CLASSES_GF_GFGAMELOAD_H
#define CLASSES_GF_GFGAMELOAD_H

#include "classes/ml/IWorkEvent.h"
#include "mm/mtl/FixStr.h"

namespace gf { enum SAVESLOT : int; }
namespace ml { class FileHandleTh; }

namespace gf {
// table 0x7100B55EA0 (the symbols leave it unnamed; 1.0.0's GfGameLoad has the same slots: its OnFileEvent is the
// size of slot 7's 0x71002C1DAC): loads a save or option file in the background
class GfGameLoad : public ::ml::IWorkEvent {
public:
    virtual ~GfGameLoad();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh* event);  // slot 7
    void getGameFileNameBin(mm::mtl::FixStr<256>& out);
    void getOptionFileNameBin(mm::mtl::FixStr<256>& out);
    // named by 1.0.0: call-site (1.0.0's OnFileEvent calls phaseBinData where 3.0.1's calls this)
    void phaseBinData();

    // (the field names are not the original's)
    bool m_ira;            // GfGameManager::fn_71002A9E68 as it was made: the Torna ("ira") files' names are used
    SAVESLOT m_slot;
    mm::mtl::FixStr<256> m_fileName;  // a file to load instead of the slot's
    unsigned char pad_118[0x10];
    int m_state;           // 1 while a read waits for OnFileEvent
    unsigned char pad_12c[0x4];
    ml::FileHandleTh* m_fileHandle;  // the read's handle, none once it ended
    int m_fileKind;        // the end event's m_kind
    int m_fileResult;      // the end event's m_result, for kind 2
};
}  // namespace gf

#endif
