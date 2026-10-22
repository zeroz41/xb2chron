#ifndef CLASSES_GF_GFOBJ_H
#define CLASSES_GF_GFOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/MessageObject.h"
#include "classes/fw/UpdatableObject.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GFOBJ_INFO; }

namespace gf {
// table 0x7100B69E08; its fw::MessageObject at 0xE0 (that table: getRTTI, the destructors, recieveMessage)
class GfObj : public ::fw::UpdatableObject, public ::fw::MessageObject {
public:
    GfObj(unsigned int type, const fw::HandlePtr<fw::UpdatableObject>& handle, unsigned int arg);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObj();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 4
    virtual void onEvent(fw::ObjectEvent const&);  // slot 5
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 6
    // sets or clears m_updateFlags bit 1 and has GfObjUtil::applyExecUpdate decide m_execUpdate again
    void setUpdateComponent(bool on);
    static mm::mtl::RTTI m_rtti;
    // (the names below are not the original's)
    GF_OBJ_HANDLE* m_handle;  // its handle: GfObjAcc(GfObj*) looks the object's info up by it
    // its info at GfObjManager (GfObjUtil::applyExecUpdate tests its flags); none at first
    GFOBJ_INFO* m_info;
    unsigned char pad_108[0xC];  // zeroed by the constructor
    // bit 0: update is running the components' updates; bit 1: setUpdateComponent's switch
    unsigned int m_updateFlags;
    // whether GfObjUpdate::updateComponent runs the components' updates (GfObjUtil::applyExecUpdate sets it)
    bool m_execUpdate;
};

// the speed each model layer is asked to play at (functions and data, by its symbols)
class GfObjLayerSpeed {
public:
    // a layer's request (the struct and field names are not the original's)
    struct Info {
        Info() : m_request(false), m_speed(1.0f) {}
        bool m_request;  // reqApplyModelLayerSpeed sets it, isRequest reads it
        float m_speed;
    };
    static void initialize();
    static void finalize();
    static void reqApplyModelLayerSpeed(unsigned int layer, float speed);
    static bool isRequest(unsigned int layer);
    static float getSpeed(unsigned int layer);
    static void cleanup();
    static Info s_info[32];
};
}  // namespace gf

#endif
