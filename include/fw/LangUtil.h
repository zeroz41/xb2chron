#ifndef FW_LANGUTIL_H
#define FW_LANGUTIL_H

#include <utility>
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace fw {
// the game's languages (1.0.0's setLangType and UIUtil::getMoneySeparetor take one); which value is which
// language is not known yet, so it names none of them. Their values are ml::DevSetting's (initialize takes the
// device's language as it is, unsigned as ml::LangType: getLangFolder zero-extends m_selectLang), and they index LangUtil.cpp's folder table (0: "jp", 1: "gb", ...)
enum LangType : unsigned int {};

// the game's language and the language of its voices, each with the device's as its default
class LangUtil {
public:
    // a language with its folder's name
    typedef mm::mtl::FixedVector<std::pair<LangType, mm::mtl::FixStr<16> >, 15> LangList;

    static void initialize();       // both from the device's language
    static int getLangType();       // the selected language (m_selectLang)
    static LangType getVoiceType();  // the selected voice language (m_selectVoice)
    static void setLangType(LangType type);  // one getLangList does not list selects 1
    // the device's languages, each with its text folder
    static LangList& getLangList(LangList& list);
    // one the voice folder is not getVoiceList's selects the selected language's voice
    static void setVoiceType(LangType type);
    // the device's languages with a voice folder no language before them has, each with that folder
    static LangList& getVoiceList(LangList& list);
    // the selected language's text folder ("jp", "gb", ...): its FixStr, which fw::LocalizeResource hands on as it is
    static const mm::mtl::FixStr<16>& getLangFolder();
    static const char* getVoiceFolder();  // the selected voice language's folder ("jp" or "us")

    static LangType m_selectLang;
    static LangType m_selectVoice;
    static LangType m_defaultLang;   // initialize's: the device's language
    static LangType m_defaultVoice;  // initialize's
};
}  // namespace fw

#endif
