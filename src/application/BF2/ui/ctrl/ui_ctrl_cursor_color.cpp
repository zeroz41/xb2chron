#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UICtrlObject.h"
#include "classes/ui/UICtrlCursorColor.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/FixStr.h"
#include "ui/UIUtil.h"

namespace ui {

UICtrlCursorColor::~UICtrlCursorColor() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

UICtrlCursorColor* UICtrlCursorColor::create(unsigned int handle, const CursorSetting& setting,
                                             UISelectObjList* list) {
    if (list == nullptr) {
        return nullptr;
    }
    list->addRef();
#line 47
    UICtrlCursorColor* ctrl = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UICtrlCursorColor(handle);
    if (ctrl == nullptr) {
        return nullptr;
    }
    ctrl->m_setting = setting;
    ctrl->m_list = list;
    ctrl->m_index = list->getIndex(false);
    ctrl->m_objHandle = handle;
    return ctrl;
}

void UICtrlCursorColor::open(int index) {
    if (m_list != nullptr) {
        m_index = index;
        m_list->setIndex(index);
    }
}

bool UICtrlCursorColor::inputChange(unsigned int index) {
    bool changed = false;
    UISelectObjList* list = m_list;
    if (index != 0xFFFFFFFF && list != nullptr && list->getSize() != 0) {
        setIndex(index);
        mm::mtl::FixStr<32> name;
        mm::mtl::FixStr<32> color;
        for (unsigned int i = 0; i < m_list->getSize(); i++) {
            UIObjectAcc acc(m_list->getObject(i));
            if (m_setting.m_dispName != nullptr) {
                bool disp = index == i;
                name.format(m_setting.m_dispName, i + 1);
                UIObjectAcc child(acc.searchChild(name.m_str));
                child.setDisp(disp);
            }
            if (m_setting.m_colorName != nullptr) {
                name.format(m_setting.m_colorName, i + 1);
                UIObjectAcc child(acc.searchChild(name.m_str));
                const char* colorName = index == i ? m_setting.m_selectColor : m_setting.m_normalColor;
                color.format("%s_mul", colorName);
                child.setMulColor(color.m_str);
                color.format("%s_add", colorName);
                child.setAddColor(color.m_str);
            }
        }
        changed = true;
    }
    return changed;
}

void UICtrlCursorColor::setDisp(bool disp) {
    inputChange(disp ? m_list->getIndex(false) : m_list->getSize() + 1);
}

void UICtrlCursorColor::update(const fw::UpdateInfo& info) {
    if (m_list != nullptr && m_list->getSize() != 0) {
        unsigned int index = m_list->getIndex(false);
        if (index != m_index) {
            m_index = index;
        }
    }
}

}  // namespace ui
