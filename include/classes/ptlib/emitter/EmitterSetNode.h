#ifndef CLASSES_PTLIB_EMITTER_EMITTERSETNODE_H
#define CLASSES_PTLIB_EMITTER_EMITTERSETNODE_H

#include "ptlib/IntrusiveList.h"

namespace ptlib { class FxHeader; }

namespace ptlib { namespace emitter {
// table 0x7100B807B0; its links sit after the table pointer (EmitterManager::emitter_set_check converts a node
// back by subtracting 8)
class EmitterSetNode : public IntrusiveListNode {
public:
    virtual ~EmitterSetNode() {}  // slot 0

    // the effect file the node is linked for (EmitterManager::emitter_set_link; the name is not the original's)
    FxHeader* m_pHeader;
};
}}  // namespace ptlib::emitter

#endif
