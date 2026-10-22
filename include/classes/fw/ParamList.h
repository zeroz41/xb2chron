#ifndef CLASSES_FW_PARAMLIST_H
#define CLASSES_FW_PARAMLIST_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "fw/ParamAdapter.h"
#include "fw/Reflection.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw {
// table 0x7100B42940; counted (LookAxisPlugin::setup holds one through an IntrusivePtr, releasing it with
// reference_object.h's assertion on the count at 0x8)
class ParamList : public mm::mtl::ReferenceObject {
public:
    // a list's binary as bin::BinaryResolver resolves it: its entries and their count (ParamBuilder::importBinary
    // copies both; the names are not the original's)
    struct Binary {
        unsigned int m_count;
        const ParamAdapter::Entry* m_entries;
    };

    ParamList() : m_count(0), m_entries(nullptr) {}  // inline: ParamBuilder::importBinary's code has it
    virtual ~ParamList();  // slot 0

    // the entry at index, none past the end (inline: the name is not the original's)
    ParamAdapter getAdapter(unsigned int index) const {
        return ParamAdapter(index < m_count ? &m_entries[index] : nullptr);
    }

    unsigned int m_count;                   // ParamBuilder sets both from the list's binary
    const ParamAdapter::Entry* m_entries;
    // the reflection ParamBuilder::importBinary was given, referenced (the name is not the original's)
    mm::mtl::IntrusivePtr<Reflection> m_reflection;
};
}  // namespace fw

#endif
