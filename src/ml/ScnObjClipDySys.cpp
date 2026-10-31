#include "classes/ml/ScnObjClipDySys.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "ml/DrCalcClipObj.h"
#include "ml/DrCreator.h"

namespace ml {

inline ScnObjClipDySys::ScnObjClipDySys(Scn* scn, const void* res, int view)
    : ScnObjClip(scn), m_pClipObj(nullptr), m_view(view), m_name("clipList") {
    DrCreator creator;
    m_pClipObj = creator.createClipObj(res, m_view);
}

ScnObjClipDySys::~ScnObjClipDySys() {
    if (m_pClipObj != nullptr) {
        m_pClipObj->release();
    }
}

ScnObjClipDySys* ScnObjClipDySys::create(Scn* scn, const void* res, int view) {
    if (!scn->m_pool->isValidInsert(4)) {
        return nullptr;
    }
    ScnObjClipDySys* obj = new (scn->m_allocHandle, nullptr, 0, 4, false) ScnObjClipDySys(scn, res, view);
    scn->m_pool->insert(obj);
    return obj;
}

const char* ScnObjClipDySys::getName() const {
    return m_name.m_str;
}

}  // namespace ml
