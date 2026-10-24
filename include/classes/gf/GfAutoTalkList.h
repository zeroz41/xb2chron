#ifndef CLASSES_GF_GFAUTOTALKLIST_H
#define CLASSES_GF_GFAUTOTALKLIST_H

#include "classes/gf/GfAutoTalk.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/Vector.h"

namespace gf {
// table 0x7100B53818: one gimmick set's auto talks (GfAutoTalkManager keeps them in an intrusive list through the
// node at 0x8). The members are 1.0.0's.
class GfAutoTalkList : public ::mm::mtl::IntrusiveListNodeBase {
public:
    // the gimmick set's row and its autoTalk tables (the names are not the original's)
    struct CreateInfo {
        CreateInfo() : m_id(0), m_fp(nullptr), m_fpMs(nullptr) {}
        int m_id;
        unsigned char* m_fp;
        unsigned char* m_fpMs;
    };

    GfAutoTalkList(const CreateInfo* info = nullptr) : m_info(), m_talks() {
        if (info != nullptr) {
            create(*info);
        }
    }
    virtual ~GfAutoTalkList();  // slot 0
    void create(const CreateInfo& info);
    void dispose();
    void update(float dt) {
        if (m_info.m_id > 0 && m_info.m_fp != nullptr && m_info.m_fpMs != nullptr) {
            unsigned long count = m_talks.size();
            for (unsigned long i = 0; i < count; ++i) {
                m_talks[i].update(dt);
            }
        }
    }

    CreateInfo m_info;                         // 0x18
    mm::mtl::Vector<GfAutoTalk> m_talks;       // 0x30: a row each (the name is not the original's)
};
}  // namespace gf

#endif
