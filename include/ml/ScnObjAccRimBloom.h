#ifndef ML_SCNOBJACCRIMBLOOM_H
#define ML_SCNOBJACCRIMBLOOM_H

namespace mm { class Col3; }
namespace ml { class DrMdlObj; }
namespace ml { class ScnObjModel; }

namespace ml {
// access to a model's rim bloom: the setters write the draw object's current rim bloom work entry
class ScnObjAccRimBloom {
public:
    explicit ScnObjAccRimBloom(ScnObjModel* model);
    ~ScnObjAccRimBloom();
    void setRimColor(const mm::Col3& color);
    void setRimEmissive(float emissive);
    void setRimPower(float power);
    void setBlackRatio(float ratio);

    DrMdlObj* m_drMdl;  // the constructor's model's draw object (the name is not the original's)
};
}  // namespace ml

#endif
