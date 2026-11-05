#ifndef CLASSES_GF_GFGAMEOBJ_H
#define CLASSES_GF_GFGAMEOBJ_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedVector.h"
#include "gf/GFATTACH.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameObj; }
namespace gf { class GfGameObjEnemy; }
namespace gf { class GfObj; }
namespace gf { class GfObjAcc; }
namespace gf { class GfSetupParam; }
#include "classes/gf/IGfObjListener.h"

namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }
namespace gf {
// a message GfGameObj queues for an object (FixedList<gf::ObjMsg, 256>::erase is this unit's; 16 bytes, 8-aligned:
// the list's nodes are 24 bytes)
struct ObjMsg {
    // destroyGameObjWithAttribute queues the object and its attribute (the names are not the original's)
    GF_OBJ_HANDLE* m_handle;
    unsigned int m_attr;
};

// table 0x7100B550B8 (0x55C78 bytes, GfGameObj::build): the game's objects by type, and the ones entering and
// leaving the game; it hears the object manager's events through its IGfObjListener base (the constructor
// registers it, the destructor removes it)
class GfGameObj : public ::mm::mtl::PtrSingleton< ::gf::GfGameObj>, public IGfObjListener {
public:
    // an object entering (addInObj) or leaving the game, and its fade (24 bytes)
    struct INOUT {
        INOUT(GF_OBJ_HANDLE* handle, float fadeTime, float alpha)
            : m_handle(handle), m_fadeTime(fadeTime), m_alpha(alpha), pad_14(false), pad_15(true), pad_16(false) {}

        GF_OBJ_HANDLE* m_handle;
        float m_fadeTime;  // addInObj's time (the name is not the original's)
        float pad_c;
        float m_alpha;  // the object's life alpha when it was added (the name is not the original's)
        bool pad_14;
        bool pad_15;
        bool pad_16;
    };
    typedef mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024> ObjList;  // the name is not the original's

    GfGameObj(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    void initialize(const GfSetupParam& param);
    static void destroy();
    // the enter/leave fades, the search lists, the enemies, the first stale message, then the camera fades
    static void update(const fw::UpdateInfo& info);
    void updateEnterLeaveObj(const fw::UpdateInfo& info);  // the in and out lists' fades
    // a list's objects too near the camera (or not at full alpha) recalculate their camera alpha
    void calcCameraFade(const ObjList& list, const mm::Vec3& camPos);
    // SCOM_DESTROY_GAME_OBJ passes its request's object, time and attribute
    static void destroyGameObjWithAttribute(gf::GF_OBJ_HANDLE* handle, float fadeTime, unsigned int);
    int getObjNumberByEnArrangeId(unsigned int arrangeId);  // the live objects of an enemy arrange id
    static void postUpdate(const fw::UpdateInfo& info);
    void updateObjectProperty();
    static void bdatReload();
    virtual ~GfGameObj();  // slot 0
    static bool isEmpty();
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    void addInObj(GF_OBJ_HANDLE* handle, float fadeTime);
    // false when the object is not faded out but must be destroyed at once (destroyGameObj)
    bool addOutObj(GF_OBJ_HANDLE* handle, float fadeTime, bool);
    void removeGameObj(GF_OBJ_HANDLE* handle);
    // the object joins its type's list (always true)
    bool addGameObj(GF_OBJ_HANDLE* handle);
    // on: the object is in the game (flag 14, collision, components) and joins the entered list, else the left one
    void enableGameObj(GfObjAcc& acc, bool on);
    // the list of a type's objects (5: the enemies', or the enemy blades' when handle is one)
    ObjList* getListType(unsigned int kind, GF_OBJ_HANDLE* handle);
    static ObjList* getListEnemyBlade();
    void flushEvent();
    // an in/out entry's step: true when the faded-out object left the game (rebuilt or destroyed)
    bool fadeoutGameObj(INOUT& inout, GfObjAcc& acc, const fw::UpdateInfo& info);
    void setupEffectFadeout(INOUT& inout, GfObjAcc& acc, const fw::UpdateInfo& info);
    void checkEnableGameObj(INOUT& inout, GfObjAcc& acc);
    void setupForLoopEffect(GfObjAcc& acc);
    // whether the object behind handle exists (with checkLoad, also loaded); error takes a reason when given
    static bool isValidGameObj(gf::GF_OBJ_HANDLE* handle, bool checkLoad, mm::mtl::FixStr<128>* error);
    static bool isEnterGameObj(gf::GF_OBJ_HANDLE* handle);
    static void setupEnterGameObj(GF_OBJ_HANDLE* handle, float fadeTime);
    static void setupEnterGameObjMount(GF_OBJ_HANDLE* handle, GFATTACH attach, float fadeTime);
    static void setupLeaveGameObj(GF_OBJ_HANDLE* handle, float fadeTime);
    static void setupLeaveGameObjMount(GF_OBJ_HANDLE* handle, GFATTACH attach, float fadeTime);
    static void enterStayObject(GF_OBJ_HANDLE* handle);
    static void enterStayObjectMount(GF_OBJ_HANDLE* handle, GFATTACH attach);
    static void enterStayObjectWithVolumeFade(GF_OBJ_HANDLE* handle);
    static void enterStayObjectMountWithVolumeFade(GF_OBJ_HANDLE* handle, GFATTACH attach);
    static void destroyGameObj(gf::GF_OBJ_HANDLE* handle, float fadeTime);
    static bool isDestroyGameObj(gf::GF_OBJ_HANDLE* handle);
    static GfObj* getObj(GF_OBJ_HANDLE* handle);
    static mm::mtl::FixedList<gf::GF_OBJ_HANDLE*, 1024>* getList(unsigned int kind);
    // a type's objects appended to out (as getList(kind) picks the list); nothing without an instance
    static void getList(mm::mtl::FixedVector<GF_OBJ_HANDLE*, 1024>& out, unsigned int kind);

    // the objects by type, as getListType picks them (the names are not the original's)
    ObjList m_listDriver;       // type 3
    ObjList m_listBlade;        // type 4
    ObjList m_listEnemy;        // type 5
    ObjList m_listEnemyBlade;   // type 5, the enemy blades (getListEnemyBlade)
    ObjList m_listType6;
    ObjList m_listType7;
    ObjList m_listType8;
    ObjList m_listType9;
    ObjList m_listType10;
    ObjList m_listType0;        // types 0 and 14
    ObjList m_listType12;
    ObjList m_listType11;
    ObjList m_listType13;
    ObjList m_listOther;        // every other type
    mm::mtl::FixedList<INOUT, 1024> m_inList;  // addInObj's (the name is not the original's)
    mm::mtl::FixedList<INOUT, 1024> m_outList;  // the name is not the original's
    // the objects that entered / left since flushEvent last told the events (the names are not the original's)
    mm::mtl::FixedVector<GF_OBJ_HANDLE*, 1024> m_enterObjs;
    mm::mtl::FixedVector<GF_OBJ_HANDLE*, 1024> m_leaveObjs;
    mm::mtl::FixedList<ObjMsg, 256> m_msgs;  // the name is not the original's
    GfGameObjEnemy* m_enemy;  // flushEvent tells it the enemies entering and leaving (the name is not the original's)
    bool pad_55c70;
};
}  // namespace gf

#endif
