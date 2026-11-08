#ifndef CLASSES_EVENT_SHAKERRES_H
#define CLASSES_EVENT_SHAKERRES_H

#include "classes/RchaCam.h"
#include "classes/fw/CommonResource.h"
#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3D4B8
class ShakerRes {
public:
    // out of line, the key function: D2/D0 sit before create (0x71001000D8)
    virtual ~ShakerRes();  // slot 0
    // inline: ShakeManager's constructor builds the eight in place
    ShakerRes() : m_res(nullptr), m_rcha(nullptr) {}
    void create(const char* name);
    void update();
    // inline: the destructor's body and create's first part (1.0.0 has it out of line as destroy, 0x71000ED00C)
    void destroy() {
        if (m_rcha != nullptr) {
            delete m_rcha;
            m_rcha = nullptr;
        }
        if (m_res != nullptr) {
            m_res->release();
            m_res = nullptr;
        }
        m_name = "";
    }

    mm::mtl::FixStr<64> m_name;  // @0x8, length @0x48: create's name; the name is not the original's
    fw::CommonResource* m_res;  // @0x50: fw::CommonResource::request's; the name is not the original's
    RchaCam* m_rcha;  // @0x58: update news it once the resource is loaded; the name is not the original's
};
}  // namespace event

#endif
