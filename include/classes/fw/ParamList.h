#ifndef CLASSES_FW_PARAMLIST_H
#define CLASSES_FW_PARAMLIST_H

#include "fw/ParamAdapter.h"

namespace fw {
// table 0x7100B42940
class ParamList {
public:
    virtual ~ParamList();  // slot 0

    // the entry at index, none past the end (inline: the name is not the original's)
    ParamAdapter getAdapter(unsigned int index) const {
        return ParamAdapter(index < m_count ? &m_entries[index] : nullptr);
    }

    unsigned char pad_8[4];
    unsigned int m_count;                   // ParamBuilder sets both from the list's binary
    const ParamAdapter::Entry* m_entries;
};
}  // namespace fw

#endif
