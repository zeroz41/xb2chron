#ifndef CLASSES_GF_GFGMKBLADETRAVERSER_H
#define CLASSES_GF_GFGMKBLADETRAVERSER_H

namespace gmk { class AGmkBase; }

namespace gf {
// table 0x7100B51A70
class GfGmkBladeTraverser {
public:
    // gevBladeActivate builds them on the stack: the ids 1001 and 1002 look for either
    GfGmkBladeTraverser(unsigned char kind, int bladeId)
        : m_kind(kind), m_bladeId(bladeId), m_result(nullptr), m_rareOnly(bladeId == 1001 || bladeId == 1002) {}
    virtual void onTraverse(gmk::AGmkBase const&);  // slot 0
    // GmkManager::traverseGmkInst calls its F with each gimmick (inline; the name is not the original's)
    void operator()(gmk::AGmkBase const& gmk) { onTraverse(gmk); }

    // what onTraverse looks for (gf_field_gimmick's gevBladeActivate fills one; the names are not the original's):
    // with no blade id, a blade of that kind with none; with m_rareOnly, a blade of id 1001 or 1002; else that id
    unsigned char m_kind;  // 0x8
    int m_bladeId;  // 0xC
    const gmk::AGmkBase* m_result;  // 0x10: the last gimmick that matched
    bool m_rareOnly;  // 0x18
};
}  // namespace gf

#endif
