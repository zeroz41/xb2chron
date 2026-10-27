#include "gf/FileStaticVec3.h"
#include "classes/gf/TUnk_B63A48.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/TUnk_B62AA0.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB8D0)
TUnk_B63A48::OpenParam g_npcTelopParam;
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB928)
bool g_npcTelopOpen;

TUnk_B63A48::TUnk_B63A48(unsigned int handle)
    : GfMenuObject(handle), m_selectList(nullptr), m_idList(nullptr), m_seq0(this), m_seq1(this) {
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_selectList = ui::UISelectObjList::create(create);
    m_idList = GfMenuIDList::create();
    if (m_idList != nullptr) {
        ui::UIListInfoBase::SetupParam param;
        param.m_pageRowSize = 3;
        m_idList->setup(getAllocator(ALLOCATOR(0)), param);
        m_idList->clear();
    }
}

TUnk_B63A48::~TUnk_B63A48() {
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    if (m_selectList != nullptr) {
        m_selectList->release();
        m_selectList = nullptr;
    }
}

void TUnk_B63A48::fn_7100447644(GfMenuCallContext* context, const OpenParam& param) {
    if (GfMenuObjUtil::fn_710048FD30(3) && GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8C));
        if (acc.m_object != nullptr) {
            g_npcTelopParam = param;
            ui::UIObjectAcc dummy(acc.searchSibiling("LAY_dummy"));
            GfMenuObject::sendOpenEvent(dummy.m_handle, 0, 0.0f);
            GfMenuObject::startCallContext(context, 0x8C, dummy.m_handle);
        }
    }
}

TUnk_B63A48::OpenParam* TUnk_B63A48::fn_71004477E0() {
    return &g_npcTelopParam;
}

bool TUnk_B63A48::fn_71004477EC() {
    return g_npcTelopOpen;
}

void TUnk_B63A48::initialize() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        if (acc.m_object != nullptr) {
            GfMenuObject::attachExternalCall(0x8C, acc.m_handle);
#line 154
            TUnk_B63A90* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B63A90(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            GfMenuObject::initialize();
            GfMenuAdapterManager::beginAddAfter();
            unsigned int count = acc.countChild("LAY_char@%02d", 1);
            {
                mm::mtl::FixStr<32> name;
                for (unsigned int i = 0; i < count; i++) {
                    name.format("IMG_char_face@%02d", i + 1);
                    GfMenuCharDataAdapter::fn_710033A940(acc.searchChild(name.m_str), 0x6C, m_idList, i, false);
                }
            }
            GfMenuAdapterManager::endAddAfter();
            ui::UIObjectAcc dummy(m_handle, "LAY_dummy");
            if (dummy.m_object != nullptr) {
#line 179
                TUnk_B63AB8* dummyListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B63AB8(this);
                dummyListener->m_RefCount = 1;
                ui::UIEventManager::get()->registObjectListener(dummy.m_handle, dummyListener);
                if (dummyListener != nullptr) {
                    dummyListener->release();
                }
            }
        }
    }
}

void TUnk_B63A48::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B63A48::update() {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return;
    }
    m_seq0.update();
    m_seq1.update();
    GfMenuObject::update();
}

bool TUnk_B63A48::fn_7100447B88() {
    if (m_idList != nullptr) {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < m_idList->getSize(); i++) {
            name.format("IMG_char_face@%02d", i + 1);
            ui::UIObjectAcc face(acc.m_handle, name.m_str);
            if (face.isStreaming()) {
                return false;
            }
        }
        if (++m_waitCount > 60) {
            return true;
        }
    }
    return true;
}

bool TUnk_B63A48::fn_7100447C70() {
    return !GfMenuManager::isOpenFullScreen();
}

bool TUnk_B63A48::fn_7100447C8C() {
    ui::UIObjectAcc dummy(m_handle, "LAY_dummy");
    GfMenuObject::sendCloseEvent(dummy.m_handle, 0, 0.0f);
    return true;
}

bool TUnk_B63A48::fn_7100447CD4() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    float delay = 0.0f;
    for (unsigned int i = 0; i < m_idList->getSize(); i++) {
        ui::EventData event;
        event.m_type = 0x100;
        event.m_param0 = i;
        if (i != 0) {
            delay = i * 0.1f;
        }
        GfMenuObject::sendEvent(acc.m_handle, event, delay);
    }
    return true;
}

void TUnk_B63A48::TUnk_B63AB8::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        break;
    case 0x21:
        if (m_state == 0) {
            TUnk_B62AA0::fn_710041D238();
            GfMenuManager::fn_710035DD6C();
            GfMenuManager::openFullScreen(1, true, true);
            m_owner->m_seq1.addJob(&TUnk_B63A48::fn_7100447C70);
            m_owner->m_seq1.addJob(&TUnk_B63A48::fn_7100447C8C);
            m_state = 1;
            g_npcTelopOpen = true;
        }
        break;
    case 0x22:
        if (m_state == 1) {
            GfMenuObject::termCallContext(acc.m_handle);
            m_state = 0;
            g_npcTelopOpen = false;
        }
        break;
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
