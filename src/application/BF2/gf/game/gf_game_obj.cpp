#include "mm/mtl/FixedList.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfGameObjEnemy.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfGameMount.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjInfo.h"
#include "gf/GfGameUtil.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameSearchObj.h"
#include "classes/gf/GfObjSetupBlade.h"
#include "classes/gf/GfObjSetupWeapon.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/GfPause.h"
#include "classes/gf/GfInfo.h"
#include "fw/UpdateInfo.h"
#include "gf/GfDataEnemy.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/gf/SCOM_OBJ_WARP_POS.h"
#include "gf/GfObjAlpha.h"
#include "gf/GfUtil.h"
#include "mm/Math.h"
#include "gf/SDataEnemy.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfAssetManager.h"
#include <math.h>

namespace gf {

GfGameObj::GfGameObj(const GfSetupParam& param) : m_enemy(nullptr), pad_55c70(false) {
    initialize(param);
    GfObjManager::addListener(this, static_cast<IGfObjListener::OBJEVT>(0));
}

void GfGameObj::initialize(const GfSetupParam& param) {
#line 234
    m_enemy = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameObjEnemy();
    GfGameSearchObj::build(param);
    pad_55c70 = true;
}

GfGameObj::~GfGameObj() {
    GfObjManager::removeListener(this);
}

void GfGameObj::build(const GfSetupParam& param) {
#line 213
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameObj(param);
}

void GfGameObj::destroy() {
    GfGameObj* self = get();
    self->m_msgs.clear();
    GfGameSearchObj::destroy();
    if (self->m_enemy != nullptr) {
        delete self->m_enemy;
        self->m_enemy = nullptr;
    }
    self->pad_55c70 = false;
    delete self;
}
}  // namespace gf

// instantiated for gf::GfGameObj::removeGameObj, gf::GfGameObj::update (not written yet)
template mm::mtl::FixedList<gf::ObjMsg, 256>::iterator mm::mtl::FixedList<gf::ObjMsg, 256>::erase(mm::mtl::FixedList<gf::ObjMsg, 256>::iterator);

