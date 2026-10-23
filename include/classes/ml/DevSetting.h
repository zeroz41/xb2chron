#ifndef CLASSES_ML_DEVSETTING_H
#define CLASSES_ML_DEVSETTING_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"

namespace ml { class DevSetting; }

namespace ml {
// a language the device setting names (fw::LangUtil keeps them as fw::LangType of the same value)
enum LangType : unsigned int {};
// how far the console's auto-sleep is extended: DevSettingNx::setAutoSleepExtended takes 0 (not), 1, 2 (unsafe)
enum SleepExtendType {};
class DevSettingNx;
}  // namespace ml

namespace ml {
// table 0x7100B761B0
class DevSetting : public ::mm::mtl::PtrSingleton< ::ml::DevSetting> {
public:
    virtual ~DevSetting();  // slot 0
    static LangType getLang();  // the device's language
    static void getLangList(mm::mtl::FixedVector<LangType, 15>& list);  // the languages there are
    static void setAutoSleepExtended(SleepExtendType type);

    // 0x08 the platform object: the destructor deletes it, the statics forward to it (the name is not the original's)
    DevSettingNx* m_impl;
    // the language getLang returns without a platform object; DevSettingNx::initialize sets it
    static LangType m_defaultLang;
};
}  // namespace ml

#endif
