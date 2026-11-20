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
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfFileIdx : int; }

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
    // what setup takes (the field names are not the original's)
    struct SetupInfo {
        // the defaults fn_71005418C4 (gf_obj_factory) stores before it fills the info
        SetupInfo()
            : m_skeleton(nullptr), m_boneFrameCount(1), m_arg(0), m_handle(reinterpret_cast<GF_ASSET_HANDLE*>(-1)),
              pad_20(false), m_keepScale(false), m_scale(1.0f) {}
        GfFileIdx m_file;  // the model's file in the asset (GfAssetManager::getResource's)
        const anm::Skeleton* m_skeleton;  // no pose, extra truck buffer or modifiers without one
        unsigned int m_boneFrameCount;  // the room both bone frame vectors get
        int m_arg;  // ModelSetup::arg
        GF_ASSET_HANDLE* m_handle;  // the asset the model is in: setup does nothing for -1
        // no rim bloom on the model and no volume fade
        bool pad_20;
        bool m_keepScale;  // ModelSetup::keepScale
        float m_scale;  // ModelSetup::scale, kept in m_scale
    };
    GfComModel();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComModel();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    // undoes setup (GfObjFactory::destroyComponent): frees the bone frames, unbinds the modifiers, releases the
    // model, frame, skeleton, pose and extra truck buffer
    void setup(const SetupInfo& info);
    void cleanup();
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> createBoneReferenceFrame(const char* bone);
    void destroyBoneReferenceFrame(const char* bone);
    // a new frame on the skeleton's bone index, bound to the pose and hung under the transform's frame
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> createBoneReferenceFrameImpl(unsigned short index);
    // a new frame on the skeleton's mount index
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> createMountReferenceFrameImpl(unsigned short index);
    void destroyBoneReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
    // frame taken off the transform's after-frames (1.0.0's symbol; 3.0.1 inlines it into destroyBoneReferenceFrame)
    void destroyMountReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
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
    // the bone's model-space rotation from the reference pose (its transform times every parent's); false when the
    // skeleton has no such bone
    bool clacBoneRotateMS(unsigned short bone, mm::Quat* rot) const;
    static mm::mtl::RTTI m_rtti;

    // setup copies its setup info's asset handle here, cleanup sets it back to -1
    GF_ASSET_HANDLE* pad_10;
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
