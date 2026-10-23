#ifndef CLASSES_CLOUD_CLOUDMAN_H
#define CLASSES_CLOUD_CLOUDMAN_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace cloud { class CloudMan; }

namespace cloud {
// table 0x7100B7A0F8
class CloudMan : public ::mm::mtl::PtrSingleton< ::cloud::CloudMan> {
public:
    virtual ~CloudMan();  // slot 0

    void setCldNum(unsigned int num);
};
}  // namespace cloud

#endif
