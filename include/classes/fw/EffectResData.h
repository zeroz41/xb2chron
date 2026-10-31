#ifndef CLASSES_FW_EFFECTRESDATA_H
#define CLASSES_FW_EFFECTRESDATA_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"

namespace anm { class ResASM; }
namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// one effect annotation as the resource holds it: 0x118 bytes (EffectResData::initSub reads an array of them; the
// names of the fields are not the original's, pad_<offset> fields are copied without a known role)
struct EffectAnnotationTbl {
    char m_stateName[0x40];     // the state the annotation starts in (EffectAnnotationData::m_stateName)
    char m_endStateName[0x40];  // the state it ends in
    char pad_80[0x3d];
    unsigned char pad_bd;
    unsigned char pad_be;
    unsigned char pad_bf;
    char pad_c0[0x1c];
    float m_position[3];  // copied as it is
    float m_rotation[3];  // in degrees: initSub converts them to radians
    unsigned short pad_f4;
    unsigned char pad_f6;
    unsigned char pad_f7;
    unsigned int pad_f8;
    unsigned int pad_fc;
    float m_startFrame;
    float m_endFrame;
    unsigned int pad_108;
    unsigned int pad_10c;
    unsigned int pad_110;
    unsigned char pad_114;
    unsigned char pad_115;
    unsigned char pad_116;
    unsigned char pad_117;
};

// one effect annotation as EffectResData registers it with an animation state machine (the AsmAnnotetion's data):
// 0x120 bytes (the names of the fields are not the original's)
struct EffectAnnotationData {
    EffectAnnotationData() {
        m_type = 0;
        pad_f0 = 0;
        pad_f6 = 0;
        pad_f7 = 0;
        pad_fc = 0;
        pad_100 = 0;
        m_startFrame = 0.0f;
        m_endFrame = 0.0f;
        pad_c4 = 0;
        pad_c8 = 0;
        pad_c0 = 0;
        pad_f8 = 1;
        pad_114 = 0;
        pad_f4 = 0;
        pad_f5 = 0;
        m_atStart = false;
        m_atEnd = false;
        pad_108 = 0;
        pad_10a = 0;
        pad_10c = 0;
    }
    mm::mtl::FixStr<32> m_stateName;
    float m_startFrame;  // -1 (type 1): an enter annotation instead of a frame annotation
    mm::mtl::FixStr<32> m_endStateName;
    float m_endFrame;  // -1 with a state name: type 5 (enter and leave annotations)
    unsigned int pad_50;
    mm::mtl::FixStr<32> pad_54;
    mm::mtl::FixStr<32> pad_78;
    // the state name without its "_00", "_01" or "_02": type 5 registers leave annotations of "%s_%02d" 0 to 2
    mm::mtl::FixStr<32> m_baseName;
    unsigned int pad_c0;
    unsigned int pad_c4;
    unsigned int pad_c8;
    mm::Vec3 m_position;
    mm::Vec3 m_rotation;  // in radians
    unsigned int pad_f0;
    unsigned char pad_f4;
    unsigned char pad_f5;
    unsigned char pad_f6;
    unsigned char pad_f7;
    unsigned char pad_f8;
    unsigned char pad_f9;
    unsigned char pad_fa;
    unsigned char pad_fb;
    unsigned int pad_fc;
    unsigned int pad_100;
    // initSub's: 0 "<SETUP>", 2 "<COMBAT>", 3 "<WPN_CHANGE>", 4 "<FOOTSTEP>", 8 "<PROG_HIT>", 9 "<PROG_BUFF>", 5 an
    // end frame of -1, 7 an end state with "<END>", else 6; registerAsmAnnotation makes a 6 or 7 ending where it
    // starts at frame 0 a 1
    int m_type;
    unsigned short pad_108;
    unsigned short pad_10a;
    unsigned int pad_10c;
    bool m_atStart;  // registerAsmAnnotation sets it for the start frame's annotation
    bool m_atEnd;    // and this for the end frame's
    unsigned int pad_114;
};

// table 0x7100B41350; counted: createEffectResData zeroes the count at 0x8 as ReferenceObject's constructor does and
// takes the first reference, GfExtendPacking's destructor releases it (reference_object.h's `m_RefCount > 0`)
class EffectResData : public ::mm::mtl::ReferenceObject {
public:
    // what createEffectResData builds the data from (the names of the fields are not the original's)
    struct SetupInfo {
        // one resource's annotation table
        struct Table {
            EffectAnnotationTbl* m_data;
            unsigned int m_size;  // in bytes
        };
        mm::mtl::IAllocator* m_allocator;
        mm::mtl::FixedVector<Table, 101> m_tables;
    };

    explicit EffectResData(mm::mtl::IAllocator* allocator) : m_annotations(allocator) {}
    virtual ~EffectResData();  // slot 0
    // a new data holding the setup's annotations, with its first reference
    static EffectResData* createEffectResData(const SetupInfo& info);
    void init(const SetupInfo& info);
    // the count annotations of the table
    void initSub(unsigned int count, EffectAnnotationTbl* table);
    // GfComEffectCaster::registerAsmCallbackEffect passes its ASM resource, 3 and ASM_CB_NAME_EFFECT ("asm_effect")
    // (the names of the parameters are not the original's)
    void registerAsmAnnotation(anm::ResASM* asmRes, unsigned int type, const char* name);

    mm::mtl::Vector<EffectAnnotationData> m_annotations;
};
}  // namespace fw

#endif
