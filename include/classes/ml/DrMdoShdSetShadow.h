#ifndef CLASSES_ML_DRMDOSHDSETSHADOW_H
#define CLASSES_ML_DRMDOSHDSETSHADOW_H

namespace ml { class DrShdDataList; }
namespace ml { class MdsMatInfoHeader; }

namespace ml {
// table none (its derived classes')
class DrMdoShdSetShadow {
public:
    virtual ~DrMdoShdSetShadow();  // slot 0
    virtual void SetupRender() = 0;  // slot 2
    virtual void ZPrepassRender() = 0;  // slot 3
    virtual void ThicknessRenderFirst() = 0;  // slot 4
    virtual void ThicknessRenderSecond() = 0;  // slot 5
    virtual void render() = 0;  // slot 6
    virtual void GBuffRender() = 0;  // slot 7
    virtual void lightPrePassRender() = 0;  // slot 8
    virtual void alphaRender() = 0;  // slot 9
    virtual void spAlphaRender() = 0;  // slot 10
    virtual void refractionRender() = 0;  // slot 11
    virtual void shwShd_Obj(int, ml::MdsMatInfoHeader const*, int, int, ml::DrShdDataList*);  // slot 12
};
}  // namespace ml

#endif
