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

const char* GfMenuTagNumber::getTagName() {
    return "ML:number";
}

const char* GfMenuTagNumber::convBegin(const TagParams& params, unsigned short id) {
    int digit = 1;
    int padding = 0;
    for (const mm::mtl::MapPair<const char*, const char*>* it = params.begin(); it != params.end(); ++it) {
        if (strcmp(it->first, "digit") == 0) {
            int value = atoi(it->second);
            if (value != 0) {
                digit = value;
            }
        } else if (strcmp(it->first, "padding") == 0) {
            const char* value = it->second;
            if (strcmp("none", value) == 0) {
                padding = 0;
            }
            if (strcmp("space", value) == 0) {
                padding = 1;
            }
            if (strcmp("zero", value) == 0) {
                padding = 2;
            }
        }
    }
    static mm::mtl::FixStr<16> s_format;
    switch (padding) {
    case 0:
        s_format = "%d";
        break;
    case 1:
        s_format.format("%%%dd", digit);
        break;
    case 2:
        s_format.format("%%0%dd", digit);
        break;
    }
    return s_format.m_str;
}

}  // namespace gf