namespace gf {

void GfGameObj::calcCameraFade(const ObjList& list, const mm::Vec3& camPos) {
    for (ObjList::const_iterator it = list.begin(); it != list.end(); ++it) {
        GfObjAcc acc(*it);
        if (acc.getObj()->m_execUpdate) {
            mm::Vec3 pos = acc.getWorldTransformNoSync().position;
            float radius = acc.getModelRadius();
            if (radius >= 50.0f) {
                acc.setCalcCameraAlpha();
                continue;
            }
            pos.y += radius;
            mm::Vec3 diff = pos - camPos;
            if (diff.x * diff.x + diff.y * diff.y + diff.z * diff.z < 400.0f || acc.getAlphaCamera() < 1.0f ||
                acc.getAlpha() != acc.getModelAlpha()) {
                acc.setCalcCameraAlpha();
            }
        }
    }
}

void GfGameObj::postUpdate(const fw::UpdateInfo& info) {
    get()->updateObjectProperty();
}

void GfGameObj::updateObjectProperty() {
    ObjList* list = getListType(3, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    for (ObjList::iterator it = list->begin(); it != list->end(); ++it) {
        GfGameUtil::flushProperty(*it);
    }
    list = getListType(4, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    for (ObjList::iterator it = list->begin(); it != list->end(); ++it) {
        GfGameUtil::flushProperty(*it);
    }
    list = getListType(5, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    for (ObjList::iterator it = list->begin(); it != list->end(); ++it) {
        GfGameUtil::flushProperty(*it);
    }
    list = getListType(0, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    for (ObjList::iterator it = list->begin(); it != list->end(); ++it) {
        GfGameUtil::flushProperty(*it);
    }
}

void GfGameObj::listenerGfObj(IGfObjListener::OBJEVT evt, GF_OBJ_HANDLE* handle, unsigned int) {
    GfGameObj* self = get();
    switch (evt) {
    case 1:
        GfGameEvent::applySetDispObject(handle);
        break;
    case 2:
        self->addInObj(handle, 0.5f);
        break;
    case 3:
        self->removeGameObj(handle);
        break;
    }
}

void GfGameObj::addInObj(GF_OBJ_HANDLE* handle, float fadeTime) {
    GfGameEvent::applySetDispObject(handle);
    GfObjAcc acc(handle);
    float alpha = acc.getAlphaLife();
    m_inList.push_back(INOUT(handle, fadeTime, alpha));
    acc.setFlag(15, true);
    if (acc.getType() == 5) {
        acc.getObj()->setUpdateComponent(true);
    }
}

GfGameObj::ObjList* GfGameObj::getListType(unsigned int kind, GF_OBJ_HANDLE* handle) {
    switch (kind) {
    case 3:
        return &m_listDriver;
    case 4:
        return &m_listBlade;
    case 5:
        if (GfObjUtil::isEnemyBlade(handle)) {
            return &m_listEnemyBlade;
        }
        return &m_listEnemy;
    case 6:
        return &m_listType6;
    case 7:
        return &m_listType7;
    case 8:
        return &m_listType8;
    case 9:
        return &m_listType9;
    case 10:
        return &m_listType10;
    case 0:
    case 14:
        return &m_listType0;
    case 12:
        return &m_listType12;
    case 11:
        return &m_listType11;
    case 13:
        return &m_listType13;
    default:
        return &m_listOther;
    }
}

mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>* GfGameObj::getList(unsigned int kind) {
    return get()->getListType(kind, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
}
}  // namespace gf

// instantiated for gf::GfGameObj::addOutObj, gf::GfGameObj::removeGameObj, gf::GfObjManager::checkLoadingAndCreate (not written yet)
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 1024>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 1024>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 1024>::iterator);

namespace gf {

GfGameObj::ObjList* GfGameObj::getListEnemyBlade() {
    return &get()->m_listEnemyBlade;
}

void GfGameObj::getList(mm::mtl::FixedVector<GF_OBJ_HANDLE*, 1024>& out, unsigned int kind) {
    GfGameObj* self = get();
    if (self == nullptr) {
        return;
    }
    ObjList* list = self->getListType(kind, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    for (ObjList::iterator it = list->begin(); it != list->end(); ++it) {
        out.push_back(*it);
    }
}

void GfGameObj::enableGameObj(GfObjAcc& acc, bool on) {
    acc.setFlag(14, on);
    acc.setCollisionChar(on);
    acc.getObj()->setUpdateComponent(on);
    if (!on) {
        if (acc.isPartyObj() && GfGameParty::getPartyId(acc.getHandle()) != -1 &&
            (acc.getType() == 3 || acc.getType() == 4)) {
            GfGameUtil::resetFormationParam(acc.getHandle());
        }
        m_leaveObjs.push_back(acc.getHandle());
    } else {
        m_enterObjs.push_back(acc.getHandle());
    }
}
}  // namespace gf

// instantiated for gf::GfGameObj::removeGameObj, gf::GfGameObj::updateEnterLeaveObj (not written yet)
template mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::iterator mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::erase(mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::iterator);

namespace gf {

void GfGameObj::flushEvent() {
    for (GF_OBJ_HANDLE** it = m_enterObjs.begin(); it != m_enterObjs.end(); ++it) {
        if (m_enemy != nullptr) {
            m_enemy->enterEnemyObj(*it);
        }
        GfEvent::callGameObjEnter(*it);
    }
    for (GF_OBJ_HANDLE** it = m_leaveObjs.begin(); it != m_leaveObjs.end(); ++it) {
        if (m_enemy != nullptr) {
            m_enemy->leaveEnemyObj(*it);
        }
        GfEvent::callGameObjLeave(*it);
    }
    m_enterObjs.clear();
    m_leaveObjs.clear();
}

namespace _gfgob {
// an enemy's setup when its info holds one of its own kind (5), as DataParamAcc.cpp's _gfdac::getEnemySetup (inline,
// the name is not the original's)
static inline GfObjSetupEnemy* getEnemySetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 5) {
        return mm::mtl::rttiCast<GfObjSetupEnemy>(info->m_setup);
    }
    return nullptr;
}
}  // namespace _gfgob

// a ground point beside an enemy's initial position, at angle (radians, from its initial y rotation) and 3.0 down
// to 0.2 away, written to pos; false when no ground is found (checkEnableGameObj places an entering enemy blade)
static bool fn_71002B5A34(float angle, mm::Vec3& pos, const GfObjSetupEnemy* setup);

void GfGameObj::checkEnableGameObj(INOUT& inout, GfObjAcc& acc) {
    if (inout.pad_14) {
        return;
    }
    inout.pad_14 = true;
    enableGameObj(acc, true);
    if (acc.isCameraFadeAllOK() && GfObjAlpha::isNearCamera(acc)) {
        acc.setAlphaCamera(0.0f);
    }
    setupForLoopEffect(acc);
    if (acc.isEnemyBlade()) {
        GfObjSetupEnemy* setup =
            _gfgob::getEnemySetup(GfMountManager::getHandle(acc.getHandle(), GFATTACH(0), OPTMNT(2)));
        mm::Vec3 pos;
        mm::Vec3 rot = setup->pad_30;
        if (!fn_71002B5A34(2.09439516f, pos, setup) && !fn_71002B5A34(-2.09439516f, pos, setup)) {
            pos = setup->m_initialPos + mm::Vec3(0.1f, 0.01f, 0.1f);
        }
        SCOM_OBJ_WARP_POS::create(acc.getHandle(), pos, rot, false);
    }
    if (acc.getType() == 5) {
        GfGameUtil::refreshEnemyHp(acc.getHandle());
    }
}

void GfGameObj::setupForLoopEffect(GfObjAcc& acc) {
    if (acc.getType() == 5) {
        const char* effect = GfDataEnemy::getLoopEffect(acc.getEnRscId());
        if (effect != nullptr) {
            GfComEffectCaster* caster = acc.getObj()->getComponent<GfComEffectCaster>(7);
            if (caster != nullptr) {
                GfComEffectCaster::EffectSetUp setup;
                setup.m_name = effect;
                setup.m_scale = acc.getModelScale();
                setup.m_caster = caster->m_caster;
                setup.pad_44 = 1;
                caster->effectStart(setup, nullptr);
            }
        }
    }
}

bool GfGameObj::fadeoutGameObj(INOUT& inout, GfObjAcc& acc, const fw::UpdateInfo& info) {
    inout.pad_c += info.m_deltaTime;
    float step;
    if (inout.pad_16) {
        step = 0.0f;
    } else {
        step = inout.m_fadeTime > 0.0f ? -1.0f / inout.m_fadeTime * info.m_deltaTime : 0.0f;
        inout.m_alpha += step;
    }
    if (inout.pad_15 && inout.m_alpha < 1.0f && inout.m_alpha - step >= 1.0f) {
        inout.pad_15 = false;
        setupEffectFadeout(inout, acc, info);
    }
    if (inout.m_alpha <= 0.0f || (inout.pad_16 && acc.m_obj != nullptr && inout.m_fadeTime < inout.pad_c)) {
        inout.m_alpha = 0.0f;
        if (inout.pad_14) {
            inout.pad_14 = false;
            enableGameObj(acc, false);
        }
        acc.setFlag(17, false);
        if (acc.testFlag(8) && !acc.isRebuild()) {
            GfObjUtil::rebuild(inout.m_handle);
        } else if (!acc.isDestroy()) {
            GfObjUtil::destroy(inout.m_handle);
        }
        return true;
    }
    float alpha = inout.m_alpha;
    if (alpha > 1.0f) {
        alpha = 1.0f;
    }
    acc.setAlphaLife(alpha);
    return false;
}

void GfGameObj::destroyGameObj(GF_OBJ_HANDLE* handle, float fadeTime) {
    if (GfObjUtil::getObj(handle) != nullptr) {
        if (!get()->addOutObj(handle, fadeTime, true)) {
            GfObjUtil::destroy(handle);
        }
    }
}

void GfGameObj::destroyGameObjWithAttribute(GF_OBJ_HANDLE* handle, float fadeTime, unsigned int attr) {
    if (GfObjUtil::getObj(handle) != nullptr) {
        GfGameObj* self = get();
        if (attr != 0) {
            ObjMsg msg = {handle, attr};
            self->m_msgs.push_back(msg);
        }
        if (!self->addOutObj(handle, fadeTime, true)) {
            GfObjUtil::destroy(handle);
        }
    }
}

bool GfGameObj::isDestroyGameObj(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.m_obj == nullptr) {
        return true;
    }
    return !acc.testFlag(14);
}

bool GfGameObj::isEnterGameObj(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    mm::mtl::FixedList<INOUT, 1024>& list = get()->m_inList;
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        if (it->m_handle == handle) {
            return true;
        }
    }
    return false;
}

void GfGameObj::setupEnterGameObj(GF_OBJ_HANDLE* handle, float fadeTime) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjAcc acc(handle);
    mm::mtl::FixedList<INOUT, 1024>& list = get()->m_inList;
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        if (it->m_handle == handle) {
            if (acc.getType() == 4 && GfDataBlade::isDummyBlade(acc.getBladeId())) {
                return;
            }
            it->m_fadeTime = fadeTime < 1e-6f ? 0.0f : fadeTime;
            acc.setAlphaLife(fadeTime == 0.0f ? 1.0f : 0.0f);
            return;
        }
    }
}

