#ifndef ML_DRRESMDOVTXMESHOBJ_H
#define ML_DRRESMDOVTXMESHOBJ_H

namespace ml {
class DrResMdoVtxMeshObj {
public:
    // DrMdoCtlNom::callZSortNomAlphaRender
    void alpRender();
    void setActive(bool active, unsigned int index);
    // the work bytes one object takes (a constant 0x140)
    static unsigned int calcWorkSize(const unsigned char* data);
};
}  // namespace ml

#endif
