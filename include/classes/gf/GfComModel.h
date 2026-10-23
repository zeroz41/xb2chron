#ifndef CLASSES_GF_GFCOMMODEL_H
#define CLASSES_GF_GFCOMMODEL_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
#include "classes/fw/ReferenceFrame.h"
#include "mm/mtl/IntrusivePtr.h"
namespace anm { class ExtraTruckBuffer; }
namespace anm { class Pose; }
namespace fw { class Message; }
namespace fw { class ModelObject; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B667B8
class GfComModel : public ::gf::GfComponent {
public:
    class ViewerListener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComModel();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> createBoneReferenceFrame(const char* bone);
    void destroyBoneReferenceFrame(const char* bone);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_10[0x8];
    // the model's object: GFOBJ_INFO::createVolumeFade fades its interface (the name is not the original's)
    fw::ModelObject* m_model;
    // the model's frame (GfComDynamics binds its dynamics to it) (the name is not the original's)
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;
    unsigned char pad_28[0x8];
    // the model's pose and extra truck buffer: GfComDynamics binds its dynamics to the pose, GfComPackAnim::Mot::play
    // its sampler to both (the names are not the original's)
    anm::Pose* m_pose;
    anm::ExtraTruckBuffer* m_extraTruckBuffer;
    unsigned char pad_40[0x10a8];
    // each gf::VFPARTS's opacity: GfVolumeFade::applyFadeRatio stores 1 - the part's fade ratio (the name is not
    // the original's)
    float m_partsAlpha[6];
};
}  // namespace gf

#endif
