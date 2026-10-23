#include "classes/gf/GfMenuQuestAdapter.h"
#include "classes/gf/GfMenuQuestAdapter/IConverter.h"
#include "classes/gf/GfMenuQuestAdapter/ListConverter.h"
#include "classes/gf/GfMenuQuestAdapter/ReferenceConverter.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/GfDataQuest.h"
#include "gf/GfDataUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestTask.h"
#include "gf/GfQuestUtil.h"
#include "gf/QuestListAcc.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuQuestList.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "classes/ui/UIObjectPlugin.h"
#include "classes/ui/UIObjectTextPlugin.h"
#include "gf/GfMenuBdat.h"
#include "gf/QuestTaskParam.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/RTTI.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuQuestAdapter::~GfMenuQuestAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
    m_reference = nullptr;
}

GfMenuQuestAdapter* GfMenuQuestAdapter::createFromReference(unsigned int handle,
                                                            mm::mtl::IntrusivePtr<GfMenuReferenceQuest> reference,
                                                            unsigned int type, bool changed) {
#line 299
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceConverter(reference);
    QuestID id;
    converter->getQuestID(id);
    GfMenuQuestAdapter* adapter = create(handle, id, type, changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuQuestAdapter* GfMenuQuestAdapter::createFromList(unsigned int handle, GfMenuQuestList* list, int index,
                                                       unsigned int type, bool changed) {
#line 317
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index);
    QuestID id;
    converter->getQuestID(id);
    GfMenuQuestAdapter* adapter = create(handle, id, type, changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

bool GfMenuQuestAdapter::getParamIcon(QuestID id, unsigned int type, unsigned int& icon) {
    if (id.empty()) {
        return false;
    }
    switch (type) {
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14: {
        unsigned long index = type - 3;
        mm::mtl::FixedVector<unsigned short, 32> characters;
        GfQuestUtil::getNeedCharacterByQuestTask(characters, id, m_task);
        if (index >= characters.size()) {
            return false;
        }
        unsigned short chara = characters[index];
        if (chara == 0) {
            return false;
        }
        int objType = GfDataUtil::getObjTypeByCharaId(chara);
        if (objType - 3U >= 2) {
            return false;
        }
        DataParamAcc acc(objType, characters[index], GimmickType(0));
        if (!acc.isValid()) {
            return false;
        }
        int face = GfMenuObjUtil::getFaceIconID(acc);
        if (face == 0) {
            return false;
        }
        icon = GfMenuBdat::getIconImageIndex(face);
        return true;
    }
    case 57: {
        int listIcon = QuestListAcc::get()->getListQuestIcon(id);
        if (listIcon != 0) {
            icon = listIcon;
        }
        return true;
    }
    default:
        return false;
    }
}

}  // namespace gf
