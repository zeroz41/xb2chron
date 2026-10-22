#include "gf/GfMenuEnhanceAdapter.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

bool GfMenuEnhanceAdapter::getEnhanceCaption(unsigned int enhance, ui::UIStr& text) {
    unsigned char* message = GfDataBdat::getFP(0x19B);
    unsigned char* bdat = GfDataBdat::getFP(0x2C);
    if (!GfMenuBdat::isValidBdatID(bdat, enhance)) {
        return false;
    }
    unsigned int caption = (unsigned short)(unsigned long)Bdat::getVal(bdat, "Caption", enhance);
    // with add-on menu layer 3 usable, the table's Caption2 (when it has one and it is not 0) replaces Caption
    if (GfMenuObjUtil::fn_710048FD30(3) && Bdat::getMember(bdat, "Caption2") != nullptr) {
        unsigned short caption2 = (unsigned short)(unsigned long)Bdat::getVal(bdat, "Caption2", enhance);
        if (caption2 != 0) {
            caption = caption2;
        }
    }
    if (!GfMenuBdat::isValidBdatID(message, caption)) {
        return false;
    }
    text.copy(ui::UIStr(message, caption));
    text.m_ownerId = enhance;
    return true;
}

}  // namespace gf
