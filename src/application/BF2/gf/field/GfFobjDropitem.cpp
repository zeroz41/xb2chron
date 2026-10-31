#include "gf/GfFobjSeManager.h"
#include "gf/GfFobjGottenEffectManager.h"
#include "gf/GfDropitemEmitter.h"
#include "classes/gf/GfDropitemParams.h"
#include "classes/gf/GfFobjDropitem.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfFobjManager.h"
#include "classes/gf/GfInitParamFobj.h"
#include "classes/gf/GfObjSetupFieldObj.h"
#include "gf/GfObjFactory.h"
#include "gf/GfObjInfo.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObj.h"
#include "gf/GfItemUtil.h"
#include "gf/GfPlayFactory.h"

namespace gf {
namespace {
// a field object's setup when its info holds one of field objects' kind (9) (the same test as gf_obj_factory's
// getSetupOf; inline, the name is not the original's)
inline GfObjSetupFieldObj* getFieldObjSetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr || info->m_setup == nullptr) {
        return nullptr;
    }
    GfObjSetup* setup = info->m_setup;
    GfObj* obj = info->m_obj;
    if (setup->m_type == static_cast<int>(obj->m_type) && static_cast<int>(obj->m_type) == 9) {
        return setup->getRTTI()->isKindOf(&GfObjSetupFieldObj::m_rtti) ? static_cast<GfObjSetupFieldObj*>(setup)
                                                                        : nullptr;
    }
    return nullptr;
}
// a float member's value of a row (getValCheck's type 8 gives its bits; the name is not the original's)
inline float getValFloat(unsigned char* fp, int member, int id) {
    unsigned int bits = Bdat::getValCheck(fp, member, id, 8);
    return *reinterpret_cast<float*>(&bits);
}
}  // namespace

GfFobjSeManager::GfFobjSeManager(const CreateInfo* info) : m_pack(nullptr) {
    if (info != nullptr) {
        create(*info);
    }
}

void GfFobjSeManager::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    const char* name = GfFieldSound::fn_710027C7D4();
    m_pack = fw::SoundManager::sys()->findPack(name, nullptr);
    if (m_pack == nullptr) {
        dispose();
        return;
    }
    m_seInfos.setAllocator(getAllocator(ALLOCATOR(0)));
    m_seInfos.reserve(info.m_maxSe);
    m_seTimes.setAllocator(getAllocator(ALLOCATOR(0)));
}

void GfFobjSeManager::dispose() {
    if (m_seInfos.size() != 0) {
        if (fw::SoundManager::sys() != nullptr) {
            for (SeInfo& se : m_seInfos) {
                fw::SoundManager::sys()->stopSe(se.m_soundId, 0.5f);
            }
        }
        m_seInfos.destroy();
    }
    m_info = CreateInfo();
}

void GfFobjSeManager::fn_7100282EA8() {
    const char* name = GfFieldSound::fn_710027C7D4();
    m_pack = fw::SoundManager::sys()->findPack(name, nullptr);
}

void GfFobjSeManager::update(float deltaTime) {
    if (m_info.m_maxSe == 0) {
        return;
    }
    for (mm::mtl::Vector<SeInfo>::iterator it = m_seInfos.begin(); it != m_seInfos.end(); ++it) {
        if (!fw::SoundManager::sys()->isPlaying(it->m_soundId)) {
            it = m_seInfos.erase(it);
            --it;
        }
    }
    typedef mm::mtl::Map<unsigned short, float>::tree_type Tree;
    Tree& tree = m_seTimes.m_tree;
    Tree::node* n = nullptr;
    if (tree.m_root != &Tree::m_sentinel) {
        n = tree.m_root;
        while (n->left != &Tree::m_sentinel) {
            n = n->left;
        }
    }
    for (; n != nullptr; n = tree.next(n)) {
        n->value.second += deltaTime;
    }
}

GfFobjGottenEffectManager::GfFobjGottenEffectManager(const CreateInfo* info) {
    if (info != nullptr) {
        create(*info);
    }
}

void GfFobjGottenEffectManager::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    m_effectRes[0] = fw::EffectManager::sys()->search("cmn_200_030", nullptr);
    m_effectRes[1] = fw::EffectManager::sys()->search("cmn_200_031", nullptr);
    m_effectRes[2] = fw::EffectManager::sys()->search("cmn_200_032", nullptr);
    m_effects.setAllocator(getAllocator(ALLOCATOR(0)));
    m_effects.reserve(info.m_capacity);
}