void GfGameObj::setupEnterGameObjMount(GF_OBJ_HANDLE* handle, GFATTACH attach, float fadeTime) {
    GfGameMount* mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr) {
        unsigned int count = mount->getAllWeapons();
        for (unsigned int i = 0; i < count; ++i) {
            setupEnterGameObj(mount->getAllWeapons(i), fadeTime);
        }
    }
}

void GfGameObj::setupLeaveGameObj(GF_OBJ_HANDLE* handle, float fadeTime) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfGameObj* self = get();
    GfObjAcc acc(handle);
    if (self->addOutObj(handle, fadeTime, true)) {
        acc.setCollisionChar(false);
        if (acc.testFlag(8)) {
            if (acc.getType() == 4) {
                mm::mtl::rttiCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->m_setup)->pad_70 = true;
            } else if (acc.getType() == 10) {
                mm::mtl::rttiCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->m_setup)->pad_70 = true;
            }
        }
    }
}

void GfGameObj::setupLeaveGameObjMount(GF_OBJ_HANDLE* handle, GFATTACH attach, float fadeTime) {
    GfGameMount* mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr) {
        unsigned int count = mount->getAllWeapons();
        for (unsigned int i = 0; i < count; ++i) {
            setupLeaveGameObj(mount->getAllWeapons(i), fadeTime);
        }
    }
}

