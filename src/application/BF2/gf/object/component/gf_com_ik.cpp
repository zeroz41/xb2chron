#include "classes/fw/IKFootGroundInterface.h"
#include "classes/gf/GfComIK/FootGround.h"
#include "fw/IkResolver.h"
#include "classes/fw/AnimationManager.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/GfComIK/FootGround.h"
#include "classes/gf/GfComIK/Ground.h"
#include "classes/gf/GfComIK/ViewerListener.h"
#include "classes/fw/AnimationManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/Message.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "classes/fw/BlowRotateIkSolver.h"
#include "classes/fw/LookIkSolver.h"
#include "classes/fw/PlacementGroundSolver.h"
#include "classes/fw/RotateIkSolver.h"
#include "classes/fw/RotateLocalIkSolver.h"
#include "classes/fw/SlopeGroundSolver.h"
#include "classes/fw/SphericalCoordinatesIkSolver.h"
#include "classes/fw/SpineRotateIKSolver.h"
#include "classes/fw/TransLocalIkSolver.h"
#include "classes/fw/TwoCharaGroundSolver.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComTransform.h"

namespace gf {

bool GfComIK::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    return msg.m_id == 0x1000003;
}

GfComIK::GfComIK() : m_footCount(0), m_pViewer(nullptr) {
    m_solvers.setAllocator(getAllocator(ALLOCATOR(0)));
    m_viewerListener.m_pOwner = this;
}

GfComIK::~GfComIK() {}

// whether the skeleton has a bone labelled foot `index` (inline: the name is not the original's)
static inline bool hasFootLabel(const anm::Skeleton* skeleton, unsigned short index) {
    if (const anm::Bone* bone = skeleton->getBoneFromLabel(static_cast<anm::LabelType>(0), index)) {
        if (bone->m_name != nullptr) {
            return true;
        }
    }
    return false;
}

void GfComIK::setup(const SetupInfo& info) {
    m_solvers.resize(9, mm::mtl::IntrusivePtr<fw::IkSolver>());
    unsigned int footCount = 0;
    if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
        if (model->m_pose != nullptr) {
            if (const anm::Skeleton* skeleton = model->m_pose->m_pSkeleton) {
                if (hasFootLabel(skeleton, 2)) {
                    footCount = 6;
                } else if (hasFootLabel(skeleton, 1)) {
                    footCount = 4;
                } else if (hasFootLabel(skeleton, 0)) {
                    footCount = 2;
                } else {
                    footCount = 0;
                }
            }
        }
    }
    m_footCount = footCount;
    if (GfComProperty* property = m_owner->getComponent<GfComProperty>(5)) {
        if (const GfEnvProperty* env = property->m_env.get()) {
#line 267
            m_ground.reset(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) Ground());
            m_ground->setup(env, m_footCount);
        }
    }
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        fw::IkResolver& resolver = *this;
        manager->addIkResolver(getLayer(), resolver);
    }
}

void GfComIK::cleanup() {
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        manager->removeIkResolver(getLayer(), *this);
    }
    m_solvers.clear();
    m_ground.reset();
}

