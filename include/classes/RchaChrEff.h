#ifndef CLASSES_RCHACHREFF_H
#define CLASSES_RCHACHREFF_H

#include "classes/RchaNode.h"
#include "mm/Vec3.h"

// table 0x7100B71CC8
// An Rcha node whose setup looks for the anms its getters read by name (the names in the table setup reads); each getter
// returns its anm's value at a frame, or a default when the data has none. The enum and field names are not the
// original's: the enum follows those anm names.
class RchaChrEff : public ::RchaNode {
public:
    enum {
        ANM_VOLUME_FADE,  // "chrEff/VolumeFade"
        ANM_VOLUME_FADE_ID,  // "chrEff/VolumeFadeId"
        ANM_VOLUME_FADE_UVW_SCALE_X,  // "chrEff/VolumeFadeUVWScaleX"
        ANM_VOLUME_FADE_UVW_SCALE_Y,  // "chrEff/VolumeFadeUVWScaleY"
        ANM_VOLUME_FADE_UVW_SCALE_Z,  // "chrEff/VolumeFadeUVWScaleZ"
        ANM_VOLUME_FADE_CENTER_POS_X,  // "chrEff/VolumeFadeCenterPosX"
        ANM_VOLUME_FADE_CENTER_POS_Y,  // "chrEff/VolumeFadeCenterPosY"
        ANM_VOLUME_FADE_CENTER_POS_Z,  // "chrEff/VolumeFadeCenterPosZ"
        ANM_VOLUME_FADE_DISTANCE,  // "chrEff/VolumeFadeDistance"
        ANM_VOLUME_FADE_DIRECTIVITY,  // "chrEff/VolumeFadeDirectivity"
        ANM_VOLUME_FADE_MESH_NO,  // "chrEff/VolumeFadeMeshNo"
        ANM_VOLUME_FADE_RATIO,  // "chrEff/VolumeFadeRatio"
        ANM_RIM_BLOOM,  // "chrEff/RimBloom"
        ANM_RIM_BLOOM_ID,  // "chrEff/RimBloomId"
        ANM_AFTER_IMAGE,  // "chrEff/AfterImage"
        ANM_AFTER_IMAGE_ID1,  // "chrEff/AfterImageId1"
        ANM_AFTER_IMAGE_ID2,  // "chrEff/AfterImageId2"
        ANM_AFTER_IMAGE_CAPTURE_FRAME,  // "chrEff/AfterImageCaptureFrame"
        ANM_AFTER_IMAGE_EXIST_FRAME,  // "chrEff/AfterImageExistFrame"
        ANM_AFTER_IMAGE_FADE_OUT_FRAME,  // "chrEff/AfterImageFadeOutFrame"
        ANM_NUM
    };

    RchaChrEff();
    // inline: the table's slot 0 holds RchaNode's complete destructor, which this one became
    virtual ~RchaChrEff() {}  // slot 0
    virtual bool setup(mtl::ALLOC_HANDLE handle, void const* data);  // slot 2
    virtual void clear();  // slot 3
    bool getVolumeFade(int& value, float frame) const;
    bool getVolumeFadeId(int& value, float frame) const;
    void getVolumeFadeUVWScale(mm::Vec3& vec, float frame) const;
    void getVolumeFadeCenterPos(mm::Vec3& vec, float frame) const;
    bool getVolumeFadeDistance(float& value, float frame) const;
    bool getVolumeFadeDirectivity(float& value, float frame) const;
    bool getVolumeFadeMesh(int& value, float frame) const;
    bool getVolumeFadeRatio(float& value, float frame) const;
    bool getRimBloom(int& value, float frame) const;
    bool getRimBloomId(int& value, float frame) const;
    bool getAfterImage(int& value, float frame) const;
    bool getAfterImageId1(int& value, float frame) const;
    bool getAfterImageId2(int& value, float frame) const;
    bool getAfterImageCaptureFrame(float& value, float frame) const;
    bool getAfterImageExistFrame(float& value, float frame) const;
    bool getAfterImageFadeOutFrame(float& value, float frame) const;

    bool m_hasAnm;  // 0x19A0 set by setup whatever it finds (1.0.0's hasAnm returns it)
    int m_anmIndex[ANM_NUM];  // 0x19A4 per name, the index in m_anm of the anm setup found for it, -1 for none
};

#endif
