#ifndef ML_DRMDOCTLMPFINST_H
#define ML_DRMDOCTLMPFINST_H

namespace grlib { class CGLibVtxInstans; }
namespace ml { class DrCalcViewWork; class DrMdoCtlMpfWork; class DrResMdoSeamWrkPosMpf; struct MdsMpfObjData; }

namespace ml {
// One 0x20-byte entry of DrResMdoSeamWrkPosMpf::m_info (the type name is the symbols': calcMpfObjTree takes it).
// The field names are not the original's.
struct MdsMpfObjTreeData {
    unsigned char pad_0[0x1C];
    unsigned short m_objIdx;  // 0x1C: its MdsMpfObjData (DrMdoCtlMpf::calcMpfRenderList)
    unsigned char pad_1E[0x2];
};

// The instanced mpf part of a model control (its constructor is empty: no table). Field and type names are not
// the original's.
class DrMdoCtlMpfInst {
public:
    // the head of the instanced mpf resource setupInstMpf takes: its instance data sits m_instOfs bytes from it
    struct ResHeader {
        unsigned char pad_0[0x4];
        unsigned int m_instOfs;  // 0x4
    };

    DrMdoCtlMpfInst();
    void setupInstMpf(const unsigned char* data);
    void calcMpfObjTree(const MdsMpfObjTreeData* tree, DrCalcViewWork* view, float param);
    void calcSeamInstMpf(DrCalcViewWork* view, DrMdoCtlMpfWork* work, DrResMdoSeamWrkPosMpf* pos);
    void calcSeamMpfObjTree(const MdsMpfObjTreeData* tree, DrCalcViewWork* view, float param);

    const MdsMpfObjData* m_pInstData;  // 0x0
    DrMdoCtlMpfWork* m_pWork;  // 0x8: DrMdoCtlMpf::calcMpfRenderList sets it before the tree walk
    DrResMdoSeamWrkPosMpf* m_pPosMpf;  // 0x10: likewise
};
}  // namespace ml

#endif
