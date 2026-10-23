#ifndef CLASSES_ML_DEVSETTINGNX_H
#define CLASSES_ML_DEVSETTINGNX_H

#include "classes/ml/DevSetting.h"

namespace ml {
// table 0x7100B769C8
class DevSettingNx {
public:
    virtual ~DevSettingNx();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    // the device's language, 15 for none (1.0.0's name; initialize asserts "getLang() is DEV_LANG_INVALID!!")
    virtual LangType getLang() const;  // slot 4
    // Placeholder name: changed in 3.0.1, nothing in 1.0.0's place names it. A member because it fills
    // DevSettingNx's slot 5. What it does: DevSetting::getLangList clears its list and passes it here.
    virtual void fn_71006AEDA8(mm::mtl::FixedVector<LangType, 15>& list);  // slot 5
    virtual void setAutoSleepExtended(SleepExtendType type);  // slot 6
    virtual bool isAutoSleepExtended() const;  // slot 7
};
}  // namespace ml

#endif
