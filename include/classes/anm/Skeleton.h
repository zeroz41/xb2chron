#ifndef CLASSES_ANM_SKELETON_H
#define CLASSES_ANM_SKELETON_H

#include <string.h>
#include <algorithm>
#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "anm/AnimationObject.h"
#include "classes/anm/ReferenceObject.h"

namespace anm {
// one of a skeleton's bones (getBoneFromLabel returns one): 16 bytes, its name first
struct Bone {
    const char* m_name;  // the IK solvers' setup finds a bone by it
    unsigned char pad_8[0x4];
    // Util::computeBonePairFromName pairs it with no bone (-1) while set (the name is not the original's)
    bool m_noPair;
    unsigned char pad_d[0x3];
};

// one of a skeleton's extra-track slots (Skeleton keeps them 0x38 apart; anm::ExtraTruckBuffer is made for one):
// the fields' names are not the original's
struct ExtraTruckSlot {
    const char* m_name;  // getExtraTruckSlotID finds a slot by it
    // the index of the truck named `name`, -1 when none is (AnimPoseModifier.cpp's unit; it lower_bounds m_truckNames)
    short getTruckID(const char* name) const;
    // the name of a value's truck (inline: SimpleMapper's constructor indexes the names with a 16-bit index; the name
    // is not the original's)
    const char* getTruckName(unsigned short truck) const { return m_truckNames[truck]; }

    // per value, its truck's name, sorted (getTruckID searches them; the name is not the original's)
    Array<const char*> m_truckNames;
    // its values' defaults: Blender::sampleExtraTrucks normalizes with them (NormalizeExtraTruckSrc::pDefaults), so its
    // size is the slot's value count (Factory::createExtraTruckBuffer makes no buffer for a slot without any). The
    // name is not the original's
    Array<float> m_defaults;
    // one value's limits (Util::clampLimitExtraTruck clamps the value into them; the names are not the original's)
    struct Limit {
        float m_min;
        float m_max;
    };

    Array<Limit> m_limits;  // one per value
};

// a label's kind (1.0.0's name; its values' names are not known: GfComEnvSensor::setup asks for kinds 0 and 1 for
// the feet, 15 for the root)
enum LabelType {};

// one of a skeleton's labels, kept sorted by kind then index (1.0.0's name; the field names are not the original's)
struct SkelLabel {
    LabelType m_type;
    unsigned short m_index;
    unsigned short m_bone;  // the bone it names
};

// table 0x7100B810B8 (weak: DynamicSkeleton.cpp's SkeletonImporter::import constructs it in place)
// counted: GfComModel::cleanup releases its skeleton as the pose and extra truck buffer
class Skeleton : public ::anm::AnimationObject {
public:
    // trivial and inline: the table's slot 0 holds AnimationObject's destructor (its base's)
    virtual ~Skeleton() {}  // slot 0

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
    // the bone of the index (Util::computeIgnoreMirrorFromName indexes the bones with a 16-bit index; the name is not
    // the original's)
    const Bone& getBone(unsigned short bone) const { return m_bones[bone]; }
    // the extra-track slot of the index (inline: Blender's constructor indexes the slots with a 16-bit index; the
    // name is not the original's)
    const ExtraTruckSlot& getExtraTruckSlot(unsigned short slot) const { return m_extraTruckSlots[slot]; }

    // the index of the extra-track slot named `name`, -1 when none is
    short getExtraTruckSlotID(const char* name) const;
    // what getBoneFromLabel searches m_labels for (1.0.0's names)
    struct LabelKey {
        LabelType m_type;
        unsigned short m_index;
    };
    struct CompLable {
        bool operator()(const SkelLabel& label, const LabelKey& key) const {
            if (label.m_type == key.m_type) {
                return label.m_index < key.m_index;
            }
            return label.m_type < key.m_type;
        }
    };
    // the bone a label names, 0xFFFF when none does (1.0.0's; inline: GfComEnvSensor::setup inlines it)
    unsigned short getBoneFromLabel(LabelType type, unsigned short index) const {
        if (m_labels.size() != 0) {
            LabelKey key = {type, index};
            ArrayIterartor<const SkelLabel> it = std::lower_bound(m_labels.begin(), m_labels.end(), key, CompLable());
            if (it != m_labels.end() && it.m_pData->m_type == type && it.m_pData->m_index == index) {
                return it.m_pData->m_bone;
            }
        }
        return 0xFFFF;
    }
    // orders the extra-track slots by name (std::lower_bound's comparator in getExtraTruckSlotID)
    struct CompTruck {
        bool operator()(const ExtraTruckSlot& slot, const char* name) const { return strcmp(slot.m_name, name) < 0; }
    };

    const char* m_name;  // Factory::createASMResource prints it (the name is not the original's)
    // per bone, its parent's index, -1 for a root (BlendUtil::normalizePoseMS; the name is not the original's)
    Array<short> m_parents;
    Array<Bone> m_bones;  // getBoneFromLabel indexes it; its size is the pose's transform count
    // per bone, its transform in the reference pose (BlendUtil::normalizePoseMS; the name is not the original's)
    Array<QsTransform> m_referencePose;
    Array<ExtraTruckSlot> m_extraTruckSlots;  // getExtraTruckSlotID's (the name is not the original's)
    // per mount, the index of the bone it hangs on, 0xFFFF for none (GfComModel::createBoneReferenceFrame makes the
    // bone's frame the mount frame's parent; the name is not the original's)
    Array<unsigned short> m_mountBones;
    // names searched with strcmp for GfDataDriver::getBelongingMountBone ("MT_wire") by GfAppendWire's constructor,
    // which keeps the index (the name is not the original's)
    Array<const char*> m_mountNames;
    // per mount, its transform against the bone it hangs on (GfComModel::createMountReferenceFrameImpl makes it the
    // mount frame's local transform; the name is not the original's)
    Array<QsTransform> m_mountTransforms;
    Array<SkelLabel> m_labels;  // getBoneFromLabel searches them (the name is not the original's)
};
}  // namespace anm

#endif
