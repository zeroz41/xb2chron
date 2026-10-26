#ifndef CLASSES_FW_TRANSFORMUPDATER_H
#define CLASSES_FW_TRANSFORMUPDATER_H

#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/ReferenceFrame.h"

namespace fw {
// table none: the frames an object resolves each frame, linked into TransformManager's list for its layer (its links
// are a base: TransformManager::update walks the list and calls resolveWorldTrasform on each node). GfComTransform
// holds one at 0x20.
class TransformUpdater : public ::mm::mtl::IntrusiveListNodeBase {
public:
    void resolveWorldTrasform();

    // the frames resolveWorldTrasform walks first (GfComTransform::addReferenceFrame adds one; the name is not the
    // original's)
    mm::mtl::Vector<mm::mtl::IntrusivePtr<ReferenceFrame> > m_referenceFrames;
    // the frames it walks second (GfComTransform::addAfterReferenceFrame adds one; the name is not the original's)
    mm::mtl::Vector<mm::mtl::IntrusivePtr<ReferenceFrame> > m_afterReferenceFrames;
};
}  // namespace fw

#endif
