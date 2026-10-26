#include "classes/gf/GfMenuMsgList.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfMenuBdat.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuMsgList::~GfMenuMsgList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuMsgList* GfMenuMsgList::create() {
#line 41
    GfMenuMsgList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuMsgList;
    list->addRef();
    return list;
}

void GfMenuMsgList::setBdat(unsigned int dataBdat, unsigned int msgBdat) {
    unsigned char* data = nullptr;
    if (dataBdat != 0) {
        data = GfDataBdat::getFP(dataBdat);
        if (data == nullptr) {
            return;
        }
    }
    unsigned char* msg = GfDataBdat::getFP(msgBdat);
    if (msg != nullptr) {
        m_dataBdat = data;
        m_msgBdat = msg;
    }
}

bool GfMenuMsgList::getMsg(int index, ui::UIStr& str, bool page) {
    if (m_msgBdat == nullptr) {
        return false;
    }
    if (page) {
        index = getPageIndex(index);
    }
    MsgID* contents;
    if (index == -1) {
        contents = &getContents(getIndex(false));
    } else {
        if (index >= getSize()) {
            return false;
        }
        contents = &getContents(index);
    }
    unsigned int id = contents->m_id;
    if (id == 0) {
        return false;
    }
    if (m_dataBdat != nullptr) {
        if (!GfMenuBdat::isValidBdatID(m_dataBdat, id)) {
            return false;
        }
        id = (unsigned short)Bdat::getVal(m_dataBdat, "name", id);
        if (id == 0) {
            return false;
        }
    }
    if (GfMenuBdat::isValidBdatID(m_msgBdat, id)) {
        str.setupMstxt(m_msgBdat, id);
        return true;
    }
    return false;
}

void GfMenuMsgList::fn_7100379F9C(bool descending) {
    if (getSize() == 0) {
        return;
    }
    std::function<bool(const MsgID&, const MsgID&)> compare;
    compare = descending ? fn_710037A0E0 : fn_710037A10C;
    sort(compare);
}

bool GfMenuMsgList::fn_710037A0E0(const MsgID& a, const MsgID& b) {
    if (a.m_sortKey == b.m_sortKey) {
        return a.m_id < b.m_id;
    }
    return a.m_sortKey > b.m_sortKey;
}

bool GfMenuMsgList::fn_710037A10C(const MsgID& a, const MsgID& b) {
    if (a.m_sortKey == b.m_sortKey) {
        return a.m_id < b.m_id;
    }
    return a.m_sortKey < b.m_sortKey;
}

unsigned int GfMenuMsgList::fn_710037A244(unsigned int id) {
    for (unsigned int i = 0; i < getSize(); i++) {
        if (getContents(i).m_id == id) {
            return i;
        }
    }
    return -1;
}

}  // namespace gf
