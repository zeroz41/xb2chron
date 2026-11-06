#ifndef CLASSES_ML_DRMDOCTL_H
#define CLASSES_ML_DRMDOCTL_H

#include "classes/ml/DrMdoNode.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibVtxInstans; }

namespace ml {
struct MdsMdlInfoHeader;
struct MdsMdlTopHeader;
class DrMdoCtlMpfWork;
class DrResMdoAlpTbl;

// What DrMdoCtl::partsInstance*Render draw one top header's parts with (the type name is the symbols'; 0x28 bytes,
// DrMdoCtlSeamInstMap's passes fill it on the stack). The field names are not the original's: m_count, m_first and
// m_instances are what DrMdoCtlSeamInstMap::callInstShadowCacheAddRender passes partsPosNoamShadowRender from the
// same model info.
struct MdoInstancePrePassArg {
    const MdsMdlInfoHeader* m_info;  // 0x0: the part, stepped through the top header's parts
    unsigned int m_count;            // 0x8
    unsigned int m_first;            // 0xC
    unsigned int m_instances;        // 0x10
    unsigned int m_billNum;          // 0x14: the billboard instances (partsInstanceZPrepassBillRender)
    unsigned int m_billArg;          // 0x18
    unsigned char pad_1C[0x4];
    bool m_bill;                     // 0x20
    bool m_first2;                   // 0x21: createInstThicknessPassDisplayList's argument
    unsigned char pad_22[0x6];
};

// table 0x7100B7B680
class DrMdoCtl : public ::ml::DrMdoNode {
public:
    // 1.0.0 has DrMdoCtl(int) and DrMdoNode(int) (both 0x104 bytes); 3.0.1's inlines DrMdoNode's
    explicit DrMdoCtl(int viewNum);
    virtual ~DrMdoCtl() {}  // slot 0
    void setMatrix(const mm::Mat44& matrix);
    void setOffsetPos(const mm::Vec3& pos);
    void createWeightVtx(int, unsigned int, unsigned int, bool);
    void partsDefRender(const MdsMdlInfoHeader*, int, int, bool);
    // mot != 0: the node (motion) shader variants, drawn without the triangle block
    void partsShadowRender(const MdsMdlInfoHeader* info, int triIdx, int mot, int shdOfs);
    void partsShadowDirRender(const MdsMdlInfoHeader* info, int triIdx, int mot);
    void partsShadowBaseRender(const MdsMdlTopHeader* top);
    void partsShadowNukiBaseRender(const MdsMdlTopHeader* top);
    void partsPosShadowRender(const MdsMdlTopHeader* top);
    void partsPosNukiShadowRender(const MdsMdlTopHeader* top);
    void partsZPrePassRender(const MdsMdlInfoHeader* info, int, int, DrResMdoAlpTbl* alpTbl, unsigned int alpIdx);
    void partsThicknessRender(const MdsMdlInfoHeader* info, int, int, DrResMdoAlpTbl* alpTbl, unsigned int alpIdx,
                              bool first);
    void partsInstanceZPrepassRender(const MdoInstancePrePassArg& arg);
    void partsInstanceZPrepassBillRender(const MdoInstancePrePassArg& arg);
    void partsInstanceThicknessRender(const MdoInstancePrePassArg& arg);
    // count/first go to grlib::CGLibCtlVertex::setInstanceVertex, instances to DrResMdoVertex::renderIns (the
    // parameter names are not the original's)
    void partsPosNoamShadowRender(const MdsMdlTopHeader* top, grlib::CGLibVtxInstans* inst, unsigned int count,
                                  unsigned int first, unsigned int instances);
    // DrMdoCtlMpf::defMpfZPreRender/defMpfrender call them for each part of an object's render list
    void mpfZPrePassRender(int idx, const MdsMdlInfoHeader* info, DrMdoCtlMpfWork* work, grlib::CGLibVtxInstans* inst);
    void mpfDrawRender(int idx, const MdsMdlInfoHeader* info, DrMdoCtlMpfWork* work, grlib::CGLibVtxInstans* inst);
};
}  // namespace ml

#endif
