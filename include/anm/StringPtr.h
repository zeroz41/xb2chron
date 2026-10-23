#ifndef ANM_STRINGPTR_H
#define ANM_STRINGPTR_H

#include <string.h>

namespace anm {
// a name as a map key, ordered by strcmp: a state's (anm::StateMachine) or a sound source's
// (fw::SoundResSourceManager) (the RedBlackTreeBase<Map<StringPtr, ...>> instances are 1.0.0's
// names; the field's name is not the original's)
class StringPtr {
public:
    StringPtr() : m_str(nullptr) {}
    StringPtr(const char* str) : m_str(str) {}
    bool operator<(const StringPtr& other) const { return strcmp(m_str, other.m_str) < 0; }

    const char* m_str;
};
}  // namespace anm

#endif
