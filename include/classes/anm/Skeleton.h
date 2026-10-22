#ifndef CLASSES_ANM_SKELETON_H
#define CLASSES_ANM_SKELETON_H

#include <string.h>
#include "anm/Array.h"

namespace anm {
// one of a skeleton's bones (getBoneFromLabel returns one): 16 bytes, its name first
struct Bone {
    const char* m_name;  // the IK solvers' setup finds a bone by it
    unsigned char pad_8[0x8];
};

// table 0x7100B810B8
class Skeleton {
public:
    virtual ~Skeleton();  // slot 0

    // the index of the bone named `name`, 0xFFFF when none is (inline: the IK solvers' setup each inline it;
    // the name is not the original's)
    unsigned short getBoneIndex(const char* name) const {
        for (unsigned int i = 0; i < m_bones.size(); i++) {
            if (strcmp(name, m_bones[i].m_name) == 0) {
                return i;
            }
        }
        return 0xFFFF;
    }

    unsigned char pad_8[0x28];
    Array<Bone> m_bones;  // getBoneFromLabel indexes it; its size is the pose's transform count
};
}  // namespace anm

#endif
