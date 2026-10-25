#include "classes/ui/UITagConv.h"
#include "classes/gf/GfMenuTagAchievement.h"
#include "classes/gf/GfMenuTagDash.h"
#include "classes/gf/GfMenuTagEnhance.h"
#include "classes/gf/GfMenuTagHomuriName.h"
#include "classes/gf/GfMenuTagLink.h"
#include "classes/gf/GfMenuTagNumber.h"
#include "classes/gf/GfMenuTagNumberMoney.h"
#include "classes/gf/GfMenuTagPercent.h"
#include "classes/gf/GfMenuTagPouch.h"
#include "classes/gf/GfMenuTagSpace.h"
#include "classes/gf/GfMenuTagTownFlag.h"
#include "classes/gf/GfMenuTagUndisp.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuItemList.h"
#include "fw/LangUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Map.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "ui/UIUtil.h"
#include <math.h>
#include "stdlib.h"
#include <string.h>

namespace gf {

// a tag's parameters: (name, value) pairs
typedef mm::mtl::FixedVector<mm::mtl::MapPair<const char*, const char*>, 8> TagParams;

namespace {
// a float column's value: the low 32 bits of what getVal returns (the name is not the original's)
inline float bdatFloat(unsigned char* fp, const char* column, int id) {
    unsigned int bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getVal(fp, column, id)));
    float value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}
// the text's decimal points as commas (the name is not the original's)
template <int LEN>
inline void toDecimalComma(mm::mtl::FixStr<LEN>& text) {
    for (int i = 0; i < text.m_nLen; i++) {
        if (text.m_str[i] == '.') {
            text.m_str[i] = ',';
        }
    }
}
}  // namespace

const char* GfMenuTagEnhance::getTagName() {
    return "ML:Enhance";
}

const char* GfMenuTagEnhance::convBegin(const TagParams& params, unsigned short id) {
    int kind = 0;
    for (const mm::mtl::MapPair<const char*, const char*>* it = params.begin(); it != params.end(); ++it) {
        if (strcmp(it->first, "kind") == 0) {
            const char* value = it->second;
            if (strcmp("Param", value) == 0) {
                kind = 0;
            } else if (strcmp("Param1", value) == 0) {
                kind = 1;
            } else if (strcmp("Param2", value) == 0) {
                kind = 2;
            }
        }
    }
    static mm::mtl::FixStr<256> s_text;
    s_text = "****";
    int lang = fw::LangUtil::getLangType();
    unsigned char* fp = GfDataBdat::getFP(44);
    unsigned char* effectFp = GfDataBdat::getFP(45);
    if (id != 0) {
        switch (kind) {
        case 0: {
            unsigned short effect = reinterpret_cast<unsigned long>(Bdat::getVal(fp, "EnhanceEffect", id));
            unsigned short param = reinterpret_cast<unsigned long>(Bdat::getVal(effectFp, "Param", effect));
            s_text.format("%d", param);
            break;
        }
        case 1: {
            float value = bdatFloat(fp, "Param1", id);
            float whole;
            if (modff(value, &whole) == 0.0f) {
                s_text.format("%d", static_cast<unsigned int>(whole));
            } else {
                s_text.format("%2.1f", value);
                switch (lang) {
                case 2: case 3: case 4: case 5: case 13: case 14:
                    toDecimalComma(s_text);
                    break;
                }
            }
            break;
        }
        case 2: {
            float value = bdatFloat(fp, "Param2", id);
            float whole;
            if (modff(value, &whole) == 0.0f) {
                s_text.format("%d", static_cast<unsigned int>(whole));
            } else {
                s_text.format("%2.1f", value);
                switch (lang) {
                case 2: case 3: case 4: case 5: case 13: case 14:
                    toDecimalComma(s_text);
                    break;
                }
            }
            break;
        }
        }
    }
    return s_text.m_str;
}

}  // namespace gf
