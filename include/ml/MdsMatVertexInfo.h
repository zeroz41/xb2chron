#ifndef ML_MDSMATVERTEXINFO_H
#define ML_MDSMATVERTEXINFO_H

namespace ml {
// One vertex attribute of a material technique (8 bytes: DrShdFetchMan::createFetchObj steps through an array of
// them). The field names are not the original's.
struct MdsMatVertexInfo {
    unsigned short m_attr;  // 0x0: the attribute slot (createFetchObj sets bit m_attr of its attribute bits)
    unsigned short m_size;  // 0x2: createFetchObj sums them
    unsigned char pad_4[0x4];
};
}  // namespace ml

#endif
