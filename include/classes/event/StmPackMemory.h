#ifndef CLASSES_EVENT_STMPACKMEMORY_H
#define CLASSES_EVENT_STMPACKMEMORY_H

#include "classes/event/IStmMemory.h"
#include "classes/event/StmPackData.h"
#include "classes/event/StmPackHeader.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mtl/AllocHandle.h"

namespace mm { template <typename> class Rect; }

namespace event {
// table 0x7100B3C470; MotstmManager::create makes one of 0x58f8 bytes
class StmPackMemory : public ::event::IStmMemory {
public:
    // a region of the buffer handed out by adr (the name is not the original's)
    struct Block {
        int pad_0;  // adr counts it up, free down
        unsigned int pad_4;  // bit 0: skipped by adr and free; bit 1: set by free
        int pad_8;
        unsigned char pad_c[4];
        unsigned long pad_10;  // address of the region (free's range start)
        unsigned long pad_18;  // size of the region
        unsigned long pad_20;
        unsigned long pad_28;  // adr's first entry index
        unsigned long pad_30;  // adr's last entry index
        unsigned long pad_38;
        unsigned long pad_40;
        unsigned long pad_48;
        unsigned long pad_50;  // pack index adr compares with pad_58f0
    };
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

    unsigned int pad_8;  // flags: bit 0 the buffer is allocated, bit 1 waiting for a cut, bit 2 stop
    mtl::ALLOC_HANDLE pad_c;  // MotstmManager::create's handle
    void* pad_10;  // the buffer the destructor deallocates
    unsigned long pad_18;  // its size in 0x1000-byte pages
    unsigned long pad_20;
    unsigned long pad_28;
    mm::mtl::FixedVector<Block, 256> pad_30;
    unsigned long pad_5838;
    unsigned int pad_5840;  // isLoadingPrio compares it with the priority
    unsigned long pad_5848;
    unsigned long pad_5850;
    unsigned int pad_5858;
    mm::mtl::FixedVector<Pack*, 16> pad_5860;  // loadStream's packs
    unsigned long pad_58e8;  // index of the pack isFailure checks
    unsigned long pad_58f0;  // index of the current pack
};
}  // namespace event

#endif
