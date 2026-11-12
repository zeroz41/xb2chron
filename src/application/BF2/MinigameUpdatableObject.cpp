#include "gf/FileStaticVec3.h"
#include "classes/minigame/tora/minigame.h"
#include "classes/minigame/tora/MinigameUpdatableObject.h"
#include "classes/fw/CommonResource.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundResource.h"
#include "classes/fw/UpdatableObjectFactory.h"
#include "classes/fw/UpdatableObjectManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/gf/SCOM_ADD_ETHER.h"
#include "classes/gf/SCOM_ADD_ITEM.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/ml/Scn.h"
#include "classes/ui/UIObjectAcc.h"
#include "layer/LayerAccManager.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerBase.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "mtl/MemManager.h"
#include <new>
#include <string.h>

namespace minigame {
namespace tora {

minigame::~minigame() {}

MinigameUpdatableObject::~MinigameUpdatableObject() {
    if (m_screen != nullptr) {
        delete m_screen;
        m_screen = nullptr;
    }
    if (m_layer != nullptr) {
        ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
        acc.resetModelTexture(0);
        acc.resetModelTexture(1);
        if (m_layer != nullptr) {
            m_layer->release();
        }
        m_layer = nullptr;
    }
    if (m_sound != nullptr) {
        m_sound->release();
        m_sound = nullptr;
    }
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
    m_minigame->finalize();
    if (m_minigame != nullptr) {
        delete m_minigame;
        m_minigame = nullptr;
    }
    mm::mtl::PtrSingleton<gf::GfFieldBgm>::get()->stopBgmForDebug(false);
}

void MinigameUpdatableObject::myinit(ui::UIObjectAcc* acc) {
    mm::mtl::PtrSingleton<gf::GfFieldBgm>::get()->stopBgmForDebug(true);
    mm::mtl::PtrSingleton<fw::SoundManager>::get()->stopBgmAll();
    m_minigame = new (gf::getAllocator(gf::ALLOCATOR(0))->getMemHandle(), nullptr, 0, 4, false) minigame();
    m_minigame->initialize();
    m_resource = fw::CommonResource::request(gf::getAllocator(gf::ALLOCATOR(10)), "minigame/tora.bin", 10, false);
    {
        fw::SoundResource::SetupInfo info;
        info.pad_8 = 0x80;
        info.pad_0 = 5;
        info.pad_4 = 0;
        m_sound = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), "sound/se/minigame.xsp", info,
                                             static_cast<fw::LOAD_PRIO>(10));
    }
    m_screen = acc;
    if (acc != nullptr && acc->m_object != nullptr) {
        acc->setDisp(true);
        m_screen->setTexFilterNearest();
    }
    layer::LayerAccManager manager;
    m_layer = manager.createMemObj(320, 240, static_cast<layer::LayerMemType>(1));
    layer::LayerAccMemObj memObj(m_layer);
    memObj.setRender(false);
    grlib::CGLibTextureBuffer* texture = memObj.getTexture();
    ml::ScnRenderDrSysParmAcc parm(mm::mtl::PtrSingleton<ml::Scn>::get()->m_renderDrSys, 0);
    parm.setModelTexture(ml::ScnRenderDrMdlTexture{texture, 0, true});
    parm.setModelTexture(ml::ScnRenderDrMdlTexture{texture, 1, false});
    memset(memObj.getMemBufer(), 0, memObj.getMemWidth() * memObj.getMemHeight() * 3);
    memObj.updateMemBufer();
}

