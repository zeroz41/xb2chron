#ifndef CLASSES_GF_CHAINATTACKCAMERA_H
#define CLASSES_GF_CHAINATTACKCAMERA_H

#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/Camera.h"
#include "fw/ColiCheck.h"

namespace fw { class Transform; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B45A68: btl::ChainAttackManager's camera: setup picks a bdat row by the target's size (lottery) and
// pushes a gf::ChainAttackCameraEntity moving between the row's points; change picks again; end pops it. The field
// names are not the original's.
class ChainAttackCamera {
public:
    // a row of the chain attack camera bdat (GfDataBdat 0x14), its points turned and placed by updateParam (the field
    // names follow the bdat's columns, they are not the original's)
    struct Param {
        unsigned char m_speedType;  // SpeedType: 0 moves by a rate a frame (SpeedNum / 10000), others over frames
        float m_speedNum;           // SpeedNum
        unsigned char m_moveType;   // MoveType: the entity's m_moveType
        unsigned char m_startLookPosType;  // S_LookPosType: 0 looks from the attacker's bone, others the target's
        mm::Vec3 m_startPos;        // S_PosX/Y/Z (centimetres in the bdat)
        mm::Vec3 m_startLook;       // S_LookX/Y/Z
        unsigned char m_endLookPosType;    // E_LookPosType
        mm::Vec3 m_endPos;          // E_PosX/Y/Z
        mm::Vec3 m_endLook;         // E_LookX/Y/Z
    };

    ChainAttackCamera();
    virtual ~ChainAttackCamera();  // slot 0
    void setup(GF_OBJ_HANDLE* attacker, GF_OBJ_HANDLE* target);
    int lottery(unsigned char camType);
    void getParam(int id, Param& param);
    void updateParam(Param& param, const fw::Transform& transform, const mm::Vec3& attackerPos,
                     const mm::Vec3& targetPos);
    void start();
    void end();
    void destroyCamera(mm::mtl::IntrusivePtr<fw::Camera>* camera, float time);
    void change(GF_OBJ_HANDLE* attacker);

    mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // the entity while set up
    Param m_param;
    unsigned char m_sizeMask;  // the target's size bit (EnSize), 0xf for any
    GF_OBJ_HANDLE* m_target;
    fw::ColiCheckConfig m_coliConfig;
};
}  // namespace gf

#endif
