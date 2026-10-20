#ifndef CLASSES_ML_LANGUAGEINFO_H
#define CLASSES_ML_LANGUAGEINFO_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class LanguageInfo; }

namespace ml {
// table 0x7100B785B8
class LanguageInfo : public ::mm::mtl::PtrSingleton< ::ml::LanguageInfo> {
public:
    virtual ~LanguageInfo();  // slot 0
};
}  // namespace ml

#endif
