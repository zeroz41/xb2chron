#ifndef CLASSES_EVENT_STMPACKMEMORY_H
#define CLASSES_EVENT_STMPACKMEMORY_H

#include "classes/event/IStmMemory.h"
#include "classes/event/StmPackData.h"
#include "classes/event/StmPackHeader.h"
#include "classes/event/StmPackRes.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mtl/AllocHandle.h"

namespace mm { template <typename> class Rect; }

namespace event {
// table 0x7100B3C470; MotstmManager::create makes one of 0x58f8 bytes
class StmPackMemory : public ::event::IStmMemory {
public:
    // one stream pack loadStream makes (0x130 bytes; the name is not the original's); the destructor clears its
    // data and header before deleting it
    struct Pack {
        explicit Pack(const char* name) : m_name(name) {}
        mm::mtl::FixStr<128> m_name;  // loadStream's first name
        StmPackHeader m_header;  // 0x88
        StmPackData m_data;  // 0x98
    };

    virtual ~StmPackMemory();  // slot 0
    virtual void update();  // slot 2
    virtual void render(mm::Rect<int> const&, float);  // slot 3
    // the address of the named entry of the current pack, its size in the second parameter
    virtual void* adr(char const*, unsigned long*);  // slot 5
    virtual void free(void*, int);  // slot 6
    virtual bool isLoadingPrio(float) const;  // slot 7
    virtual bool isFailure() const;  // slot 8
    // a new pack named by the first name, its header and data requested by the other two (SeqManager::setupScene)
    void loadStream(const char* name, const char* header, const char* data);
    // 1.0.0's StmPackMemory::freeCut (0x71000A41B4, out of line there; 3.0.1 inlines it in update): drops the oldest
    // cut once it was freed and waited for, or when it belongs to an earlier pack
    void freeCut() {
        if (!pad_30.empty()) {
            StmPackRes& res = *pad_30.begin();
            if (((res.pad_4 & 2) && res.pad_0 <= 0 && (res.pad_8 < 0 || res.pad_8-- == 0)) || res.pad_50 < pad_58f0) {
                unsigned long pageEnd = res.pad_40;
                pad_30.erase(pad_30.begin());
                if (pad_30.empty()) {
                    pad_20 = pageEnd;
                } else {
                    pad_20 = pad_30.begin()->pad_38;
                }
            }
        }
    }
    // the next cuts of the current pack read into the buffer's free pages, or the next pack opened
    bool loadCut();
    // whether the cut being read has arrived (then the next cut's priority is kept)
    bool waitCut();
    // as many entries from the next one as fit in size bytes read to adr, from page on; the page after them in next
    bool loadCut(void* adr, unsigned long size, unsigned long page, unsigned long& next);
    // entries first..last (size bytes) read to adr, pages pageStart..pageEnd, recorded as a StmPackRes
    void loadCut(void* adr, unsigned long size, unsigned long first, unsigned long last, unsigned long pageStart,
                 unsigned long pageEnd, int prio);
    // 1.0.0's StmPackMemory::isBusy (0x71000A3D14, out of line there): a pack's data still reading
    bool isBusy() {
        for (unsigned long i = 0; i < pad_5860.size(); i++) {
            if (pad_5860[i]->m_data.isBusy()) {
                return true;
            }
        }
        return false;
    }

    unsigned int pad_8;  // flags: bit 0 the buffer is allocated, bit 1 waiting for a cut, bit 2 stop
    mtl::ALLOC_HANDLE pad_c;  // MotstmManager::create's handle
    void* pad_10;  // the buffer the destructor deallocates
    unsigned long pad_18;  // its size in 0x1000-byte pages
    unsigned long pad_20;  // first page still in use (freeCut moves it on)
    unsigned long pad_28;  // next free page (loadCut moves it on)
    mm::mtl::FixedVector<StmPackRes, 256> pad_30;  // the cuts read into the buffer
    unsigned long pad_5838;  // the current pack's next entry to read
    unsigned int pad_5840;  // isLoadingPrio compares it with the priority
    unsigned long pad_5848;  // the size loadCut found for its first entry
    unsigned long pad_5850;  // the room loadCut had for it
    unsigned int pad_5858;  // counts the reads, each StmPackRes keeps its number
    mm::mtl::FixedVector<Pack*, 16> pad_5860;  // loadStream's packs
    unsigned long pad_58e8;  // index of the pack isFailure checks
    unsigned long pad_58f0;  // index of the current pack
};
}  // namespace event

#endif
