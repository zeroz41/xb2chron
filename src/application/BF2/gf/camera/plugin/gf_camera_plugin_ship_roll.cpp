#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/CameraPlugin.h"
#include "classes/fw/Framework.h"
#include "classes/gf/GfGameManager.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/gf/GimmickCameraParams.h"
#include "classes/gf/PlayerCamera.h"
#include "classes/gf/ShipRollPlugin.h"
#include "math.h"
#include "ml/MtRand.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {

// the plugin ShipRollPlugin::setEnable creates and pushes onto the camera layer while rolling is enabled
static mm::mtl::IntrusivePtr<fw::CameraPlugin> s_plugin;

GimmickCameraParams::GimmickCameraParams() : m_size(0), m_params(nullptr) {}

GimmickCameraParams::GimmickCameraParams(void* data, int version) : m_size(0), m_params(nullptr) {
    Header* header = static_cast<Header*>(data);
    if (header->m_magic == 0x504347 && header->m_version == version) {
        m_size = header->m_size;
        m_params = header->m_params;
    }
}

void GimmickCameraParams::setup(void* data, int version) {
    Header* header = static_cast<Header*>(data);
    if (header->m_magic == 0x504347 && header->m_version == version) {
        m_size = header->m_size;
        m_params = header->m_params;
    }
}

GimmickCameraParams::~GimmickCameraParams() {}

int GimmickCameraParams::getSize() const {
    return m_size;
}

const GimmickCameraParams::Param* GimmickCameraParams::getParam(int index) const {
    // what an index past the file's entries gets
    static const Param s_empty = {};
    if (index < m_size) {
        return &m_params[index];
    }
    return &s_empty;
}

ShipRollPlugin::~ShipRollPlugin() {}

void ShipRollPlugin::update(fw::Camera* camera) {
    bool pause = GfGameManager::isPlayerCameraPause();
    if (camera == nullptr || pause) {
        return;
    }
    if (!camera->getRTTI()->isKindOf(&PlayerCamera::m_rtti)) {
        return;
    }
    const PlayerCamera::Param* param = static_cast<PlayerCamera*>(camera)->m_param.get<PlayerCamera::Param>();
    if (!param->m_shipCurve) {
        m_rollSwing.m_angle = 0.0f;
        m_pitchSwing.m_angle = 0.0f;
        if (m_rollSwing.m_enable) {
            if (m_rollSwing.m_back) {
                m_roll -= param->m_shipRollMove * 0.0174532924f;
                if (m_roll < m_rollSwing.m_amplitude * -0.0174532924f) {
                    m_rollSwing.m_back = false;
                    if (param->m_shipRandom) {
                        m_rollSwing.m_amplitude = ml::mtRandf1(param->m_shipRollMin, param->m_shipRollMax);
                    } else {
                        m_rollSwing.m_amplitude = param->m_shipRollMax;
                    }
                }
            } else {
                m_roll += param->m_shipRollMove * 0.0174532924f;
                if (m_rollSwing.m_amplitude * 0.0174532924f < m_roll) {
                    m_rollSwing.m_back = true;
                    if (param->m_shipRandom) {
                        m_rollSwing.m_amplitude = ml::mtRandf1(param->m_shipRollMin, param->m_shipRollMax);
                    } else {
                        m_rollSwing.m_amplitude = param->m_shipRollMax;
                    }
                }
            }
        } else {
            m_roll = 0.0f;
            m_rollSwing.m_amplitude = param->m_shipRollMax;
        }
        if (m_pitchSwing.m_enable) {
            if (m_pitchSwing.m_back) {
                m_pitch -= param->m_shipPitchMove;
                if (m_pitch < -m_pitchSwing.m_amplitude) {
                    m_pitchSwing.m_back = false;
                    if (param->m_shipRandom) {
                        float t = ml::mtRandf1();
                        m_pitchSwing.m_amplitude = param->m_shipPitchMin + t * (param->m_shipPitchMax - param->m_shipPitchMin);
                    } else {
                        m_pitchSwing.m_amplitude = param->m_shipPitchMax;
                    }
                }
            } else {
                m_pitch += param->m_shipPitchMove;
                if (m_pitchSwing.m_amplitude < m_pitch) {
                    m_pitchSwing.m_back = true;
                    if (param->m_shipRandom) {
                        float t = ml::mtRandf1();
                        m_pitchSwing.m_amplitude = param->m_shipPitchMin + t * (param->m_shipPitchMax - param->m_shipPitchMin);
                    } else {
                        m_pitchSwing.m_amplitude = param->m_shipPitchMax;
                    }
                }
            }
        } else {
            m_pitch = 0.0f;
            m_pitchSwing.m_amplitude = param->m_shipPitchMax;
        }
    } else {
        if (m_rollSwing.m_enable) {
            m_rollSwing.m_angle += param->m_shipRollMove;
            if (m_rollSwing.m_angle > 360.0f) {
                m_rollSwing.m_angle -= 360.0f;
                if (param->m_shipRandom) {
                    m_rollSwing.m_amplitude = ml::mtRandf1(param->m_shipRollMin, param->m_shipRollMax);
                } else {
                    m_rollSwing.m_amplitude = param->m_shipRollMax;
                }
            }
            m_roll = m_rollSwing.m_amplitude * sinf(m_rollSwing.m_angle * 0.0174532924f) * 0.0174532924f;
        } else {
            m_rollSwing.m_angle = 0.0f;
            m_roll = 0.0f;
            m_rollSwing.m_amplitude = param->m_shipRollMax;
        }
        if (m_pitchSwing.m_enable) {
            m_pitchSwing.m_angle += param->m_shipPitchMove;
            if (m_pitchSwing.m_angle > 360.0f) {
                m_pitchSwing.m_angle -= 360.0f;
                if (param->m_shipRandom) {
                    m_pitchSwing.m_amplitude = ml::mtRandf1(param->m_shipPitchMin, param->m_shipPitchMax);
                } else {
                    m_pitchSwing.m_amplitude = param->m_shipPitchMax;
                }
            }
            m_pitch = m_pitchSwing.m_amplitude * sinf(m_pitchSwing.m_angle * 0.0174532924f);
        } else {
            m_pitchSwing.m_angle = 0.0f;
            m_pitch = 0.0f;
            m_pitchSwing.m_amplitude = param->m_shipPitchMax;
        }
    }
    camera->m_eye.y = m_pitch + camera->m_eye.y;
    camera->m_target.y = m_pitch + camera->m_target.y;
    camera->m_roll = m_roll;
    camera->updateViewMatrix();
}

// setEnable (0x71001D86D0) is not here yet: candidates/gf_camera_plugin_ship_roll.near.cpp's differs from the
// original only in reusing the first load of s_plugin where the original loads it again after the branch

}  // namespace gf
