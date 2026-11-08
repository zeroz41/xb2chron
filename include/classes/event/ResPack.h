#ifndef CLASSES_EVENT_RESPACK_H
#define CLASSES_EVENT_RESPACK_H

#include "classes/event/IResPackEvent.h"
#include "classes/fw/RenderResource.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"

namespace event {
// table 0x7100B3C058
class ResPack {
public:
    // the pack file func_loading walks (draw shows its count); the names are not the original's
    struct PackData {
        struct Entry {
            unsigned int m_offset;  // 0x0: the file's data, from the pack's start
            unsigned int m_size;  // 0x4
            unsigned char pad_8[8];
            char m_name[0x80];  // 0x10
        };
        unsigned int pad_0;
        unsigned int m_count;  // 0x4
        unsigned char pad_8[8];
        Entry m_entries[1];  // 0x10, m_count of them (0x90 bytes each)
    };

    // inline: ResPackManager::load builds it
    ResPack() : m_event(nullptr), m_func(nullptr), m_res(nullptr) {}
    // out of line, the key function: D2/D0 sit before draw (0x71000B87A0)
    virtual ~ResPack();  // slot 0
    void draw();
    // 1.0.0's ResPack::clear (0x7100097BD4; 3.0.1 inlines it: ResManager::clear)
    void clear() {
        if (m_res != nullptr) {
            m_res->release();
            m_res = nullptr;
        }
        m_handle.m_handle = 0;
        m_func = nullptr;
        m_event = nullptr;
    }
    // 1.0.0's ResPack::update (0x7100097CC8; 3.0.1 inlines it: ResManager::update): runs the step until it stays
    void update() {
        if (m_func) {
            void (ResPack::*func)();
            do {
                func = m_func;
                if (!func) {
                    break;
                }
                (this->*func)();
            } while (func != m_func);
        }
    }
    void load(mtl::ALLOC_HANDLE handle, const char* name, IResPackEvent* event);
    void func_loading();

    mtl::ALLOC_HANDLE m_handle;  // @0x8: load's; the name is not the original's
    mm::mtl::FixStr<128> m_name;  // @0xc, length @0x8c: load's name; the name is not the original's
    IResPackEvent* m_event;  // @0x90: load's listener; the name is not the original's
    void (ResPack::*m_func)();  // @0x98: load sets func_loading; the name is not the original's
    fw::RenderResource* m_res;  // @0xa8: fw::RenderResource::request's; the name is not the original's
};
}  // namespace event

#endif