void GfFobjGottenEffectManager::dispose() {
    if (m_effects.size() != 0) {
        for (EffectInfo& effect : m_effects) {
            fw::EffectManager::sys()->kill(effect.m_handle);
        }
        m_effects.destroy();
    }
    m_info = CreateInfo();
}

GfDropitemParams::~GfDropitemParams() {
    m_params.destroy();
}

GfDropitemEmitter::GfDropitemEmitter(const CreateInfo* info) : m_isEmitted(false), m_timer(0.0f), m_endTime(0.0f) {
    if (info != nullptr) {
        create(*info);
    }
}

void GfDropitemEmitter::create(const CreateInfo& info) {
    dispose();
    m_info = info;
    m_seq = &GfDropitemEmitter::seqWaitBeginDrop;
}

void GfDropitemEmitter::dispose() {
    m_timer = 0.0f;
    m_endTime = 0.0f;
    m_isEmitted = false;
    // the original keeps the defaults in a stack copy and copies them with memcpy: the self-copy test (folded
    // later) keeps the copy from being split into direct stores, as in the original
    const CreateInfo info;
    if (&m_info != &info) {
        m_info = info;
    }
}

void GfDropitemEmitter::update(float dt) {
    if (m_info.m_items != nullptr && m_info.m_itemCount > 0) {
        m_timer += dt;
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
}

void GfDropitemEmitter::seqWaitEndDrop(float dt) {
    if (m_timer < m_endTime) {
        return;
    }
    m_isEmitted = true;
    m_seq = nullptr;
}

GfFobjDropitem::~GfFobjDropitem() {}

void GfFobjDropitem::destroy() {
    if (m_effect != 0) {
        fw::EffectManager::sys()->dead(m_effect);
        m_effect = 0;
    }
    if (m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfObjAcc acc(m_handle);
        if (acc.m_obj != nullptr) {
            acc.setUserData(GfObjUserData(2), 0);
        }
    }
}

void GfFobjDropitem::setEventDisp(bool disp) {
    GfObjAcc acc(m_handle);
    if (acc.m_obj != nullptr) {
        acc.setDisp(OBJDISP(1), disp);
    }
    if (m_effect != 0) {
        fw::EffectManager::sys()->setDisp(m_effect, disp);
    }
}

bool GfFobjDropitem::applyGetItem(GF_OBJ_HANDLE* item, GF_OBJ_HANDLE* getter) {
    GfObjAcc acc(item);
    if (acc.m_obj == nullptr) {
        return false;
    }
    GfFobjDropitem* dropitem = static_cast<GfFobjDropitem*>(acc.getUserData(GfObjUserData(2)));
    if (dropitem == nullptr) {
        return false;
    }
    if (GfObjUtil::getObj(getter) == nullptr) {
        return false;
    }
    dropitem->applyGetItem(getter);
    return true;
}

GF_OBJ_HANDLE* GfFobjDropitem::emitDropitem(unsigned char paramId, int itemId, float value) {
    unsigned char* fp = GfFobjManager::sys() != nullptr ? GfFobjManager::sys()->m_dropitemListFP : nullptr;
    GfFobjManager::getDropitemParams();
    const unsigned int bdats[] = {0x93, 0x94, 0x95, 0x97, 0x98, 0x9B, 0x9C, 0xA0, 0xA1, 0xA2, 0x9A, 0x9D};
    unsigned int itemBdat = 0x1E1;
    const unsigned int* bdatIt = bdats;
    for (unsigned long i = 0; i < sizeof(bdats) / sizeof(bdats[0]); i++) {
        unsigned int bdat = *bdatIt++;
        unsigned char* bdatFp = GfDataBdat::getFP(bdat);
        if (bdatFp == nullptr) {
            continue;
        }
        int top = Bdat::getIdTop(bdatFp);
        int end = top + Bdat::getIdCount(bdatFp);
        if (top <= itemId && itemId < end) {
            itemBdat = bdat;
            if (bdat == 0x9C || bdat == 0x9D) {
                if (GfItemUtil::isEnableAddItemBox(itemId, 1) && GfItemUtil::addItemBox(itemId, 1)) {
                    GfPlayFactory::createMenuPrecious(itemId, true);
                }
                return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
            }
            break;
        }
    }
    int resId = getResBdatIdFromItemId(itemId);
    GfInitParamFobj param;
    param.m_isDropItem = true;
    param.pad_90 = 2;
    param.m_objId = resId;
    param.pad_18 = &fp;
    param.pad_94 = paramId;
    GF_OBJ_HANDLE* handle = GfObjFactory::createFieldObj(param);
    GfObjSetupFieldObj* setup = getFieldObjSetup(handle);
    setup->m_itemBdat = itemBdat;
    setup->m_itemId = itemId;
    setup->m_fobjId = resId;
    setup->pad_8c = value;
    return handle;
}

GF_OBJ_HANDLE* GfFobjDropitem::fn_7100287E30(unsigned char paramId, unsigned int amount) {
    unsigned char* fp = GfFobjManager::sys() != nullptr ? GfFobjManager::sys()->m_dropitemListFP : nullptr;
    GfFobjManager::getDropitemParams();
    GfInitParamFobj param;
    param.m_isDropItem = true;
    param.pad_90 = 2;
    param.m_objId = 30;
    param.pad_18 = &fp;
    param.pad_94 = paramId;
    GF_OBJ_HANDLE* handle = GfObjFactory::createFieldObj(param);
    GfObjSetupFieldObj* setup = getFieldObjSetup(handle);
    setup->m_amount = amount;
    setup->m_fobjId = param.m_objId;
    return handle;
}

GF_OBJ_HANDLE* GfFobjDropitem::emitDropgold(unsigned char paramId, unsigned int gold) {
    unsigned char* fp = GfFobjManager::sys() != nullptr ? GfFobjManager::sys()->m_dropitemListFP : nullptr;
    GfFobjManager::getDropitemParams();
    GfInitParamFobj param;
    param.m_isDropItem = true;
    param.pad_90 = 2;
    unsigned char* settings = GfDataBdat::getFP(0x7B);
    unsigned int limit10 = getValFloat(settings, 0, 8);
    unsigned int limit11 = getValFloat(settings, 0, 9);
    unsigned int limit12 = getValFloat(settings, 0, 10);
    unsigned int limit13 = getValFloat(settings, 0, 11);
    if (gold < limit10) {
        param.m_objId = 10;
    } else if (gold < limit11) {
        param.m_objId = 11;
    } else if (gold < limit12) {
        param.m_objId = 12;
    } else if (gold < limit13) {
        param.m_objId = 13;
    } else {
        param.m_objId = 14;
    }
    param.pad_18 = &fp;
    param.pad_94 = paramId;
    GF_OBJ_HANDLE* handle = GfObjFactory::createFieldObj(param);
    GfObjSetupFieldObj* setup = getFieldObjSetup(handle);
    setup->m_gold = gold;
    setup->m_fobjId = param.m_objId;
    return handle;
}

int GfFobjDropitem::getResBdatIdFromItemId(int itemId) {
    const unsigned int bdats[] = {0x93, 0x94, 0x95, 0x97, 0x98, 0x9B, 0x9C, 0xA0, 0xA1, 0xA2, 0x9A, 0x9D};
    int resId = -1;
    for (unsigned long i = 0; i < sizeof(bdats) / sizeof(bdats[0]); i++) {
        unsigned int bdat = bdats[i];
        unsigned char* fp = GfDataBdat::getFP(bdat);
        if (fp == nullptr) {
            continue;
        }
        int top = Bdat::getIdTop(fp);
        int end = top + Bdat::getIdCount(fp);
        if (top <= itemId && itemId < end) {
            fp = GfDataBdat::getFP(bdat);
            resId = -1;
            if (fp != nullptr) {
                switch (bdat) {
                case 0x93:
                    resId = Bdat::getValCheckU8(fp, "Category", itemId) - 3;
                    break;
                case 0x94:
                    resId = 9;
                    break;
                case 0x95:
                    resId = 15;
                    break;
                case 0x97:
                    resId = 18;
                    break;
                case 0x98:
                case 0x9A:
                    resId = 19;
                    break;
                case 0x9B:
                    resId = Bdat::getValCheckU8(fp, "DropRsc", itemId);
                    break;
                case 0x9C:
                case 0x9D:
                    resId = 23;
                    break;
                case 0xA0:
                    resId = Bdat::getValCheckU8(fp, "Category", itemId) + 24;
                    break;
                case 0xA1:
                    resId = 8;
                    break;
                case 0xA2:
                    resId = 9;
                    break;
                }
            }
            break;
        }
    }
    return resId;
}

}  // namespace gf
