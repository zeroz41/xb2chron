#ifndef CLASSES_ML_INIPARSER_H
#define CLASSES_ML_INIPARSER_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace ml {
// an ini text's keys (parse fills them; no table). The field names are not the original's: getKeyValue compares
// its first argument with m_key, its second with m_section, and returns m_value
class IniParser {
public:
    struct KeyParam {
        ::mm::mtl::FixStr<128> m_section;  // 0x000
        ::mm::mtl::FixStr<128> m_value;    // 0x084
        ::mm::mtl::FixStr<32> m_key;       // 0x108
    };
    void parse(char* text, int size);
    // the value of key in section, or "" (the parameter names are not the original's)
    const char* getKeyValue(const char* key, const char* section) const;
    ::mm::mtl::FixedVector<KeyParam, 128> m_keys;
};
}  // namespace ml

#endif
