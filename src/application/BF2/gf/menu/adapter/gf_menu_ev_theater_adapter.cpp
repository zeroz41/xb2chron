#include "classes/gf/GfMenuEvTherterAdapter.h"
#include "classes/gf/GfMenuEvTherterAdapter/IConverter.h"
#include "classes/gf/GfMenuEvTherterAdapter/ListConverter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, image index)
static GfMenuEvTherterAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuEvTherterAdapter::update_Title, {2, 0, 0}},
    {&GfMenuEvTherterAdapter::update_Thumb, {1, 0, 0}},
};

GfMenuEvTherterAdapter::~GfMenuEvTherterAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuEvTherterAdapter* GfMenuEvTherterAdapter::create(unsigned int handle, unsigned int type,
                                                       unsigned int theaterId, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 150
    GfMenuEvTherterAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuEvTherterAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_theaterId = theaterId;
    plugin->release();
    return adapter;
}

bool GfMenuEvTherterAdapter::update_Title(unsigned int theaterId) {
    unsigned char* fp = GfDataBdat::getFP(GfMenuObjUtil::fn_710048FD30(3) ? 0xFE : 0xFD);
    if (fp == nullptr) {
        return false;
    }
    unsigned short title = (unsigned short)Bdat::getVal(fp, "title", theaterId);
    ui::UIStr text(GfDataBdat::getFP(300), title);
    setText(text);
    return true;
}

bool GfMenuEvTherterAdapter::update_Thumb(unsigned int theaterId) {
    unsigned char* fp = GfDataBdat::getFP(GfMenuObjUtil::fn_710048FD30(3) ? 0xFE : 0xFD);
    if (fp == nullptr) {
        return false;
    }
    unsigned short thumbnail = (unsigned short)Bdat::getVal(fp, "thumbnail", theaterId);
    if (thumbnail == 0) {
        return false;
    }
    setNumber(thumbnail);
    return true;
}

GfMenuEvTherterAdapter* GfMenuEvTherterAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                                   IConverter* converter, bool changed) {
    GfMenuEvTherterAdapter* adapter = create(handle, type, converter->getEvTheaterID(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuEvTherterAdapter* GfMenuEvTherterAdapter::createFromList(unsigned int handle, unsigned int type,
                                                               GfMenuIDList* list, int index, bool changed) {
#line 166
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuEvTherterAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int theaterId = m_converter->getEvTheaterID();
        if (m_theaterId != theaterId) {
            m_theaterId = theaterId;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_theaterId != 0) {
            setDisp(m_update(m_theaterId));
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

}  // namespace gf
