#include "classes/gf/CreditReader.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuEquip.h"
#include "fw/LangUtil.h"
#include "gf/GfDataBlade.h"
#include "gf/GfMenuBdat.h"
#include "gf/MenuOffset.h"
#include "plugin/Bdat.h"

namespace gf {

CreditReader::CreditReader() : m_data(nullptr), m_rowCount(0), m_rows(nullptr), m_text(nullptr) {}

CreditReader::~CreditReader() {}

void CreditReader::bind(void* data, int size) {
    FileHeader* header = static_cast<FileHeader*>(data);
    m_data = header;
    if (header->m_magic == 0x545243) {
        m_rowCount = header->m_rowCount;
        int rowOffset = header->m_rowOffset;
        int textOffset = header->m_textOffset;
        m_rows = reinterpret_cast<FileRow*>(reinterpret_cast<char*>(header) + rowOffset);
        m_text = reinterpret_cast<const char*>(header) + textOffset;
        return;
    }
    m_data = nullptr;
    m_rowCount = 0;
}

int CreditReader::getRowCount() {
    return m_rowCount;
}

bool CreditReader::getRow(int index, Row& row) {
    if (m_rowCount <= 0 || index >= m_rowCount) {
        return false;
    }
    if (m_rows == nullptr) {
        return false;
    }
    if (m_text == nullptr) {
        return false;
    }
    FileRow* src = &m_rows[index];
    row.m_id = src->m_id;
    row.m_param = src->m_param;
    row.m_skip = src->m_skip > 0;
    if (src->m_skip != 0) {
        for (int i = 0; i < 3; i++) {
            row.m_columns[i].m_text = nullptr;
        }
        return true;
    }
    for (int i = 0; i < 3; i++) {
        Column& column = row.m_columns[i];
        FileColumn& file = src->m_columns[i];
        column.m_enable = file.m_enable > 0;
        column.m_param0 = file.m_param0;
        column.m_param1 = file.m_param1;
        column.m_text = file.m_textOffset == -1 ? nullptr : m_text + file.m_textOffset;
    }
    return true;
}

unsigned char* GfMenuBdat::s_BdatArray[7];

void GfMenuBdat::initialize() {
    s_BdatArray[0] = Bdat::getFP("MNU_OffsetList");
    s_BdatArray[1] = Bdat::getFP("MNU_IconList");
    s_BdatArray[2] = Bdat::getFP("MNU_Layer");
    s_BdatArray[3] = Bdat::getFP("FLD_FieldSkillList");
    s_BdatArray[4] = Bdat::getFP("ITM_CollectionList");
    s_BdatArray[5] = Bdat::getFP("itm_collection");
    s_BdatArray[6] = Bdat::getFP("BTL_Arts_Dr");
}

bool GfMenuBdat::isValidBdatID(unsigned char* bdat, int id) {
    if (bdat == nullptr || id < Bdat::getIdTop(bdat)) {
        return false;
    }
    return id < Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat);
}

int GfMenuBdat::getValueLevel(unsigned char* bdat, unsigned int value) {
    int top = Bdat::getIdTop(bdat);
    if (Bdat::getIdCount(bdat) < 2) {
        return 1;
    }
    unsigned int first = Bdat::getVal(bdat, "value", top);
    unsigned int second = Bdat::getVal(bdat, "value", top + 1);
    if (first > second) {
        for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
            if ((unsigned int)Bdat::getVal(bdat, "value", top + i) <= value) {
                return i + 1;
            }
        }
    } else {
        for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
            if ((unsigned int)Bdat::getVal(bdat, "value", top + i) >= value) {
                return i + 1;
            }
        }
    }
    return Bdat::getIdCount(bdat);
}

void GfMenuBdat::getMenuOffset(int id, MenuOffset& offset) {
    unsigned char* bdat = s_BdatArray[0];
    if (!isValidBdatID(bdat, id)) {
        return;
    }
    Bdat::uVal val;
    val.uint = Bdat::getVal(bdat, "offs_x", id);
    offset.m_offset.x = val.real;
    val.uint = Bdat::getVal(bdat, "offs_y", id);
    offset.m_offset.y = val.real;
    val.uint = Bdat::getVal(bdat, "offs_z", id);
    offset.m_offset.z = val.real;
    offset.m_bone = reinterpret_cast<const char*>(Bdat::getVal(bdat, "bone_name", id));
    if (*offset.m_bone == '\0') {
        offset.m_bone = nullptr;
    }
}

int GfMenuBdat::getIconImageIndex(int icon) {
    unsigned char* bdat = s_BdatArray[1];
    if (isValidBdatID(bdat, icon)) {
        return (unsigned char)Bdat::getVal(bdat, "icon_index", icon);
    }
    return 0;
}

