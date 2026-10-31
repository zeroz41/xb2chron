#include "classes/fw/EffectPoint.h"

#include <math.h>
#include <string.h>

#include "classes/fw/Framework.h"
#include "classes/fw/ModelObject.h"
#include "csvb/CsvbData.h"
#include "ml/ScnObjAccResNode.h"
#include "mm/mtl/Hash.h"

namespace fw {

EffectPoint::EffectPoint(const EfpInitData& init) : m_RefCount(0), m_model(nullptr) {
    m_model = init.model;
    m_createFrame = init.createFrame;
    m_releaseFrame = init.releaseFrame;
    csvb::CCsvbData csv;
    if (init.data != nullptr) {
        csv.Load(init.allocator, init.data, init.size);
    }
    m_params.setAllocator(Framework::getAllocator());
    m_transforms.setAllocator(Framework::getAllocator());
    unsigned int count = 0;
    if (init.data != nullptr) {
        count = csv.GetRowCount();
        if (count != 0) {
            m_params.reserve(count);
            m_transforms.reserve(count);
        }
    }
    if (init.data != nullptr) {
        for (unsigned int row = 0; row < count; row++) {
            if (csv.GetColumCount(row) != 8) {
                continue;
            }
            Param param;
            param.name = csv.GetString(row, 0);
            param.hash = mm::mtl::hashStrCrc(param.name.m_str);
            param.parentName = csv.GetString(row, 1);
            param.dirty = false;
            float x = csv.GetFloat(row, 2);
            float y = csv.GetFloat(row, 3);
            float z = csv.GetFloat(row, 4);
            if (init.scale != 1.0f) {
                x *= init.scale;
                y *= init.scale;
                z *= init.scale;
            }
            float rx = csv.GetFloat(row, 5) * 0.017453292f;
            float ry = csv.GetFloat(row, 6) * 0.017453292f;
            float rz = csv.GetFloat(row, 7) * 0.017453292f;
            param.offset.setRotXYZ(mm::Vec3(rx, ry, rz));
            param.offset.m[3][0] = x;
            param.offset.m[3][1] = y;
            param.offset.m[3][2] = z;
            param.frame = m_createFrame(param.parentName.m_str);
            param.scale = mm::Vec3::zero;
            if (m_model != nullptr) {
                ml::ScnObjAccResNode node(m_model->getInterface());
                param.boneIndex = node.getBoneIndex(param.parentName.m_str);
            } else {
                param.boneIndex = -1;
            }
            m_params.push_back(param);
            m_transforms.push_back(param.offset);
        }
    }
}

EffectPoint::~EffectPoint() {
    for (unsigned int i = 0; i < m_params.size(); i++) {
        m_releaseFrame(m_params[i].parentName.m_str);
    }
    m_params.destroy();
    m_transforms.destroy();
}

void EffectPoint::update(const fw::UpdateInfo&) {
    for (unsigned int i = 0; i < m_params.size(); i++) {
        Param& param = m_params[i];
        if (param.dirty) {
            calcPoint(param, m_transforms[i]);
            param.dirty = true;
        }
    }
}

int EffectPoint::getPointIndex(const char* name) const {
    if (m_params.size() != 0) {
        unsigned int hash = mm::mtl::hashStrCrc(name);
        for (unsigned int i = 0; i < m_params.size(); i++) {
            if (hash == m_params[i].hash && strcmp(name, m_params[i].name.m_str) == 0) {
                return i;
            }
        }
    }
    return -1;
}

const char* EffectPoint::getPointName(int index) const {
    if (index >= 0 && index < getPointCount()) {
        return m_params[index].name.m_str;
    }
    return nullptr;
}

const mm::Mat44& EffectPoint::getPointTransform(int index) const {
    if (index >= 0 && index < getPointCount()) {
        return m_transforms[index];
    }
    return mm::Mat44::identity;
}

const mm::Vec3& EffectPoint::getScale(int index) const {
    if (index >= 0 && index < getPointCount()) {
        return m_params[index].scale;
    }
    return mm::Vec3::unit;
}

int EffectPoint::getPointCount() const {
    return m_params.size();
}

void EffectPoint::setDirty(unsigned int index, bool dirty) {
    if (index < getPointCount()) {
        m_params[index].dirty = dirty;
    }
}

bool EffectPoint::isDirty(unsigned int index) {
    return m_params[index].dirty;
}

const char* EffectPoint::getParentName(const char* name) {
    for (unsigned int i = 0; i < m_params.size(); i++) {
        if (strcmp(m_params[i].name.m_str, name) == 0) {
            return m_params[i].parentName.m_str;
        }
    }
    return nullptr;
}

mm::Mat44 EffectPoint::getOffset(const char* name) {
    for (unsigned int i = 0; i < m_params.size(); i++) {
        if (strcmp(m_params[i].name.m_str, name) == 0) {
            return m_params[i].offset;
        }
    }
    return mm::Mat44::identity;
}

}  // namespace fw
