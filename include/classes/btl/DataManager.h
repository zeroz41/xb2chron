#ifndef CLASSES_BTL_DATAMANAGER_H
#define CLASSES_BTL_DATAMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class DataManager; }

namespace btl {
// table 0x7100B3BAF8
class DataManager : public ::mm::mtl::PtrSingleton< ::btl::DataManager> {
public:
    virtual ~DataManager();  // slot 0
};
}  // namespace btl

#endif
