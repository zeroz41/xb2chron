#ifndef CLASSES_GF_GFGAMESAVE_H
#define CLASSES_GF_GFGAMESAVE_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }
namespace gf { enum SAVESLOT : int; }

namespace gf {
// table 0x7100B55E50
class GfGameSave : public ::ml::IWorkEvent {
public:
    virtual ~GfGameSave();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    // 1.0.0's took the slot only; 3.0.1's adds three flags (stored at 0x30-0x32, each masked to a bool)
    GfGameSave(SAVESLOT slot, bool, bool, bool);
    void execGameSaveWithMicroThread();
    void execOptionSaveWithMicroThread();

    unsigned char pad_8[0x80];  // the constructor zeroes 8-0x2F and 0x38-0x83, sets the slot at 0xC
};
}  // namespace gf

#endif
