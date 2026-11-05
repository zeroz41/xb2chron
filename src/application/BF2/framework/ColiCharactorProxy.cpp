#include "classes/fw/ColiCharactorProxy.h"
#include "classes/fw/ColiCheckCallback.h"
#include "classes/fw/ColiObject.h"
#include "fw/ColiCheck.h"
#include "idcoli/IDColiCheckObj.h"
#include "idcoli/IDColiDef.h"
#include "idcoli/IDColiMove.h"
#include "idcoli/IDColiPhantom.h"
#include "classes/idcoli/IDColiObj.h"

namespace fw {

ColiCharactorProxy::ColiCharactorProxy() : m_object(nullptr), m_floor(0.4f) {}

void ColiCharactorProxy::integrate(mm::Vec3 const& position, mm::Vec3 const& move, mm::Vec3* result) {
    mm::Vec3 target = position + move;
    idcoli::IDColiMove coliMove;
    coliMove.setFloor(m_floor);
    coliMove.setAccuracy(true);
    coliMove.moveColi(m_object->m_coliObj, target);
    *result = coliMove.m_result;
}

// hands a test's query the config (the queries share one layout; the helper's name is not the original's)
template <class Query>
static inline void setupQuery(Query& query, ColiCheckCallback& callback, const ColiCheckConfig& config,
                              mm::Vec3* positions, mm::Vec3* normals) {
    callback.m_param = config.m_callbackParam;
    switch (config.m_mode) {
    case 0:
        query.m_result.m_type = 0;
        break;
    case 1:
        query.m_result.m_type = 1;
        break;
    case 2:
        query.m_result.m_type = 2;
        query.m_result.m_tblMax = 256;
        query.m_result.m_tblPos = positions;
        query.m_result.m_tblNormal = normals;
        break;
    default:
        break;
    }
    query.pad_1 = (config.m_flags & 1) != 0;
    query.pad_2 = (config.m_flags & 8) != 0;
    query.pad_0 = (config.m_flags & 2) != 0;
    query.m_radiusSq = config.m_radius * config.m_radius;
    query.m_result.m_ignoreMaterial = ~config.m_mask;
    query.m_result.m_calcVector = callback.m_param;
    query.m_callback = &callback;
}

bool ColiCheck::testLine(TColiCheckResult<256>& result, const mm::Vec3& start, const mm::Vec3& end,
                         const ColiCheckConfig& config) {
    result.clear();
    bool hit = false;
    if (config.m_flags & 0xB) {
        idcoli::IDColiDef def;
        ColiCheckCallback callback(&result);
        mm::Vec3 positions[256];
        mm::Vec3 normals[256];
        setupQuery(def, callback, config, positions, normals);
        hit = result.m_hit = def.testLine(start, end);
    }
    if (config.m_flags & 4) {
        idcoli::IDColiPhantom phantom;
        ColiCheckCallback callback(&result);
        mm::Vec3 positions[256];
        mm::Vec3 normals[256];
        setupQuery(phantom, callback, config, positions, normals);
        result.m_hit = phantom.testLine(start, end);
        hit |= result.m_hit;
    }
    result.m_hit = hit;
    return hit;
}

bool ColiCheck::testLineChara(TColiCheckResult<256>& result, const mm::Vec3& start, const mm::Vec3& end,
                              const ColiCheckConfig& config) {
    result.clear();
    idcoli::IDColiDef def;
    ColiCheckCallback callback(&result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    setupQuery(def, callback, config, positions, normals);
    return result.m_hit = def.testLine(start, end);
}

bool ColiCheck::testLineColi(TColiCheckResult<256>& result, const idcoli::IDColiObj* obj, const mm::Vec3& start,
                             const mm::Vec3& end, const ColiCheckConfig& config) {
    result.clear();
    idcoli::IDColiCheckObj check;
    ColiCheckCallback callback(&result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    setupQuery(check, callback, config, positions, normals);
    return result.m_hit = check.testLine(obj, start, end);
}

bool ColiCheck::testSphere(TColiCheckResult<256>& result, const mm::Vec3& pos, float radius,
                           const ColiCheckConfig& config) {
    result.clear();
    bool hit = false;
    if (config.m_flags & 0xB) {
        idcoli::IDColiDef def;
        ColiCheckCallback callback(&result);
        mm::Vec3 positions[256];
        mm::Vec3 normals[256];
        setupQuery(def, callback, config, positions, normals);
        hit = result.m_hit = def.testSphere(pos, radius);
    }
    if (config.m_flags & 4) {
        idcoli::IDColiPhantom phantom;
        ColiCheckCallback callback(&result);
        mm::Vec3 positions[256];
        mm::Vec3 normals[256];
        setupQuery(phantom, callback, config, positions, normals);
        result.m_hit = phantom.testSphere(pos, radius);
        hit |= result.m_hit;
    }
    result.m_hit = hit;
    return hit;
}

bool ColiCheck::testSphereChara(TColiCheckResult<256>& result, const mm::Vec3& pos, float radius,
                                const ColiCheckConfig& config) {
    result.clear();
    idcoli::IDColiDef def;
    ColiCheckCallback callback(&result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    setupQuery(def, callback, config, positions, normals);
    return result.m_hit = def.testSphere(pos, radius);
}

bool ColiCheck::testSpherePhantom(TColiCheckResult<256>& result, const mm::Vec3& pos, float radius,
                                  const ColiCheckConfig& config) {
    result.clear();
    idcoli::IDColiPhantom phantom;
    ColiCheckCallback callback(&result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    setupQuery(phantom, callback, config, positions, normals);
    return result.m_hit = phantom.testSphere(pos, radius);
}

bool ColiCheck::testSphereColi(TColiCheckResult<256>& result, const idcoli::IDColiObj* obj, const mm::Vec3& pos,
                               float radius, const ColiCheckConfig& config) {
    result.clear();
    idcoli::IDColiCheckObj check;
    ColiCheckCallback callback(&result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    setupQuery(check, callback, config, positions, normals);
    return result.m_hit = check.testSphere(obj, pos, radius);
}

bool ColiCheck::testCapsule(TColiCheckResult<256>& result, const mm::Vec3& start, const mm::Vec3& end, float radius,
                            const ColiCheckConfig& config) {
    result.clear();
    bool hit = false;
    if (config.m_flags & 0xB) {
        idcoli::IDColiDef def;
        ColiCheckCallback callback(&result);
        mm::Vec3 positions[256];
        mm::Vec3 normals[256];
        setupQuery(def, callback, config, positions, normals);
        hit = result.m_hit = def.testCapsule(start, end, radius);
    }
    if (config.m_flags & 4) {
        idcoli::IDColiPhantom phantom;
        ColiCheckCallback callback(&result);
        mm::Vec3 positions[256];
        mm::Vec3 normals[256];
        setupQuery(phantom, callback, config, positions, normals);
        result.m_hit = phantom.testCapsule(start, end, radius);
        hit |= result.m_hit;
    }
    result.m_hit = hit;
    return hit;
}

bool ColiCheck::testCapsuleChara(TColiCheckResult<256>& result, const mm::Vec3& start, const mm::Vec3& end,
                                 float radius, const ColiCheckConfig& config) {
    result.clear();
    idcoli::IDColiDef def;
    ColiCheckCallback callback(&result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    setupQuery(def, callback, config, positions, normals);
    return result.m_hit = def.testCapsule(start, end, radius);
}

bool ColiCheck::testObjectChara(TColiCheckResult<256>& result, ColiObject* object, const ColiCheckConfig& config) {
    if (object == nullptr || object->m_coliObj == nullptr) {
        return false;
    }
    result.clear();
    bool hit;
    if (object->m_coliObj->m_type == 1) {
        idcoli::IDColiDef def;
        ColiCheckCallback callback(&result);
        mm::Vec3 positions[256];
        mm::Vec3 normals[256];
        setupQuery(def, callback, config, positions, normals);
        hit = def.testCharColiObj(object->m_coliObj, config.pad_c);
    } else {
        idcoli::IDColiPhantom phantom;
        ColiCheckCallback callback(&result);
        mm::Vec3 positions[256];
        mm::Vec3 normals[256];
        setupQuery(phantom, callback, config, positions, normals);
        hit = phantom.testPhantomColiObj(object->m_coliObj, config.pad_c);
    }
    return result.m_hit = hit;
}

bool ColiCheck::testObjectPhantom(TColiCheckResult<256>& result, ColiObject* object, const ColiCheckConfig& config) {
    if (object == nullptr || object->m_coliObj == nullptr) {
        return false;
    }
    result.clear();
    idcoli::IDColiPhantom phantom;
    ColiCheckCallback callback(&result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    setupQuery(phantom, callback, config, positions, normals);
    return result.m_hit = phantom.testCharColiObj(object->m_coliObj, config.pad_c);
}

}  // namespace fw
