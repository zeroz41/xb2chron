#ifndef CLASSES_GF_GFMENUMODELVIEW_H
#define CLASSES_GF_GFMENUMODELVIEW_H

#include "classes/ui/UICtrlSimple.h"
#include "fw/Transform.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Vector.h"

namespace fw { class Camera; }
namespace fw { class CommonResource; }
namespace fw { class EffectPack; }
namespace fw { class RenderResource; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B5F8D0: the models a menu shows in its own view (render index), with their cameras and effects. Its
// menu row (gf::GfDataBdat table 0xFC, m_bdatId) names the camera file ("camera_file") and the effect file
// ("efp_file"); "obj_model%02d" columns name map objects. The names of the fields are not the original's unless
// a symbol names them.
class GfMenuModelView {
public:
    // what startObjectCtrl moves an object to: its constructor takes the object's current place, scale, alpha,
    // turn and vanish ratio
    class CtrlParam {
    public:
        CtrlParam(GF_OBJ_HANDLE* handle, float time, bool loop);
        // the target height: the object's current one plus y
        void setAddPosY(float y);
        // each sets its target and its flag bit (0x8, 0x20, 0x40, 0x100)
        void setMoveSclX(float x);
        void setMoveSclZ(float z);
        void setMoveAlpha(float alpha);
        void setMoveVanish(float ratio);

        GF_OBJ_HANDLE* m_handle;
        unsigned short m_flags;      // which targets are set: 0x2 height (setAddPosY), 0x8 scale x, 0x20 scale z, 0x40 alpha, 0x100 vanish
        unsigned short m_curveType;  // a ui::CURVE_TYPE
        float m_time;
        bool m_loop;
        float m_posX;
        float m_posY;
        float m_posZ;
        float m_scaleX;
        float m_scaleY;
        float m_scaleZ;
        float m_alpha;
        float m_rotY;
        float m_vanishRatio;
    };
    // one object: its handle and the values startObjectCtrl moves (place xyz, scale xyz, alpha, turn, vanish)
    class ObjEntry {
    public:
        GF_OBJ_HANDLE* m_handle;
        ui::UICtrlSimple<9> m_ctrl;
    };
    // an effect playEffect started (its handle) on an object
    class EffectEntry {
    public:
        EffectEntry() : m_handle(0), m_obj(reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {}

        unsigned int m_handle;
        GF_OBJ_HANDLE* m_obj;
    };

    GfMenuModelView(unsigned int uiObjHandle, unsigned int bdatId);
    virtual ~GfMenuModelView();  // slot 0
    void update();
    bool isLoading() const;  // its models still load (GfMenuObjBladeCreate::seqWaitLoading waits for false)

    static fw::Transform& getObjectTransformLocal(GF_OBJ_HANDLE* handle);
    static fw::Transform& getObjectTransform(GF_OBJ_HANDLE* handle);
    static void setVanishRatio(GF_OBJ_HANDLE* handle, float ratio);
    static float getVanishRatio(GF_OBJ_HANDLE* handle);
    static bool getObjectEffectPoint(GF_OBJ_HANDLE* handle, const char* name, mm::Vec3& pos);
    static void setObjectScale(GF_OBJ_HANDLE* handle, const mm::Vec3& scale);
    static void setObjectDisp(GF_OBJ_HANDLE* handle, bool disp);
    unsigned short getMapObjID(unsigned int index);
    void sendObjectCommand(GF_OBJ_HANDLE* handle, const char* cmd);
    void attachObject(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* parent, const char* bone);
    void startObjectCtrl(const CtrlParam& param);
    bool isObjectCtrlBusy(GF_OBJ_HANDLE* handle);
    const char* getObjectAnimationState(GF_OBJ_HANDLE* handle);
    void setObjectVanishParam(GF_OBJ_HANDLE* handle, unsigned int type);
    void setObjectVanishRatio(GF_OBJ_HANDLE* handle, float ratio);
    unsigned int addCamera(mm::mtl::IntrusivePtr<fw::Camera> camera);
    void popCamera(float time);
    void pushCamera(unsigned int index, float time);
    void resetCamera(unsigned int index, float time);
    void stopCameraMotion();  // GfMenuObjBladeCreate::seqResultEnd calls it before popCamera
    void playEffect(unsigned int slot, const char* name, const mm::Vec3& pos, GF_OBJ_HANDLE* handle);
    void playEffectFromCAS(unsigned int slot, const char* name, GF_OBJ_HANDLE* handle);
    void stopEffect(unsigned int slot);
    void removeEffect(unsigned int slot);
    void delGfObj(unsigned int type, unsigned int bdatId);
    GF_OBJ_HANDLE* findGfObj(unsigned int type, unsigned int bdatId);
    bool checkGfObj(unsigned int type, unsigned int bdatId);

    static fw::Transform s_DefTransform;

    unsigned int m_bdatId;
    unsigned int m_uiObjHandle;
    unsigned int m_renderIndex;  // the UI object's; its view is render index + 1
    mm::mtl::IntrusivePtr<fw::CommonResource> m_cameraRes;
    mm::mtl::IntrusivePtr<fw::RenderResource> m_effectRes;
    mm::mtl::FixedVector<ObjEntry, 16> m_objs;
    mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::Camera> > m_cameras;
    mm::mtl::FixedVector<unsigned int, 16> m_cameraStack;  // m_cameras indices pushed on the layer
    mm::mtl::IntrusivePtr<fw::EffectPack> m_effectPack;
    EffectEntry m_effects[16];
    bool m_isReady;  // set when the row names no files (isLoading)
    unsigned char pad_aa9[0x7];
    mm::mtl::IntrusivePtr<fw::Camera> m_motionCamera;
};
}  // namespace gf

#endif
