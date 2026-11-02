#ifndef CLASSES_EVENT_STMPACKDATA_H
#define CLASSES_EVENT_STMPACKDATA_H

#include "classes/ml/IWorkEvent.h"
#include "classes/ml/DevFileTh.h"
#include "mm/mtl/FixStr.h"

namespace ml { class EventFileTh; class FileHandleTh; }

namespace event {
// table 0x7100B3C420
class StmPackData : public ::ml::IWorkEvent {
public:
    // inline (StmPackMemory::loadStream builds one in each pack)
    StmPackData() : pad_8(0), pad_90(nullptr) {}
    virtual ~StmPackData();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
    // closes what it held, then keeps the name
    void create(const char* name);

    // inline: the destructor and create() share it (the name is not the original's)
    void clear() {
        if (pad_90 != nullptr) {
            ml::DevFileTh::rfIsBusy(pad_90);
            ml::DevFileTh::rfClose(pad_90);
            pad_90 = nullptr;
        }
        pad_c = "";
        pad_8 = 0;
    }

    // 1.0.0's StmPackData::isBusy (0x71000A3968, out of line there)
    bool isBusy() const {
        if (pad_8 & 1) {
            return true;
        }
        return ml::DevFileTh::rfIsBusy(pad_90);
    }

    unsigned int pad_8;  // bit 0 cleared by OnFileEvent when a read ended (event kind 2)
    mm::mtl::FixStr<128> pad_c;  // create's name
    ml::FileHandleTh* pad_90;  // the handle the destructor closes (DevFileTh::rfClose)
};
}  // namespace event

#endif
