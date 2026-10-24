#ifndef CLASSES_GRLIB_CONTEXT_CGLIBSYSTEMCONTEXT_H
#define CLASSES_GRLIB_CONTEXT_CGLIBSYSTEMCONTEXT_H

#include "classes/mm/mtl/PtrSingleton.h"
namespace grlib { struct CGLibMemType; }

namespace grlib { namespace context { class CGLibSystemContext; }}

namespace grlib { namespace context {
// table 0x7100B79E78
class CGLibSystemContext : public ::mm::mtl::PtrSingleton< ::grlib::context::CGLibSystemContext> {
public:
    virtual ~CGLibSystemContext();  // slot 0

    // the GPU address of a block's memory, into address
    void getVertexGpuAddress(unsigned long& address, const CGLibMemType& mem);
    // frees the block once the GPU is done with it
    void releaseDelayVertex(CGLibMemType& mem);
};
}}  // namespace grlib::context

#endif
