#define MM_LIB_FROM_EFLIB
#include "ptlib/forcefield/FfManager.h"
#include "ptlib/forcefield/TurbulenceN.h"
#include "ptlib/ParticleSystem.h"
#include "mm/MMStdBase.h"
#include "new"

#define PTLIB_FORCE_FIELD_PATH "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/forcefield/particle_force_field.cpp"

namespace ptlib {

// the gradients ImprovedNoise::noise picks with a hash's low four bits (Perlin's twelve and four of them again)
// (Proposed name, not the original's: the symbols leave it unnamed (lbl_71015EAE50))
static mm::Vec3 s_grad[16] = {
    mm::Vec3(1.0f, 1.0f, 0.0f),  mm::Vec3(-1.0f, 1.0f, 0.0f),  mm::Vec3(1.0f, -1.0f, 0.0f), mm::Vec3(-1.0f, -1.0f, 0.0f),
    mm::Vec3(1.0f, 0.0f, 1.0f),  mm::Vec3(-1.0f, 0.0f, 1.0f),  mm::Vec3(1.0f, 0.0f, -1.0f), mm::Vec3(-1.0f, 0.0f, -1.0f),
    mm::Vec3(0.0f, 1.0f, 1.0f),  mm::Vec3(0.0f, -1.0f, 1.0f),  mm::Vec3(0.0f, 1.0f, -1.0f), mm::Vec3(0.0f, -1.0f, -1.0f),
    mm::Vec3(1.0f, 1.0f, 0.0f),  mm::Vec3(0.0f, -1.0f, 1.0f),  mm::Vec3(-1.0f, 1.0f, 0.0f), mm::Vec3(0.0f, -1.0f, -1.0f),
};

// Perlin's permutation, which ImprovedNoise's constructor copies twice
// (Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B80840))
static int s_permutation[256] = {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225,
    140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148,
    247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
    57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175,
    74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
    60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
    65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169,
    200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64,
    52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212,
    207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213,
    119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
    129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104,
    218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
    81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157,
    184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93,
    222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
};

namespace forcefield {

// the manager init makes (Proposed name, not the original's: the symbols leave it unnamed (lbl_71015EAE38))
static FfManager* s_pIns;

void FfManager::init() {
#line 22 PTLIB_FORCE_FIELD_PATH
    getPtr() = static_cast<FfManager*>(ParticleManager::sysAlloc(sizeof(FfManager), 16, __FILE__, __LINE__));
    if (getPtr() != nullptr) {
        new (getPtr()) FfManager;
    }
}

FfManager*& FfManager::getPtr() {
    return s_pIns;
}

void FfManager::term() {
    if (getPtr() != nullptr) {
        FfManager* pIns = getPtr();
        for (ForceList::iterator it = pIns->m_forces.begin(); it != pIns->m_forces.end(); ++it) {
            if (*it != nullptr) {
                ParticleManager::sysFree(*it);
            }
        }
        pIns->m_forces.clear();
        getPtr()->~FfManager();
        if (getPtr() != nullptr) {
            ParticleManager::sysFree(getPtr());
            getPtr() = nullptr;
        }
    }
}

void FfManager::update(float frame) {
    for (ForceList::iterator it = m_forces.begin(); it != m_forces.end();) {
        Force* pForce = *it;
        pForce->m_frame += (int)frame;
        if (pForce->m_param.m_life != -1 && pForce->m_param.m_life <= pForce->m_frame) {
            it = m_forces.erase(it);
            if (pForce != nullptr) {
                ParticleManager::sysFree(pForce);
            }
        } else {
            ++it;
        }
    }
}

void FfManager::addForce(const AddForceParam& param) {
#line 306 PTLIB_FORCE_FIELD_PATH
    Force* pForce = new (ParticleManager::sysAlloc(sizeof(Force), 16, __FILE__, __LINE__)) Force;
    if (pForce != nullptr) {
        pForce->m_param = param;
        if (pForce->m_param.m_life != -1) {
            pForce->m_param.m_life++;
        }
        pForce->m_frame = 0;
        m_forces.push_back(pForce);
        return;
    }
    efMsg("memory empty");
}

}  // namespace forcefield

void TurbulenceN::init() {
    s_fTotalTime = 0.0f;
}

void TurbulenceN::updateTime(float time) {
    s_fTotalTime += time;
}

// turb3d (0x7100859DFC) and ImprovedNoise::noise (0x7100859F9C) are not identical yet: session31/pforce/wip

ImprovedNoise::ImprovedNoise() {
    for (int i = 0; i < 256; i++) {
        p[256 + i] = p[i] = s_permutation[i];
    }
}

float TurbulenceN::s_fTotalTime;
ImprovedNoise TurbulenceN::s_noise;

}  // namespace ptlib
