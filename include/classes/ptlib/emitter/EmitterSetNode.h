#ifndef CLASSES_PTLIB_EMITTER_EMITTERSETNODE_H
#define CLASSES_PTLIB_EMITTER_EMITTERSETNODE_H

#include "ptlib/IntrusiveList.h"

namespace ptlib { namespace emitter {
// table 0x7100B807B0; its links sit after the table pointer (EmitterManager::emitter_set_check converts a node
// back by subtracting 8)
class EmitterSetNode : public IntrusiveListNode {
public:
    virtual ~EmitterSetNode() {}  // slot 0
};
}}  // namespace ptlib::emitter

#endif
