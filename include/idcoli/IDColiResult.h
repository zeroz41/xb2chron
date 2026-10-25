#ifndef IDCOLI_IDCOLIRESULT_H
#define IDCOLI_IDCOLIRESULT_H

namespace idcoli {
// a collision query's result, filled by the IDColiUtilColiResult tests. Only the field the test functions of
// IDColiObjCharCheck/IDColiObjPhantomCheck read is declared; the name is not the original's.
class IDColiResult {
public:
    unsigned char pad_0[0xE8];
    // 0xE8, the materials the query skips: an object whose m_materialBit shares a bit is not tested
    unsigned int m_ignoreMaterial;
};
}  // namespace idcoli

#endif
