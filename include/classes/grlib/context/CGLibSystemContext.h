#ifndef CLASSES_GRLIB_CONTEXT_CGLIBSYSTEMCONTEXT_H
#define CLASSES_GRLIB_CONTEXT_CGLIBSYSTEMCONTEXT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace grlib { namespace context { class CGLibSystemContext; }}

namespace grlib { namespace context {
// table 0x7100B79E78
class CGLibSystemContext : public ::mm::mtl::PtrSingleton< ::grlib::context::CGLibSystemContext> {
public:
    virtual ~CGLibSystemContext();  // slot 0
};
}}  // namespace grlib::context

#endif
