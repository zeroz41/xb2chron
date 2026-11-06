#ifndef CLASSES_EVENT_MDLSTMDATA_H
#define CLASSES_EVENT_MDLSTMDATA_H

#include "classes/event/ModelObj.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3FC88
// Kept as Singleton<MdlstmData>::getPtr's instance: its guard constructs the count, then the table, and registers
// the destructor (MdlstmManager::clear/addReplaceInfo, MdlstmObj::init). The table is weak: D2/D0 sit in CharaObj's
// tail, so the destructor is inline.
class MdlstmData {
public:
    // a model a scene replaces (1.0.0's addReplaceInfo/getReplaceInfo take it); MdlstmObj::init copies the fields
    // after the name into its own type/id fields; the field names are not the original's
    struct Info {
        Info() : m_type(), m_id(0), m_bladeId(0), m_left(false) {}
        mm::mtl::FixStr<128> m_name;  // 0x0: getReplaceInfo looks for it inside the model name (1.0.0's strstr)
        MODEL_TYPE m_type;  // 0x84
        unsigned int m_id;  // 0x88
        unsigned int m_bladeId;  // 0x8c: MdlstmObj::init copies it to m_option.bladeId
        bool m_left;  // 0x90: to m_option.left
    };

    MdlstmData() {}
    virtual ~MdlstmData() {}  // slot 0

    // 1.0.0's MdlstmData::clear (inlined in 3.0.1)
    void clear() { m_infos.clear(); }
    // 1.0.0's MdlstmData::addReplaceInfo (inlined in 3.0.1)
    void addReplaceInfo(const Info& info) { m_infos.push_back(info); }
    // out of line (0x71000C2D54, not written yet)
    bool getReplaceInfo(Info& info, const char* name);

    mm::mtl::FixedVector<Info, 1> m_infos;  // @0x8, count @0xA0
};
}  // namespace event

#endif
