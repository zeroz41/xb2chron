#include "classes/gf/GfMenuAdapter.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuHanaPartsAdapter.h"
#include "classes/gf/GfMenuHanaPartsAdapter/IConverter.h"
#include "classes/gf/GfMenuHanaPartsAdapter/ListConverter.h"
#include "classes/gf/GfMenuHanaPartsAdapter/ReferenceNumberConverter.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfGameUtilHana.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, image index, number)
static GfMenuHanaPartsAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuHanaPartsAdapter::update_partsText, {2, 0, 0}},
    {&GfMenuHanaPartsAdapter::update_partsIcon, {1, 0, 0}},
    {&GfMenuHanaPartsAdapter::update_needEther, {0, 0, 999999999}},
};

GfMenuHanaPartsAdapter::~GfMenuHanaPartsAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuHanaPartsAdapter* GfMenuHanaPartsAdapter::create(unsigned int handle, unsigned int type, unsigned int partsId,
                                                       bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 148
    GfMenuHanaPartsAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuHanaPartsAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_partsId = partsId;
    plugin->release();
    return adapter;
}

bool GfMenuHanaPartsAdapter::update_partsText() {
    if (m_partsId == 0) {
        return false;
    }
    unsigned char* message = GfDataBdat::getFP(0xF5);
    unsigned short name = (unsigned short)Bdat::getVal(GfDataBdat::getFP(0x17C), "name", m_partsId);
    if (name == 0) {
        return false;
    }
    ui::UIStr text(message, name);
    setText(text);
    return true;
}

bool GfMenuHanaPartsAdapter::update_partsIcon() {
    if (m_partsId == 0) {
        return false;
    }
    unsigned short icon = (unsigned short)Bdat::getVal(GfDataBdat::getFP(0x17C), "icon", m_partsId);
    if (icon == 0) {
        return false;
    }
    setNumber(icon);
    return true;
}

// update_needEther: not written yet (the original reloads the blade and part for its switch)

GfMenuHanaPartsAdapter* GfMenuHanaPartsAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                                   IConverter* converter, bool changed) {
    GfMenuHanaPartsAdapter* adapter = create(handle, type, converter->getPartsId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuHanaPartsAdapter* GfMenuHanaPartsAdapter::createFromList(unsigned int handle, unsigned int type,
                                                               GfMenuIDList* list, int index, bool changed) {
#line 164
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuHanaPartsAdapter* GfMenuHanaPartsAdapter::createFromReference(
    unsigned int handle, unsigned int type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference, bool changed) {
#line 172
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceNumberConverter(reference);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuHanaPartsAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int partsId = m_converter->getPartsId();
        if (m_partsId != partsId) {
            m_partsId = partsId;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update());
        m_flags &= ~1;
    }
}

GfMenuHanaPartsAdapter::ListConverter::~ListConverter() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

unsigned int GfMenuHanaPartsAdapter::ListConverter::getPartsId() {
    if (m_index == -1) {
        return m_list->getContents(m_list->getIndex(false)).m_id;
    }
    if (m_index >= m_list->getSize()) {
        return 0;
    }
    return m_list->getContents(m_list->getPageIndex(m_index)).m_id;
}

GfMenuHanaPartsAdapter::ReferenceNumberConverter::~ReferenceNumberConverter() {
    m_reference = nullptr;
}

unsigned int GfMenuHanaPartsAdapter::ReferenceNumberConverter::getPartsId() {
    return m_reference->m_value;
}

}  // namespace gf
