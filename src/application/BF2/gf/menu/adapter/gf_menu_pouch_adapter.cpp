#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuPouchAdapter.h"
#include "classes/gf/GfMenuPouchAdapter/IConverter.h"
#include "classes/gf/GfMenuPouchAdapter/ReferenceDriverConverter.h"
#include "gf/GfPouchUtil.h"
#include "gf/SDataPouch.h"
#include "ui/uiDateTime.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (a time)
static GfMenuPouchAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuPouchAdapter::update_PouchRemainTime, {7, 3, 0}},
};

GfMenuPouchAdapter::~GfMenuPouchAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuPouchAdapter* GfMenuPouchAdapter::create(unsigned int handle, unsigned int type, unsigned short pouch,
                                               unsigned int driver, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 183
    GfMenuPouchAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuPouchAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_pouch = pouch;
    adapter->m_driver = driver;
    plugin->release();
    return adapter;
}

bool GfMenuPouchAdapter::update_PouchRemainTime() {
    const SDataPouch& data = GfPouchUtil::getPouch(m_driver, m_pouch);
    if (data.itemId == 0) {
        return false;
    }
    ui::uiDateTime time = {};
    unsigned int sec = m_remainTime;
    time.hour = sec / 3600;
    time.minute = (sec - time.hour * 3600) / 60;
    time.sec = sec % 60;
    setTime(time);
    return true;
}

GfMenuPouchAdapter* GfMenuPouchAdapter::createFromReferenceDriver(unsigned int handle, unsigned int type,
                                                                  unsigned int pouch, unsigned int reference,
                                                                  bool changed) {
#line 207
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceDriverConverter(pouch, reference);
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuPouchAdapter* GfMenuPouchAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                           IConverter* converter, bool changed) {
    GfMenuPouchAdapter* adapter =
        create(handle, type, converter->getPouchIndex(), converter->getDriverId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

void GfMenuPouchAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int pouch = m_converter->getPouchIndex();
        if (m_pouch != pouch) {
            m_pouch = pouch;
            setChange();
        }
        unsigned int driver = m_converter->getDriverId();
        if (m_driver != driver) {
            m_driver = driver;
            setChange();
        }
    }
    const SDataPouch& data = GfPouchUtil::getPouch(m_driver, m_pouch);
    if (m_remainTime != data.remainTime) {
        m_remainTime = data.remainTime;
        setChange();
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update());
        m_flags &= ~1;
    }
}

}  // namespace gf
