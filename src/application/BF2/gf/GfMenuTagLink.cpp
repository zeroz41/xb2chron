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

const char* GfMenuTagLink::getTagName() {
    return "ML:link";
}

const char* GfMenuTagLink::convBegin(const TagParams& params, unsigned short id) {
    const char* kind = nullptr;
    int linkId = 0;
    for (const mm::mtl::MapPair<const char*, const char*>* it = params.begin(); it != params.end(); ++it) {
        if (strcmp(it->first, "kind") == 0) {
            kind = it->second;
        } else if (strcmp(it->first, "id") == 0) {
            linkId = atoi(it->second);
        }
    }
    if (linkId != 0 && kind != nullptr) {
        if (strcmp(kind, "ene") == 0) {
            unsigned char* fp = Bdat::getFP("CHR_EnArrange");
            int top = Bdat::getIdTop(fp);
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int row = top + i;
                if (static_cast<unsigned short>(Bdat::getVal(fp, "Name", row)) == linkId) {
                    if (row != 0) {
                        GfMenuReference::addEnemyLink(row);
                    }
                    break;
                }
            }
        } else if (strcmp(kind, "colle") == 0) {
            unsigned char* fp = Bdat::getFP("ITM_CollectionList");
            int top = Bdat::getIdTop(fp);
            for (int i = 0; i < Bdat::getIdCount(fp); i++) {
                int row = top + i;
                if (static_cast<unsigned short>(Bdat::getVal(fp, "Name", row)) == linkId) {
                    if (row != 0) {
                        MenuItemInfo item;
                        item.m_type = 7;
                        item.m_id = row;
                        GfMenuReference::addItemLink(item);
                    }
                    break;
                }
            }
        }
    }
    return nullptr;
}

}  // namespace gf
