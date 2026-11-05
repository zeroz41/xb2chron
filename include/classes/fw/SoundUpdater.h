#ifndef CLASSES_FW_SOUNDUPDATER_H
#define CLASSES_FW_SOUNDUPDATER_H

#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw {
// what a sound object links into SoundLayerManager's list of its layer (the symbol
// FixedArray<IntrusiveList<fw::SoundUpdater>, 32> names the class). SoundLayerManager::update calls each one's
// delegate and unlinks those whose call returned 0 (clearing m_linked). GfComSound holds one (its delegate is
// GfComSound::flush). The field names are not the original's.
class SoundUpdater : public mm::mtl::IntrusiveListNodeBase {
public:
    SoundUpdater() : m_keep(false), m_linked(false) {}
    mm::mtl::Delegate<unsigned int()> m_delegate;  // called each frame of its layer
    bool m_keep;  // the last call's result was not 0; update unlinks the updater when it is false
    bool m_linked;  // whether the updater is linked into a layer's list
};
}  // namespace fw

#endif