void GfGameObj::enterStayObject(GF_OBJ_HANDLE* handle) {
    GfObjManager::enterStayObject(handle);
}

void GfGameObj::enterStayObjectMount(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    GfGameMount* mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr) {
        unsigned int count = mount->getAllWeapons();
        for (unsigned int i = 0; i < count; ++i) {
            GfObjManager::enterStayObject(mount->getAllWeapons(i));
        }
    }
}

void GfGameObj::enterStayObjectWithVolumeFade(GF_OBJ_HANDLE* handle) {
    GfObjSetup* setup = GfObjUtil::getObjSetup(handle);
    if (setup != nullptr) {
        setup->pad_50 = 1.0f;
        setup->pad_60 = false;
        setup->pad_64 = 4;
    }
    GfObjManager::enterStayObject(handle);
}

void GfGameObj::enterStayObjectMountWithVolumeFade(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    GfGameMount* mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr) {
        unsigned int count = mount->getAllWeapons();
        for (unsigned int i = 0; i < count; ++i) {
            enterStayObjectWithVolumeFade(mount->getAllWeapons(i));
        }
    }
}

bool GfGameObj::isEmpty() {
    GfGameObj* self = get();
    if (self == nullptr) {
        return true;
    }
    if (!self->m_listEnemy.empty()) {
        return false;
    }
    if (!self->m_listEnemyBlade.empty()) {
        return false;
    }
    if (!self->m_listType6.empty()) {
        return false;
    }
    if (!self->m_listType7.empty()) {
        return false;
    }
    if (!self->m_listType11.empty()) {
        return false;
    }
    if (!self->m_listDriver.empty()) {
        return false;
    }
    if (!self->m_listBlade.empty()) {
        return false;
    }
    if (!self->m_listType8.empty()) {
        return false;
    }
    if (!self->m_listType9.empty()) {
        return false;
    }
    if (!self->m_listType10.empty()) {
        return false;
    }
    if (!self->m_listType12.empty()) {
        return false;
    }
    if (!self->m_listType0.empty()) {
        return false;
    }
    if (!self->m_listType13.empty()) {
        return false;
    }
    if (!self->m_inList.empty()) {
        return false;
    }
    return self->m_outList.empty();
}

GfObj* GfGameObj::getObj(GF_OBJ_HANDLE* handle) {
    GfGameObj* self = get();
    GfObjAcc acc(handle);
    mm::mtl::FixedList<INOUT, 1024>& list = self->m_inList;
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        if (it->m_handle == handle) {
            return GfObjUtil::getObj(handle);
        }
    }
    if (!acc.testFlag(14)) {
        return nullptr;
    }
    return GfObjUtil::getObj(handle);
}

