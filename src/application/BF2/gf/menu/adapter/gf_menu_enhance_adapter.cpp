#include "gf/GfMenuEnhanceAdapter.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfDataDriverArts.h"

namespace gf {

// 1.0.0's adapter (names from its symbols): 3.0.1's linker dropped all of it but getEnhanceCaption as unused,
// leaving its file string (the allocations' __FILE__) in this file's .rodata. 1.0.0's ItemConverter,
// ItemListConverter, ReferenceItemConverter and their createFrom* are not written back: they read ItemProperty
// fields at 1.0.0's offsets, which 3.0.1's layout does not keep.

// per type: the update_* the adapter drives, and the plugin create makes (a text plugin)
static GfMenuEnhanceAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuEnhanceAdapter::update_Caption, {2, 0, 0}},
};

GfMenuEnhanceAdapter::GfMenuEnhanceAdapter(ui::UIObjectPlugin* plugin, bool changed)
    : GfMenuAdapter(plugin, false, changed), m_update(), m_converter(nullptr), m_enhance(0), pad_5C(0) {}

GfMenuEnhanceAdapter::~GfMenuEnhanceAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuEnhanceAdapter* GfMenuEnhanceAdapter::create(unsigned int handle, unsigned int type, unsigned int enhance,
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
#line 211
    GfMenuEnhanceAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuEnhanceAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_enhance = enhance;
    plugin->release();
    return adapter;
}

bool GfMenuEnhanceAdapter::update_Caption(unsigned int enhance) {
    ui::UIStr text;
    if (getEnhanceCaption(enhance, text)) {
        setText(text);
        return true;
    }
    return false;
}

GfMenuEnhanceAdapter* GfMenuEnhanceAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                               IConverter* converter, bool changed) {
    GfMenuEnhanceAdapter* adapter = create(handle, type, converter->getEnhanceID(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuEnhanceAdapter* GfMenuEnhanceAdapter::createFromArts(unsigned int handle, unsigned int type,
                                                           unsigned int arts, unsigned int level, bool changed) {
#line 254
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ArtsConverter(arts, level);
    return createFromCoverter(handle, type, converter, changed);
}

bool GfMenuEnhanceAdapter::getEnhanceCaption(unsigned int enhance, ui::UIStr& text) {
    unsigned char* message = GfDataBdat::getFP(0x19B);
    unsigned char* bdat = GfDataBdat::getFP(0x2C);
    if (!GfMenuBdat::isValidBdatID(bdat, enhance)) {
        return false;
    }
    unsigned int caption = (unsigned short)Bdat::getVal(bdat, "Caption", enhance);
    // with add-on menu layer 3 usable, the table's Caption2 (when it has one and it is not 0) replaces Caption
    if (GfMenuObjUtil::isValidExpansion(3) && Bdat::getMember(bdat, "Caption2") != nullptr) {
        unsigned short caption2 = (unsigned short)Bdat::getVal(bdat, "Caption2", enhance);
        if (caption2 != 0) {
            caption = caption2;
        }
    }
    if (!GfMenuBdat::isValidBdatID(message, caption)) {
        return false;
    }
    text.copy(ui::UIStr(message, caption));
    text.m_ownerId = enhance;
    return true;
}

void GfMenuEnhanceAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int enhance = m_converter->getEnhanceID();
        if (m_enhance != enhance) {
            m_enhance = enhance;
            setChange();
        }
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        if (m_enhance != 0) {
            setDisp(m_update(m_enhance));
        } else {
            setDisp(false);
        }
        m_flags &= ~1;
    }
}

unsigned int GfMenuEnhanceAdapter::ArtsConverter::getEnhanceID() {
    return GfDataDriverArts::getEnhance(m_arts, m_level);
}

}  // namespace gf
