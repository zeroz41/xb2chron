#ifndef CLASSES_FW_CAMERAPLUGIN_H
#define CLASSES_FW_CAMERAPLUGIN_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class Camera; }

namespace fw {
// what a camera layer runs on its camera (fw::CameraLayer::pushPlugin/popPlugin take an
// mm::mtl::IntrusivePtr<fw::CameraPlugin>&): a counted object, so the pointer's end releases it. No table of its
// own is identified; gf::ShipRollPlugin's has update(fw::Camera*) after the destructors.
class CameraPlugin : public ::mm::mtl::ReferenceObject {
public:
    virtual void update(fw::Camera*) = 0;

    // unlinked at construction (gf::ShipRollPlugin's inlined constructor; the name is not the original's)
    mm::mtl::IntrusiveListNodeBase m_node;
};
}  // namespace fw

#endif