void GfGameObj::bdatReload() {
    GfGameObj* self = get();
    if (self == nullptr) {
        return;
    }
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = self->m_inList.begin(); it != self->m_inList.end(); ++it) {
        GfObjAcc acc((*it).m_handle);
        if (acc.getType() == 5) {
            GfObjSetupEnemy* setup = _gfgob::getEnemySetup((*it).m_handle);
            if (setup != nullptr) {
                SDataEnemy* data = setup->m_sdata;
                GfDataEnemy::setupSDataEnemy(*data, data->m_id, data->m_level);
            }
        }
    }
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = self->m_outList.begin(); it != self->m_outList.end(); ++it) {
        GfObjAcc acc((*it).m_handle);
        if (acc.getType() == 5) {
            GfObjSetupEnemy* setup = _gfgob::getEnemySetup((*it).m_handle);
            if (setup != nullptr) {
                SDataEnemy* data = setup->m_sdata;
                GfDataEnemy::setupSDataEnemy(*data, data->m_id, data->m_level);
            }
        }
    }
    for (ObjList::iterator it = self->m_listEnemy.begin(); it != self->m_listEnemy.end(); ++it) {
        GfObjSetupEnemy* setup = _gfgob::getEnemySetup(*it);
        if (setup != nullptr) {
            SDataEnemy* data = setup->m_sdata;
            GfDataEnemy::setupSDataEnemy(*data, data->m_id, data->m_level);
        }
    }
    for (ObjList::iterator it = self->m_listEnemyBlade.begin(); it != self->m_listEnemyBlade.end(); ++it) {
        GfObjSetupEnemy* setup = _gfgob::getEnemySetup(*it);
        if (setup != nullptr) {
            SDataEnemy* data = setup->m_sdata;
            GfDataEnemy::setupSDataEnemy(*data, data->m_id, data->m_level);
        }
    }
}

int GfGameObj::getObjNumberByEnArrangeId(unsigned int arrangeId) {
    if (arrangeId == 0) {
        return 0;
    }
    int count = 0;
    ObjList* list = getList(5);
    for (ObjList::iterator it = list->begin(); it != list->end(); ++it) {
        DataParamAcc acc(*it);
        if ((acc.isValid() ? acc.getBdatId() : 0) == arrangeId) {
            ++count;
        }
    }
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = m_inList.begin(); it != m_inList.end(); ++it) {
        DataParamAcc acc((*it).m_handle);
        if (acc.getObjType() == 5 && (acc.isValid() ? acc.getBdatId() : 0) == arrangeId) {
            ++count;
        }
    }
    for (mm::mtl::FixedList<INOUT, 1024>::iterator it = m_outList.begin(); it != m_outList.end(); ++it) {
        DataParamAcc acc((*it).m_handle);
        if (acc.getObjType() == 5 && (acc.isValid() ? acc.getBdatId() : 0) == arrangeId) {
            ++count;
        }
    }
    return count;
}
}  // namespace gf

// instantiated for gf::GfGameObjEnemy::leaveEnemyObj, gf::GfObjManager::checkTerminate (not written yet)
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 256>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 256>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 256>::iterator);

// instantiated for gf::GfGameObjEnemy::leaveEnemyObj (not written yet)
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 64>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 64>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 64>::iterator);

// instantiated for gf::GfGameObjEnemy::leaveEnemyObj (not written yet)
template mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::iterator mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::erase(mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::iterator);

namespace gf {

GfGameObjEnemy::~GfGameObjEnemy() {}

}  // namespace gf

namespace gf {

bool GfGameObjEnemy::isGenusLink(GF_OBJ_HANDLE* handle) {
    GfGameObjEnemy* self = get();
    if (self == nullptr) {
        return false;
    }
    GfObjAcc acc(handle);
    if (acc.isBattle()) {
        return false;
    }
    return self->pad_1890.find(handle) != self->pad_1890.end();
}

static bool fn_71002B5A34(float angle, mm::Vec3& pos, const GfObjSetupEnemy* setup) {
    float r = mm::normalizeRadian(setup->pad_30.y + angle);
    float dist = 3.0f;
    do {
        mm::Vec3 hit;
        mm::Vec3 from = setup->m_initialPos + mm::Vec3(dist * sinf(r), 2.0f, dist * cosf(r));
        if (gf::util::getUnderHitCollision(hit, from, 10.0f)) {
            pos = hit + mm::Vec3(0.0f, 0.01f, 0.0f);
            return true;
        }
        dist -= 0.1f;
    } while (dist >= 0.2f);
    return false;
}

}  // namespace gf