void MinigameUpdatableObject::update(fw::UpdateInfo const&) {
    if (m_resource != nullptr && m_resource->valid() && m_minigame != nullptr && !(m_minigame->m_phase > 10)) {
        if (m_screen != nullptr && m_screen->m_object != nullptr) {
            short width;
            short height;
            m_screen->getSize(false, width, height);
            width *= 3;
            unsigned char* buffer = static_cast<unsigned char*>(m_screen->getOnMemoryBuffer());
            m_minigame->update(buffer, width, height, m_resource->getAssetData(), m_sound);
            m_screen->swapOnMemoryBuffer();
        } else if (m_layer != nullptr) {
            layer::LayerAccMemObj memObj(m_layer);
            unsigned char* buffer = static_cast<unsigned char*>(memObj.getMemBufer());
            int width = memObj.getMemWidth();
            int height = memObj.getMemHeight();
            m_minigame->update(buffer, width * 3, height, m_resource->getAssetData(), m_sound);
            memObj.updateMemBufer();
        }
        if (m_minigame->m_phase > 10) {
            minigame::_sResult result;
            m_minigame->getResult(&result);
            gf::SCOM_ACHIEV_INC::create(0x44, result.m_score, 0);
            int count = 0;
            for (int i = 0; result.m_items[i].m_num != 0; ++i) {
                switch (result.m_items[i].m_id) {
                case 0xFFFF:
                    gf::SCOM_ADD_ETHER::create(result.m_items[i].m_num);
                    break;
                case 0xFFFE:
                    switch (static_cast<unsigned char>(result.m_items[i].m_num)) {
                    case 3:
                        gf::SCOM_ACHIEV_INC::createTiger(0x4C);
                        break;
                    case 4:
                        gf::SCOM_ACHIEV_INC::createTiger(0x4D);
                        break;
                    }
                    break;
                default:
                    ++count;
                    gf::SCOM_ADD_ITEM::create(result.m_items[i].m_id, result.m_items[i].m_num);
                    break;
                }
            }
            if (count > 0) {
                m_context = gf::GfMenuCallContext::create();
                m_results = static_cast<minigame::ResultItem*>(
                    gf::getAllocator(gf::ALLOCATOR(0))->allocate((count + 1) * sizeof(minigame::ResultItem), 0x40));
                m_results[0].m_id = 1;
                m_results[0].m_num = count + 1;
                int index = 1;
                for (minigame::ResultItem* item = result.m_items; item->m_num != 0; ++item) {
                    if (item->m_id < 0xFFFE) {
                        m_results[index].m_id = item->m_id;
                        m_results[index].m_num = item->m_num;
                        ++index;
                    }
                }
                disp_result();
            }
        }
    } else {
        if (m_screen != nullptr && m_screen->m_object != nullptr) {
            short width;
            short height;
            m_screen->getSize(false, width, height);
            memset(m_screen->getOnMemoryBuffer(), 0, width * height * 3);
            m_screen->swapOnMemoryBuffer();
        } else if (m_layer != nullptr) {
            layer::LayerAccMemObj memObj(m_layer);
            memset(memObj.getMemBufer(), 0, memObj.getMemWidth() * memObj.getMemHeight() * 3);
            memObj.updateMemBufer();
        }
        if (m_minigame != nullptr && m_minigame->m_phase > 10) {
            if (m_context == nullptr) {
                gf::getAllocator(gf::ALLOCATOR(0))->deallocate(m_results);
                m_results = nullptr;
                setTerminate();
            } else if (m_context->isTerm() && !disp_result() && m_context != nullptr) {
                m_context->release();
                m_context = nullptr;
            }
        }
    }
}

mm::mtl::RTTI MinigameUpdatableObject::m_rtti("MinigameUpdatableObject", &::fw::UpdatableObject::m_rtti, nullptr);

namespace factory {
MinigameUpdatableObject* create(ui::UIObjectAcc* acc) {
    fw::UpdatableObjectFactory* factory = mm::mtl::PtrSingleton<fw::UpdatableObjectFactory>::get();
    void* memory = factory->m_allocator->allocate(sizeof(MinigameUpdatableObject), 8);
    MinigameUpdatableObject* object =
        new (memory) MinigameUpdatableObject(0xF, factory->m_manager->registPointer(0xF, memory));
    factory->m_manager->registObject(0xF, object);
    object->initialize();
    if (object != nullptr) {
        object->myinit(acc);
    }
    return object;
}
}  // namespace factory

}  // namespace tora
}  // namespace minigame
