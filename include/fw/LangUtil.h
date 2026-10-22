#ifndef FW_LANGUTIL_H
#define FW_LANGUTIL_H

namespace fw {
// the game's languages (1.0.0's setLangType and UIUtil::getMoneySeparetor take one); which value is which
// language is not known yet, so it names none of them
enum LangType : int {};

// the game's language
class LangUtil {
public:
    static int getLangType();  // the selected language (m_selectLang)
};
}  // namespace fw

#endif
