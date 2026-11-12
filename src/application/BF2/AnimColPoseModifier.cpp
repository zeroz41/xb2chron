#include "mm/mtl/Vector.h"
#include "classes/fw/AnimColPoseModifier.h"
#include "classes/fw/AnimVolumeFadeModifier.h"
#include "classes/fw/ModelObject.h"
#include "classes/fw/ColiObject.h"
#include "idcoli/IDColiParms.h"
#include "ml/ScnObjAccResNode.h"
#include "ml/ScnObjAccEtcParams.h"
#include "ml/ScnObjAccVolumeFade.h"
#include <stdlib.h>
#include <string.h>

namespace fw {

AnimColPoseModifier::AnimColPoseModifier() : m_model(nullptr), m_coli(nullptr) {}

AnimColPoseModifier::~AnimColPoseModifier() {}

void AnimColPoseModifier::bind(ModelObject* model, ColiObject* coli, mm::mtl::IAllocator* allocator) {
    unbind();
    if (model != nullptr) {
        m_model = model;
        model->addRef();
    }
    if (coli != nullptr) {
        m_coli = coli;
        coli->addRef();
    }
    if (!isBound()) {
        return;
    }
    m_boneIndices.setAllocator(allocator);
    idcoli::IDColiParmsBone bones(m_coli->m_coliObj);
    ml::ScnObjAccResNode nodes(m_model->getInterface());
    unsigned int count = bones.getBoneMax();
    m_boneIndices.resize(count, -1);
    for (unsigned int i = 0; i < count; i++) {
        int node = nodes.getBoneIndex(bones.getBoneName(i));
        if (node >= 0) {
            m_boneIndices[i] = node;
        }
    }
}

void AnimColPoseModifier::unbind() {
    if (m_model != nullptr) {
        m_model->release();
        m_model = nullptr;
    }
    if (m_coli != nullptr) {
        m_coli->release();
        m_coli = nullptr;
    }
    m_boneIndices.clear();
}

void AnimColPoseModifier::apply() {
    if (!isBound()) {
        return;
    }
    idcoli::IDColiParmsBone bones(m_coli->m_coliObj);
    ml::ScnObjAccResNode nodes(m_model->getInterface());
    for (unsigned int i = 0; i < m_boneIndices.size(); i++) {
        short node = m_boneIndices[i];
        if (node >= 0) {
            bones.setBoneMatrix(i, nodes.getBoneMat(node));
        }
    }
}

AnimVolumeFadeModifier::AnimVolumeFadeModifier() : m_model(nullptr), m_useVolumeFadeAcc(true) {}

AnimVolumeFadeModifier::~AnimVolumeFadeModifier() {}

void AnimVolumeFadeModifier::unbind() {
    if (m_model != nullptr) {
        m_model->release();
        m_model = nullptr;
    }
}

void AnimVolumeFadeModifier::bind(ModelObject* model) {
    unbind();
    if (model == nullptr) {
        return;
    }
    m_model = model;
    model->addRef();
    for (int i = 0; i < 6; i++) {
        m_partsAlpha[i] = 1.0f;
    }
    for (int i = 0; i < 6; i++) {
        m_paramIndices[i] = -1;
    }
    ml::ScnObjAccEtcParams params(m_model->getInterface());
    unsigned int count = params.getMax();
    m_useVolumeFadeAcc = true;
    for (unsigned int i = 0; i < count; i++) {
        const char* name = params.getName(i);
        if (strncmp(name, "VolumeFade_", 11) == 0) {
            m_useVolumeFadeAcc = false;
            m_paramIndices[atoi(name + 11)] = i;
        }
    }
}

void AnimVolumeFadeModifier::apply() {
    if (m_condition.isValid() && !m_condition()) {
        return;
    }
    if (!m_useVolumeFadeAcc) {
        ml::ScnObjAccEtcParams params(m_model->getInterface());
        for (int i = 0; i < 6; i++) {
            if (m_paramIndices[i] >= 0) {
                params.setParams(m_paramIndices[i], m_partsAlpha[i]);
            }
        }
    } else {
        ml::ScnObjAccVolumeFade fade(m_model->getInterface());
        for (unsigned int i = 0; i < fade.getMax(); i++) {
            fade.setRatio(m_partsAlpha[i], i);
        }
    }
}

}  // namespace fw
