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

const char* GfMenuTagHomuriName::getTagName() {
    return "ML:HomuriName";
}

const char* GfMenuTagHomuriName::convBegin(const TagParams& params, unsigned short id) {
    unsigned char* fp = GfDataBdat::getFP(425);
    if (fp == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const char*>(
        Bdat::getVal(fp, "name", GfDataBlade::isHomuriNameHikari() + Bdat::getIdTop(fp)));
}

}  // namespace gf
