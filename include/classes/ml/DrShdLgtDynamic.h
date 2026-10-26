#ifndef CLASSES_ML_DRSHDLGTDYNAMIC_H
#define CLASSES_ML_DRSHDLGTDYNAMIC_H

namespace ml { class DrMan; }

namespace ml {
// table none (its derived classes')
// The constructor and destructor are inline: DrShdLgtHybrid's, DrShdLgtClustered's constructors store m_cateIdx = 0
// first, then their own m_pDrMan, and no base destructor is called (the field names are not the original's).
class DrShdLgtDynamic {
public:
    DrShdLgtDynamic() : m_cateIdx(0) {}
    virtual ~DrShdLgtDynamic() {}  // slot 0
    virtual void stockBegin() = 0;  // slot 2
    virtual void stockEnd() = 0;  // slot 3
    virtual void update() = 0;  // slot 4
    virtual void setupCate(int);  // slot 5

    int m_cateIdx;  // 0x8, setupCate stores it
    unsigned char pad_c[0x4];
    DrMan* m_pDrMan;  // 0x10, the constructor's renderer
};
}  // namespace ml

#endif
