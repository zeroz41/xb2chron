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
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuReference.h"
#include "fw/LangUtil.h"
#include "gf/GfDataBlade.h"
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
// a float column's value: the low 32 bits of what getVal returns
inline float bdatFloat(unsigned char* fp, const char* column, int id) {
    unsigned int bits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getVal(fp, column, id)));
    float value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}
}  // namespace

const char* GfMenuTagAchievement::getTagName() {
    return "ML:AchieveParam";
}

const char* GfMenuTagAchievement::convBegin(const TagParams& params, unsigned short id) {
    const ui::UIStr& text = GfMenuReference::getReferenceString(id);
    if (text.isValid()) {
        return text.c_str();
    }
    return "<error>";
}

const char* GfMenuTagDash::getTagName() {
    return "ML:Dash";
}

const char* GfMenuTagDash::convBegin(const TagParams& params, unsigned short id) {
    return Bdat::getMSText(GfDataBdat::getFP(278), 1);
}

const char* GfMenuTagEnhance::getTagName() {
    return "ML:Enhance";
}

const char* GfMenuTagHomuriName::getTagName() {
    return "ML:HomuriName";
}

const char* GfMenuTagLink::getTagName() {
    return "ML:link";
}

const char* GfMenuTagNumber::getTagName() {
    return "ML:number";
}

const char* GfMenuTagNumberMoney::getTagName() {
    return "ML:number_money";
}

const char* GfMenuTagPercent::getTagName() {
    return "ML:%";
}

const char* GfMenuTagPercent::convBegin(const TagParams& params, unsigned short id) {
    switch (fw::LangUtil::getLangType()) {
    case 2: case 3: case 5: case 13: case 14:
        return " %";
    }
    return "%";
}

const char* GfMenuTagPouch::getTagName() {
    return "ML:PouchParam";
}

const char* GfMenuTagSpace::getTagName() {
    return "ML:Space";
}

const char* GfMenuTagSpace::convBegin(const TagParams& params, unsigned short id) {
    return "";
}

const char* GfMenuTagTownFlag::getTagName() {
    return "ML:TownFlag";
}

const char* GfMenuTagUndisp::getTagName() {
    return "ML:undisp";
}

const char* GfMenuTagUndisp::convBegin(const TagParams& params, unsigned short id) {
    return "";
}

}  // namespace gf
