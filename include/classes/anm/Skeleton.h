#ifndef CLASSES_ANM_SKELETON_H
#define CLASSES_ANM_SKELETON_H

#include <string.h>
#include "anm/Array.h"
#include "anm/QsTransform.h"

namespace anm {
// one of a skeleton's bones (getBoneFromLabel returns one): 16 bytes, its name first
struct Bone {
    const char* m_name;  // the IK solvers' setup finds a bone by it
    unsigned char pad_8[0x8];
};

// one of a skeleton's extra-track slots (Skeleton keeps them 0x38 apart; anm::ExtraTruckBuffer is made for one):
// the fields' names are not the original's
struct ExtraTruckSlot {
    const char* m_name;  // getExtraTruckSlotID finds a slot by it
    unsigned char pad_8[0x18];
    unsigned int m_count;  // its values: Factory::createExtraTruckBuffer makes no buffer for a slot without any
    unsigned char pad_24[0x14];
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

    // bone's parent's index, -1 for a root (inline: SpaceResolveUtil's loops and BlendUtil::normalizePoseMS pass
    // it a 16-bit bone index, which they widen to 64 bits apart from the assertion's; the name is not the original's)
    short getParentIndex(unsigned short bone) const { return m_parents[bone]; }

    // the index of the extra-track slot named `name`, -1 when none is
    short getExtraTruckSlotID(const char* name) const;
    // orders the extra-track slots by name (std::lower_bound's comparator in getExtraTruckSlotID)
    struct CompTruck {
        bool operator()(const ExtraTruckSlot& slot, const char* name) const { return strcmp(slot.m_name, name) < 0; }
    };

    unsigned char pad_8[0x10];
    const char* m_name;  // Factory::createASMResource prints it (the name is not the original's)
    // per bone, its parent's index, -1 for a root (BlendUtil::normalizePoseMS; the name is not the original's)
    Array<short> m_parents;
    Array<Bone> m_bones;  // getBoneFromLabel indexes it; its size is the pose's transform count
    // per bone, its transform in the reference pose (BlendUtil::normalizePoseMS; the name is not the original's)
    Array<QsTransform> m_referencePose;
    Array<ExtraTruckSlot> m_extraTruckSlots;  // getExtraTruckSlotID's (the name is not the original's)
    unsigned char pad_60[0x10];
    // names searched with strcmp for GfDataDriver::getBelongingMountBone ("MT_wire") by GfAppendWire's constructor,
    // which keeps the index (the name is not the original's)
    Array<const char*> m_mountNames;
};
}  // namespace anm

#endif
