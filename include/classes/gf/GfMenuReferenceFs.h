#ifndef CLASSES_GF_GFMENUREFERENCEFS_H
#define CLASSES_GF_GFMENUREFERENCEFS_H

namespace gf { class MenuFieldSkill; }

namespace gf {
// table 0x7100B62578
class GfMenuReferenceFs {
public:
    virtual ~GfMenuReferenceFs();  // slot 0
    virtual void getFs(gf::MenuFieldSkill&) const;  // slot 2
};
}  // namespace gf

#endif