unsigned char* GfMenuBdat::getItemDataFP(unsigned char type, unsigned short id) {
    switch (type) {
    case 1:
        return GfDataBdat::getFP(0x95);
    case 2:
        return GfDataBdat::getFP(0x97);
    case 3:
        return GfDataBdat::getFP(0x9A);
    case 5:
        return GfDataBdat::getFP(0xA1);
    case 6: {
        unsigned char* bdat = GfDataBdat::getFP(0x9D);
        if (id < Bdat::getIdTop(bdat)) {
            return GfDataBdat::getFP(0x9C);
        }
        return bdat;
    }
    case 7:
        return GfDataBdat::getFP(0x93);
    case 8:
        return GfDataBdat::getFP(0x94);
    case 9:
        return GfDataBdat::getFP(0x98);
    case 10:
        return GfDataBdat::getFP(0xA3);
    case 11:
        return GfDataBdat::getFP(0xA0);
    case 12:
        return GfDataBdat::getFP(0xA2);
    case 14:
        return GfDataBdat::getFP(0x9E);
    case 15:
        return GfDataBdat::getFP(0x9F);
    case 16:
        return GfDataBdat::getFP(0x50);
    case 17:
        return GfDataBdat::getFP(0x51);
    case 18:
        return GfDataBdat::getFP(0x52);
    case 19:
        return GfDataBdat::getFP(0x53);
    case 20:
        return GfDataBdat::getFP(0x54);
    }
    return nullptr;
}

unsigned char* GfMenuBdat::getItemTextFP(unsigned char type, unsigned short id) {
    switch (type) {
    case 1:
        return GfDataBdat::getFP(0x1CE);
    case 2:
        return GfDataBdat::getFP(0x1CC);
    case 3:
        return GfDataBdat::getFP(0x1CB);
    case 5:
        return GfDataBdat::getFP(0x1D1);
    case 6:
        return GfDataBdat::getFP(0x1D0);
    case 7:
        return GfDataBdat::getFP(0x1C6);
    case 8:
        return GfDataBdat::getFP(0x1D2);
    case 9:
        return GfDataBdat::getFP(0x1CB);
    case 10:
        return GfDataBdat::getFP(0x1C9);
    case 11:
        return GfDataBdat::getFP(0x1C7);
    case 12:
        return GfDataBdat::getFP(0x1C5);
    case 14:
        return GfDataBdat::getFP(0x1CA);
    case 15:
        return GfDataBdat::getFP(0x1C8);
    case 16:
        return GfDataBdat::getFP(0x1A2);
    case 17:
        return GfDataBdat::getFP(0x1A4);
    case 18:
        return GfDataBdat::getFP(0x1CB);
    case 19:
        return GfDataBdat::getFP(0x1A3);
    case 20:
        return GfDataBdat::getFP(0x1CB);
    }
    return nullptr;
}

int GfMenuBdat::getIconIDFromArtsID(unsigned short arts) {
    unsigned char* bdat = s_BdatArray[6];
    int icon = 1;
    if (isValidBdatID(bdat, arts)) {
        // the column is 16 bits wide; 0 keeps the default icon
        unsigned long id = (unsigned short)Bdat::getVal(bdat, "UI", arts);
        if (id != 0) {
            icon = id;
        }
    }
    return icon;
}

int GfMenuBdat::getIconIDFromWeatherType(unsigned int type) {
    return type + 0xA7;
}

const char* GfMenuBdat::getSortKeyName() {
    // a language and its sort key column (the type, field and table names are not the original's; the symbols
    // leave the table unnamed: lbl_7100B5E478)
    struct SortKey {
        int m_lang;
        const char* m_name;
    };
    static const SortKey s_sortKeyList[] = {
        {0, "sortJP"},  {3, "sortGE"}, {2, "sortFR"},  {5, "sortSP"}, {4, "sortIT"},
        {12, "sortGB"}, {6, "sortCN"}, {11, "sortTW"}, {7, "sortKR"},
    };
    int lang = fw::LangUtil::getLangType();
    for (int i = 0; i < 9; i++) {
        if (s_sortKeyList[i].m_lang == lang) {
            return s_sortKeyList[i].m_name;
        }
    }
    return nullptr;
}

unsigned char* GfMenuBdat::getBladeDataFP(unsigned int blade, unsigned int& id) {
    unsigned char* bdat;
    if (GfDataBlade::isCommonBlade(blade)) {
        bdat = GfDataBdat::getFP(0xE3);
        blade = GfDataBlade::getBLD_NameList(blade);
    } else {
        bdat = GfDataBdat::getFP(0x8A);
    }
    id = blade;
    return bdat;
}

GfMenuEquip::GfMenuEquip(const GfSetupParam& param) {
    initialize(param);
}

void GfMenuEquip::initialize(const GfSetupParam& param) {
    m_initialized = true;
}

GfMenuEquip::~GfMenuEquip() {}

void GfMenuEquip::build(const GfSetupParam& param) {
#line 39
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuEquip(param);
}

void GfMenuEquip::destroy() {
    GfMenuEquip* menu = get();
    menu->finalize();
    delete menu;
}

void GfMenuEquip::finalize() {
    m_initialized = false;
}

bool GfMenuEquip::isInitialized() {
    GfMenuEquip* menu = get();
    if (menu != nullptr) {
        return menu->m_initialized;
    }
    return false;
}

void GfMenuEquip::postUpdate(const fw::UpdateInfo& info) {}

}  // namespace gf
