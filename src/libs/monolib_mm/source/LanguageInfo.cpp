#define MM_LIB_FROM_MONOLIB_MM
#include "classes/ml/IniParser.h"
#include "classes/ml/LanguageInfo.h"
#include "ml/MlMem.h"
#include "mtl/MemManager.h"
#include <string.h>

namespace ml {

const char* IniParser::getKeyValue(const char* key, const char* section) const {
    for (const KeyParam* it = m_keys.begin(); it != m_keys.end(); ++it) {
        if (strcmp(it->m_section.m_str, section) == 0 && strcmp(it->m_key.m_str, key) == 0) {
            return it->m_value.m_str;
        }
    }
    return "";
}

LanguageInfo::LanguageInfo() : pad_08(nullptr), pad_28(nullptr), pad_30(0) {}

LanguageInfo::~LanguageInfo() {}

void LanguageInfo::initialize(mtl::ALLOC_HANDLE) {
    get()->m_table.reserve(MlMem::getProductMem(), 64);
}

}  // namespace ml
