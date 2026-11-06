#ifndef CLASSES_EVENT_STMPACKDATA_H
#define CLASSES_EVENT_STMPACKDATA_H

#include "classes/ml/IWorkEvent.h"
#include "classes/ml/DevFileTh.h"
#include "ml/DevFileParamTh.h"
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

    // 1.0.0's StmPackData::open (0x71000A3870, out of line there): the named file opened, this hearing its events
    bool open() {
        pad_90 = nullptr;
        ml::DevFileParamTh param;
        param.m_listener = this;
        param.m_path = pad_c.m_str;
        pad_90 = ml::DevFileTh::rfOpen(param);
        return pad_90 != nullptr;
    }
    // 1.0.0's StmPackData::close (0x71000A383C, out of line there)
    void close() {
        if (pad_90 != nullptr) {
            ml::DevFileTh::rfIsBusy(pad_90);
            ml::DevFileTh::rfClose(pad_90);
            pad_90 = nullptr;
        }
    }
    // 1.0.0's StmPackData::read (0x71000A38F4, out of line there): size bytes from file offset ofs read to adr
    void read(void* adr, unsigned long size, unsigned long ofs) {
        pad_8 |= 1;
        ml::DevFileParamTh param;
        param.m_buffer = adr;
        param.pad_4c = ofs;
        param.pad_50 = size;
        param.m_size = size;
        param.m_prio = ml::FILE_PRIO(1);
        ml::DevFileTh::rfRead(pad_90, param);
    }
    // 1.0.0's StmPackData::isSuccess (0x71000A3980, out of line there): opened and no read running
    bool isSuccess() const {
        if (pad_90 == nullptr || (pad_8 & 1)) {
            return false;
        }
        return !ml::DevFileTh::rfIsBusy(pad_90);
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
