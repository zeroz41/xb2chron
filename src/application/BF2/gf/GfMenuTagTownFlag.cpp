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

const char* GfMenuTagTownFlag::getTagName() {
    return "ML:TownFlag";
}

const char* GfMenuTagTownFlag::convBegin(const TagParams& params, unsigned short id) {
    int digit = 0;
    unsigned short value = 0;
    for (const mm::mtl::MapPair<const char*, const char*>* it = params.begin(); it != params.end(); ++it) {
        if (strcmp(it->first, "digit") == 0) {
            const char* text = it->second;
            if (strcmp("F4", text) == 0) {
                digit = 0;
            } else if (strcmp("F8", text) == 0) {
                digit = 1;
            } else if (strcmp("F16", text) == 0) {
                digit = 2;
            }
        } else if (strcmp(it->first, "value") == 0) {
            int number = atoi(it->second);
            if (number != 0) {
                value = number;
            }
        }
    }
    static mm::mtl::FixStr<16> s_text;
    s_text = "****";
    switch (digit) {
    case 0:
        if (value < 10) {
            s_text.format("%d", GfGameFlag::getLocal(4, value + 506));
        }
        break;
    case 1:
        if (value < 100) {
            s_text.format("%d", GfGameFlag::getLocal(8, value + 2120));
        }
        break;
    case 2:
        if (value < 10) {
            s_text.format("%d", GfGameFlag::getLocal(16, value + 1549));
        }
        break;
    }
    return s_text.m_str;
}

}  // namespace gf
