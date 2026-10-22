#ifndef GF_GFPARAMPCCOLI_H
#define GF_GFPARAMPCCOLI_H

namespace fw { class Reflection; }

namespace gf {

// the PC collision's parameter block (1.0.0's PcColiParam::createReflection names its values; the members take
// those names)
struct PcColiParam {
    // its values as a struct of the reflection at index (1.0.0's; 3.0.1's linker dropped it)
    static void createReflection(fw::Reflection* reflection, const char* name, unsigned int index);

    float radiusCapsule;
    float heightCapsule;
    float radiusShpere;  // sic
    int type;  // 0 capsule, 1 sphere
    float bakkyoHeadDist;
};

// the PC collision's parameter block: the first entry of the eighteenth param list
const PcColiParam* getPcColiParameter();

}  // namespace gf

#endif
