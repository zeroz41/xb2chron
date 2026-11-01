#ifndef ML_DRMDONOMCLONE_H
#define ML_DRMDONOMCLONE_H

namespace ml { class DrMdoCtlNom; }

namespace ml {
// Copies one normal model's work into another (DrResMdoMat/DrResMdoMeshObj assignments, the etc params). Empty
// (no fields, no table): DrMdoCtlNom::cloneMdlObj and DrMdoNomAfterImage::captureObj both call cloneMdlObj with
// their own `this` unchanged, so both derive from it and it sits at offset 0.
class DrMdoNomClone {
public:
    bool cloneMdlObj(DrMdoCtlNom* dst, const DrMdoCtlNom* src);
};
}  // namespace ml

#endif
