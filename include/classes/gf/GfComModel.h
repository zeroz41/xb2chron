#ifndef CLASSES_GF_GFCOMMODEL_H
#define CLASSES_GF_GFCOMMODEL_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
#include "classes/fw/ReferenceFrame.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/AnimPoseModifier.h"
#include "classes/fw/AnimVolumeFadeModifier.h"
namespace anm { class ExtraTruckBuffer; }
namespace anm { class Pose; }
namespace fw { class Message; }
namespace fw { class ModelObject; }
namespace fw { class MessageObject; }

namespace anm { class Skeleton; }

namespace gf {
// table 0x7100B667B8
class GfComModel : public ::gf::GfComponent {
public:
    // table 0x7100B667F0: the viewer's standby-logout listener (GfComModel holds one at 0x1198)
    class ViewerListener {
    public:
        ViewerListener() : m_pOwner(nullptr) {}
        virtual void onWkStandbyLogout();  // slot 0
        GfComModel* m_pOwner;  // (the name is not the original's)
    };
    // a reference frame made on a bone (the field names are not the original's)
    struct BoneFrameInfo {
        BoneFrameInfo() : count(0) {}
        mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame;
        // the bone's index (the skeleton's bone, or its mount for pad_1168's; getBoneReferenceFrame searches by it)
        short bone;
        // how many createBoneReferenceFrame calls share the frame (the name is not the original's)
        int count;
    };
    GfComModel();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComModel();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> createBoneReferenceFrame(const char* bone);
    void destroyBoneReferenceFrame(const char* bone);
    // a new frame on the skeleton's bone index, bound to the pose and hung under the transform's frame
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> createBoneReferenceFrameImpl(unsigned short index);
    // a new frame on the skeleton's mount index
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> createMountReferenceFrameImpl(unsigned short index);
    void destroyBoneReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
    // hangs frame on the model's bone (GfMenuModelView::attachObject passes another object's transform frame)
    // false when no frame could be made on the bone
    bool addBoneReferenceFrame(const char* bone, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame);
    // the frame made on the bone, none when there is none
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> getBoneReferenceFrame(const char* bone);
    // takes frame out from under the bone's frame and destroys the bone's frame
    void removeBoneReferenceFrame(const char* bone, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame);
    // whether its object's info asks for the volume fade
    bool isVolumeFadeForUser() const;
    bool isRender() const;
    // the model's scale, every axis the same (GfObjAcc::setModelScale forwards to it)
    void setModelScale(float scale);
    static mm::mtl::RTTI m_rtti;

    // setup copies its setup info's value at 0x18 here, cleanup sets it back to -1
    long pad_10;
    // the model's object: GFOBJ_INFO::createVolumeFade fades its interface (the name is not the original's)
    fw::ModelObject* m_model;
    // the model's frame (GfComDynamics binds its dynamics to it) (the name is not the original's)
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;
    // the model's skeleton: GfComEvtAnim::updateSetup builds its blender on it (anm::Factory::createBlender's
    // argument; the name is not the original's)
    const anm::Skeleton* m_skeleton;
    // the model's pose and extra truck buffer: GfComDynamics binds its dynamics to the pose, GfComPackAnim::Mot::play
    // its sampler to both (the names are not the original's)
    anm::Pose* m_pose;
    anm::ExtraTruckBuffer* m_extraTruckBuffer;
    fw::AnimPoseModifier m_poseModifier;  // (the name is not the original's)
    // its volume fade: GfVolumeFade::applyFadeRatio writes its parts' opacity (the name is not the original's)
    fw::AnimVolumeFadeModifier m_volumeFade;
    // the frames createBoneReferenceFrame made, searched by name (the name is not the original's)
    mm::mtl::Vector<BoneFrameInfo> m_boneFrames;
    mm::mtl::Vector<BoneFrameInfo> pad_1168;
    float m_scale;  // setModelScale stores it (the name is not the original's)
    ViewerListener m_viewerListener;
    void* m_pViewer;  // the viewer listener's onWkStandbyLogout clears it
};
}  // namespace gf

#endif
