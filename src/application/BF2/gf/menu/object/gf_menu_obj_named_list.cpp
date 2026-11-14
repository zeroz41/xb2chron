#include "classes/gf/GfMenuObjNamedList.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjOption.h"
#include "classes/gf/GfMenuObjWorldMap.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuWorldMapAdapter.h"
#include "classes/gf/GfWeapon.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfGameUtilSaveData.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/SDataOption.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "gf/GfGameUtil.h"

namespace gf {

// the named enemy table (inline; the name is not the original's)
static inline unsigned char* getNamedTable() {
    return GfDataBdat::getFP(GfGameManager::isGameTypeIra() ? 0x2B : 0x2A);
}

// GfGameUtil::isDefeatNamed of a row of the named enemy table (inline; the name is not the original's)
static inline bool hasNamedRecord(unsigned int row, unsigned int mode) {
    unsigned char* fp = getNamedTable();
    if (fp == nullptr) {
        return false;
    }
    return GfGameUtil::isDefeatNamed((unsigned short)Bdat::getVal(fp, "EnemyID", row), static_cast<GFDIFF>(mode));
}

GfMenuObjNamedList::GfMenuObjNamedList(unsigned int handle)
    : GfMenuObject(handle), m_list(nullptr), m_select(nullptr), m_cursor(nullptr), m_zones(), m_zoneIndex(0), pad_7C(0),
      m_difficulty(0), m_difficultyCount(0) {
    m_list = GfMenuIDList::create();
}

GfMenuObjNamedList::~GfMenuObjNamedList() {
    if (m_cursor != nullptr) {
        m_cursor->release();
        m_cursor = nullptr;
    }
    if (m_select != nullptr) {
        m_select->release();
        m_select = nullptr;
    }
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

// initialize, updateNamedIDList and convZoneToFilter are not identical yet: $W/wip/full_draft.cpp (session 27 namedlist)

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B63990). The animation of each
// difficulty, as gf_menu_obj_btlch_order's s_difficultyAnims.
static const char* s_difficultyAnims[] = {"normal", "easy", "hard", nullptr, "ultimate"};

// a table's entry (the name is not the original's). The original's table is writable data (.data): clang 3.9 makes
// a static table constant unless its address is passed on before inlining (gf_menu_obj_btlch_order's getEntry).
template <unsigned long N, typename Index>
inline const char* getEntry(const char* (&table)[N], Index index) {
    return table[index];
}

void GfMenuObjNamedList::refreshDifficulty() {
    int value = GfMenuObjOption::getDifficultyFromIndex(m_difficulty);
    {
        ui::UIObjectAcc text(m_handle, "TXT_difficulty_index");
        if (GfDataBdat::getFP(0x169) == nullptr) {
            return;
        }
        unsigned short message = GfMenuObjUtil::getMsgIDFromList(0x169, m_difficulty + 1);
        ui::UIStr str(GfDataBdat::getFP(0x135), message);
        text.setText(str);
    }
    if ((unsigned int)value < 5) {
        const char* anim = getEntry(s_difficultyAnims, value);
        if (value != 3) {
            ui::UIObjectAcc base(m_handle, "IMG_difficulty_base");
            base.startAnimation(anim, false);
        }
    }
}

void GfMenuObjNamedList::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjNamedList::update() {
    GfMenuObject::update();
}

// ListListener::reciveEvent is not identical yet (its table and destructor come with it): $W/wip/full_draft.cpp (session 27 namedlist)

void GfMenuObjNamedList::FilterListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            unsigned int zone = m_owner->m_zones[index];
            m_owner->m_zoneIndex = index;
            m_owner->refreshFilterIcon();
            GfMenuReference::setReferenceWorldMapID(zone);
            {
                ui::UIObjectAcc main(m_owner->m_handle, "LAY_main");
                main.setDispChild(zone != 0, "LAY_list_index_zone");
            }
            ui::EventData changed(0x101);
            GfMenuObject::sendEvent(acc.getParentHandle(), changed, 0.0f);
        }
        if (prev != -1 && index != prev) {
            GfMenuObjUtil::playSECommonTab();
        }
        break;
    }
    case 0x21:
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelection(acc.m_handle, m_owner->m_zoneIndex, m_owner->m_zones.size());
        GfMenuObject::enableInput(acc.m_handle);
        m_owner->refreshFilterIcon();
        break;
    case 0x22:
        GfMenuObject::disableInput(handle);
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjNamedList::refreshFilterIcon() {
    ui::UIObjectAcc filter(m_handle, "LAY_list_filter");
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < m_zones.size(); ++i) {
        bool select = i == m_zoneIndex;
        name.format("IMG_ficon@%02d", i + 1);
        ui::UIObjectAcc icon(filter.searchChild(name.m_str));
        if (select) {
            icon.setMulColor("sys_select");
        } else {
            icon.loadDefColor();
        }
    }
}

bool GfMenuObjNamedList::sortLevel(const MenuID& a, const MenuID& b) {
    unsigned char* fp = getNamedTable();
    unsigned short arrangeA = Bdat::getVal(fp, "EnemyID", a.m_id);
    unsigned short arrangeB = Bdat::getVal(fp, "EnemyID", b.m_id);
    unsigned int lvA = GfBdatChrEnArrange::sys()->getChrEnArrangeLv(arrangeA);
    unsigned int lvB = GfBdatChrEnArrange::sys()->getChrEnArrangeLv(arrangeB);
    if (lvA == lvB) {
        return a.m_id < b.m_id;
    }
    return lvA < lvB;
}

bool GfMenuObjNamedList::isDefeated(unsigned int row) {
    return hasNamedRecord(row, GfGameManager::getBtlDifficult());
}

}  // namespace gf
