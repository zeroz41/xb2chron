// not proven yet: its table differs from the original's (word 4: _ZN2ml23DrResMdoSortNomFastApha11SetupRenderEv where the original has _ZN2ml13DrMdoZSortObj11SetupRenderEv)
#ifndef CLASSES_ML_DRRESMDOSORTNOMFASTAPHA_H
#define CLASSES_ML_DRRESMDOSORTNOMFASTAPHA_H

namespace ml {
// table 0x7100B7E0B0
class DrResMdoSortNomFastApha {
public:
    virtual ~DrResMdoSortNomFastApha();  // slot 0
    virtual void SetupRender();  // slot 2
    virtual void ZPrepassRender();  // slot 3
    virtual void ThicknessRenderFirst();  // slot 4
    virtual void ThicknessRenderSecond();  // slot 5
    virtual void render();  // slot 6
    virtual void GBuffRender();  // slot 7
    virtual void lightPrePassRender();  // slot 8
    virtual void alphaRender();  // slot 9
    virtual void spAlphaRender();  // slot 10
    virtual void refractionRender();  // slot 11
};
}  // namespace ml

#endif
