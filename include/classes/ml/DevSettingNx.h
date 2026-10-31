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

    // a language and its code ("ja", "en-US", ...): the unit's static initializer builds a table of 15 in its
    // merged .bss block (lbl_7100ECDF40+0x2E8), so it has a constructor. The names are not the original's.
    struct LangCode {
        LangCode(LangType lang, const char* code) : m_lang(lang), m_code(code) {}
        LangType m_lang;
        const char* m_code;
    };
};
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100ECA000). th_dev_file_nx.cpp's .bss
// byte: which language DevSettingNx::getLang reports, 0 the device's, 1 Japanese (Framework::initialize: when
// "bdat/jp.bin" is there), 2 (Framework::initialize: the config's flag at 0x3C).
extern unsigned char g_devLangMode;
}  // namespace ml

#endif
