#ifndef ML_DRPIXLPOSTOBJEXPSTENCIL_H
#define ML_DRPIXLPOSTOBJEXPSTENCIL_H

namespace ml {
class DrMan;

// The constructor only stores the renderer; other fields and members are not declared yet.
class DrPixlPostObjExpStencil {
public:
    DrPixlPostObjExpStencil(DrMan* drMan);
    ~DrPixlPostObjExpStencil();  // empty; its owners' destructors call it

    DrMan* m_pDrMan;  // 0x0 (the name is not the original's)
};

}  // namespace ml

#endif