fw::RotateIkSolver* GfComIK::createRotateBodyIK(const char* bone) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::RotateIkSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        solver = fw::RotateIkSolver::create(bone, frame, *model->m_pose);
        m_solvers[0] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::LookIkSolver* GfComIK::createLookIK(float spineFadeInTime, float spineFadeOutTime) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::LookIkSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        fw::LookIkSolver::Description desc;
        desc.spineFadeInTime = spineFadeInTime;
        desc.spineFadeOutTime = spineFadeOutTime;
        solver = fw::LookIkSolver::create(desc, frame, *model->m_pose);
        m_solvers[3] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::PlacementGroundSolver* GfComIK::createPlacementGroundIK(float maxDown) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::PlacementGroundSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        fw::PlacementGroundSolver::Description desc;
        desc.maxDown = maxDown;
        desc.footCount = m_footCount;
        solver = fw::PlacementGroundSolver::create(desc, frame, *model->m_pose, m_ground.get());
        m_solvers[2] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::SlopeGroundSolver* GfComIK::createSlopeGroundIK(float limit0, float limit1) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::SlopeGroundSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        fw::SlopeGroundSolver::Description desc;
        desc.footCount = m_footCount;
        desc.pad_14 = limit0;
        desc.pad_18 = limit1;
        solver = fw::SlopeGroundSolver::create(desc, frame, *model->m_pose, m_ground.get());
        m_solvers[0] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::TwoCharaGroundSolver* GfComIK::createTwoCharaGroundIK(float maxDown, const char* mainRootBone, const char* subRootBone) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::TwoCharaGroundSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        fw::TwoCharaGroundSolver::Description desc;
        desc.maxDown = maxDown;
        desc.footCount = m_footCount;
        desc.mainRootBone = mainRootBone;
        desc.subRootBone = subRootBone;
        solver = fw::TwoCharaGroundSolver::create(desc, frame, *model->m_pose, m_ground.get());
        m_solvers[2] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::SphericalCoordinatesIkSolver* GfComIK::createSphericalCoordinatesIkSolver(const fw::ParamAdapter& param, const char* bone) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::SphericalCoordinatesIkSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        solver = fw::SphericalCoordinatesIkSolver::create(param, bone, frame, *model->m_pose);
        m_solvers[8] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::SpineRotateIKSolver* GfComIK::createSpineRotateIkSolver(const fw::ParamAdapter& param, const char* firstBone, const char* secondBone) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::SpineRotateIKSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        solver = fw::SpineRotateIKSolver::create(param, firstBone, secondBone, frame, *model->m_pose);
        m_solvers[4] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::TransLocalIkSolver* GfComIK::createTransEyeIkSolver(unsigned int slot, const char* bone) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::TransLocalIkSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        solver = fw::TransLocalIkSolver::create(bone, frame, *model->m_pose);
        m_solvers[slot] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::RotateLocalIkSolver* GfComIK::createRotateEyeIkSolver(unsigned int slot, const char* bone) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::RotateLocalIkSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (model->m_pose != nullptr) {
        solver = fw::RotateLocalIkSolver::create(bone, frame, *model->m_pose);
        m_solvers[slot] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

fw::BlowRotateIkSolver* GfComIK::createBlowRotateIkSolver(const char* bone) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    GfComModel* model = m_owner->findComponent<GfComModel>(1);
    fw::BlowRotateIkSolver* solver = nullptr;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame = transform->getFrame();
    if (anm::Pose* pose = model->m_pose) {
        unsigned short index = 1;
        if (bone != nullptr) {
            unsigned short found = pose->m_pSkeleton->getBoneIndex(bone);
            if (found != 0xFFFF) {
                index = found;
            }
        }
        solver = fw::BlowRotateIkSolver::create(frame, *pose, index);
        m_solvers[1] = solver;
        if (solver != nullptr) {
            solver->release();
        }
    }
    return solver;
}

void GfComIK::changeLayer(unsigned int oldLayer, unsigned int newLayer) {
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        manager->removeIkResolver(getLayer(), *this);
        manager->addIkResolver(newLayer, *this);
    }
}

void GfComIK::ViewerListener::onWkStandbyLogout() {
    if (m_pOwner != nullptr) {
        m_pOwner->m_pViewer = nullptr;
    }
}

fw::IKFootGroundInterface* GfComIK::Ground::getFootGround(fw::IKFootIndex index) {
    return &m_feet[index];
}

const mm::Plane* GfComIK::Ground::getPlane() const {
    const GfEnvProperty::Ground* ground = m_result != nullptr && m_result->m_valid ? m_result->getGround(0) : nullptr;
    return ground == nullptr ? nullptr : &ground->m_plane;
}

const mm::Vec3* GfComIK::Ground::getHitPos() const {
    if (m_result != nullptr) {
        return m_result->m_valid ? &m_result->getGround(0)->m_position : nullptr;
    }
    return nullptr;
}

// the sub ground's hit is the last one
const mm::Plane* GfComIK::Ground::getPlaneSub() const {
    const GfEnvProperty::Ground* ground = m_result != nullptr && m_result->m_valid ? m_result->getGround(7) : nullptr;
    return ground == nullptr ? nullptr : &ground->m_plane;
}

const mm::Vec3* GfComIK::Ground::getHitPosSub() const {
    if (m_result != nullptr) {
        return m_result->m_valid ? &m_result->getGround(7)->m_position : nullptr;
    }
    return nullptr;
}

GfComIK::Ground::~Ground() {}

const mm::Plane* GfComIK::FootGround::getPlane() const {
    const GfEnvProperty::Ground* ground = m_result != nullptr ? m_result->getGround(m_index) : nullptr;
    return ground == nullptr ? nullptr : &ground->m_plane;
}

const mm::Vec3* GfComIK::FootGround::getHitPos() const {
    if (m_result != nullptr) {
        return &m_result->getGround(m_index)->m_position;
    }
    return nullptr;
}

mm::mtl::RTTI GfComIK::m_rtti("GfComIK", &GfComponent::m_rtti, nullptr);

}  // namespace gf
