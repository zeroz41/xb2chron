#include "classes/ui/UIBuildInfoBdat.h"
#include "plugin/Bdat.h"
#include "ui/UIUtil.h"

namespace ui {

UIBuildInfoBdat::UIBuildInfoBdat(const char* name) : m_name(name) {
    Bdat::getFP(name);
}

UIBuildInfoBdat::~UIBuildInfoBdat() {
    ;
}

unsigned int UIBuildInfoBdat::getObjectNum() const {
    return Bdat::getIdCount(Bdat::getFP(m_name));
}

void UIBuildInfoBdat::getObjectData(unsigned int index, ui::UIBuildInfo::ObjectData& data) const {
    unsigned char* fp = Bdat::getFP(m_name);
    UIUtil::getBdatFP(5);
    int id = Bdat::getIdTop(fp) + index;
    data = ObjectData();
    data.m_type = Bdat::getVal(fp, "type", id);
    if (Bdat::getMember(fp, "name")) {
        data.m_name = (const char*)Bdat::getVal(fp, "name", id);
    }
    if (Bdat::getMember(fp, "parent")) {
        data.m_parent = (const char*)Bdat::getVal(fp, "parent", id);
    }
    if (Bdat::getMember(fp, "attach_layout")) {
        data.m_attachLayout = (const char*)Bdat::getVal(fp, "attach_layout", id);
    }
    if (Bdat::getMember(fp, "offs_x") && Bdat::getMember(fp, "offs_y")) {
        data.m_offsX = Bdat::getVal(fp, "offs_x", id);
        data.m_offsY = Bdat::getVal(fp, "offs_y", id);
    }
    if (Bdat::getMember(fp, "priority")) {
        data.m_priority = Bdat::getVal(fp, "priority", id);
    }
    if (Bdat::getMember(fp, "def_undisp")) {
        data.m_defUndisp = (unsigned char)Bdat::getVal(fp, "def_undisp", id) == 1;
    }
    if (Bdat::getMember(fp, "resource")) {
        int resource = Bdat::getVal(fp, "resource", id);
        if (resource != 0) {
            switch (data.m_type) {
            case 2:
            case 6:
                data.m_resourceFile = (const char*)Bdat::getVal(UIUtil::getBdatFP(0), "file", resource);
                break;
            case 3:
            case 7:
                data.m_resourceFile = (const char*)Bdat::getVal(UIUtil::getBdatFP(1), "file", resource);
                break;
            case 8:
                data.m_resourceFile = (const char*)Bdat::getVal(UIUtil::getBdatFP(2), "file", resource);
                break;
            case 9:
                data.m_resourceFile = (const char*)Bdat::getVal(UIUtil::getBdatFP(3), "file", resource);
                data.m_resourceIsFile = true;
                break;
            case 10:
                data.m_resourceFile = (const char*)Bdat::getVal(UIUtil::getBdatFP(4), "file", resource);
                break;
            }
        }
    }
    if (Bdat::getMember(fp, "text_id")) {
        int textId = Bdat::getVal(fp, "text_id", id);
        if (textId != 0) {
            data.m_textId = textId;
        }
        if (Bdat::getMember(fp, "text_align_h")) {
            data.m_textAlignH = Bdat::getVal(fp, "text_align_h", id);
        }
        if (Bdat::getMember(fp, "text_align_v")) {
            data.m_textAlignV = Bdat::getVal(fp, "text_align_v", id);
        }
        if (Bdat::getMember(fp, "text_prop")) {
            data.m_textProp = Bdat::getVal(fp, "text_prop", id);
        }
    }
    if (Bdat::getMember(fp, "input_type") && Bdat::getMember(fp, "input_id")) {
        data.m_inputType = Bdat::getVal(fp, "input_type", id);
        data.m_inputId = Bdat::getVal(fp, "input_id", id);
    }
}

}  // namespace ui
