#include "mm/mtl/Vector.h"
#include "classes/fw/AnimColPoseModifier.h"
#include "classes/fw/AnimVolumeFadeModifier.h"
#include "classes/fw/ModelObject.h"

namespace fw {

AnimColPoseModifier::~AnimColPoseModifier() {}

void AnimColPoseModifier::unbind() {
    if (m_model != nullptr) {
        m_model->release();
        m_model = nullptr;
    }
    if (m_coli != nullptr) {
        m_coli->release();
        m_coli = nullptr;
    }
    m_boneIndices.clear();
}

AnimVolumeFadeModifier::~AnimVolumeFadeModifier() {}

void AnimVolumeFadeModifier::unbind() {
    if (m_model != nullptr) {
        m_model->release();
        m_model = nullptr;
    }
}

}  // namespace fw

// a short vector's resize (its user is not written yet)
template void mm::mtl::Vector<short>::resize(size_t, const short&);
