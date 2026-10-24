#include "classes/layer/LayerTag.h"
#include "classes/layer/LayerTagStr.h"
#include "classes/ui/UITagConv.h"
#include "classes/ui/UITagParser.h"
#include "classes/ui/UITextFile.h"
#include "plugin/Bdat.h"
#include <string.h>
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ui/UITagConv.h"
#include "classes/ui/UITagParser.h"
#include "classes/ui/UITextFile.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Map.h"
#include "mtl/MemManager.h"
#include "plugin/Bdat.h"
#include "ui/UIUtil.h"

namespace ui {

UITextFile::~UITextFile() {
    ;  // stores the table (a statement the build compiles away)
}

UITextFile* UITextFile::create(unsigned char* data) {
#line 42
    UITextFile* file = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UITextFile(data);
    file->m_name = Bdat::getSheetName(data);
    return file;
}

void UITextFile::reload() {
    m_data = Bdat::getFP(m_name.m_str);
}

const char* UITextFile::getText(unsigned int id) const {
    if (m_data == nullptr) {
        return nullptr;
    }
    return Bdat::getMSText(m_data, id);
}

unsigned short UITextFile::getStyle(unsigned int id) const {
    if (m_data == nullptr) {
        return 0xFFFF;
    }
    return Bdat::getMSStyle(m_data, id);
}

}  // namespace ui
