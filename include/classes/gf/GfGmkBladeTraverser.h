#ifndef CLASSES_GF_GFGMKBLADETRAVERSER_H
#define CLASSES_GF_GFGMKBLADETRAVERSER_H

namespace gmk { class AGmkBase; }

namespace gf {
// table 0x7100B51A70
class GfGmkBladeTraverser {
public:
    virtual void onTraverse(gmk::AGmkBase const&);  // slot 0

    // what onTraverse looks for (gf_field_gimmick's gevBladeActivate fills one; the names are not the original's):
    // with no blade id, a blade of that kind with none; with m_rareOnly, a blade of id 1001 or 1002; else that id
    unsigned char m_kind;  // 0x8
    int m_bladeId;  // 0xC
    const gmk::AGmkBase* m_result;  // 0x10: the last gimmick that matched
    bool m_rareOnly;  // 0x18
};
}  // namespace gf

#endif
