#ifndef CLASSES_ML_DEVSETTING_H
#define CLASSES_ML_DEVSETTING_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"

namespace ml { class DevSetting; }

namespace ml {
// a language the device setting names (fw::LangUtil keeps them as fw::LangType of the same value)
enum LangType : unsigned int {};
}  // namespace ml

namespace ml {
// table 0x7100B761B0
class DevSetting : public ::mm::mtl::PtrSingleton< ::ml::DevSetting> {
public:
    virtual ~DevSetting();  // slot 0
    static LangType getLang();  // the device's language
    static void getLangList(mm::mtl::FixedVector<LangType, 15>& list);  // the languages there are
};
}  // namespace ml

#endif
