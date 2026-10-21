#ifndef FW_PARAMADAPTER_H
#define FW_PARAMADAPTER_H

namespace fw {

// a handle on one entry of a ParamList (16-byte entries from the list's binary): 8 bytes, passed
// by value in one register (TwoCharaGroundSolver::createFootPlacementIKMain); its users read the
// entry's parameter block through it, nothing when it holds no entry. Its holders start it empty
// (MoveUtilField zeroes a packet's before filling it).
class ParamAdapter {
public:
    struct Entry {
        unsigned char pad_0[8];
        const void* m_data;  // the parameter block the adapter's users read
    };

    ParamAdapter() : m_entry(nullptr) {}
    ParamAdapter(const Entry* entry) : m_entry(entry) {}

    template <typename T>
    const T* get() const {
        return m_entry != nullptr ? static_cast<const T*>(m_entry->m_data) : nullptr;
    }

    const Entry* m_entry;
};

}  // namespace fw

#endif
