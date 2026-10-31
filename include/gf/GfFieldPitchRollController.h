#ifndef GF_GFFIELDPITCHROLLCONTROLLER_H
#define GF_GFFIELDPITCHROLLCONTROLLER_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gmk { class GmkRouteNavi; }

namespace gf {
// no table: tilts an object (pitch and roll) along a route navigation, run as a sequence of member functions
// (seqInit, then seqUpdate); the field names are not the original's
class GfFieldPitchRollController {
public:
    struct CreateInfo {
        CreateInfo() : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_8(true), pad_9(true), pad_a(true) {}
        GF_OBJ_HANDLE* m_handle;  // -1 without one
        bool pad_8;
        bool pad_9;
        bool pad_a;
    };
    typedef void (GfFieldPitchRollController::*Seq)(const gmk::GmkRouteNavi& navi);

    explicit GfFieldPitchRollController(const CreateInfo* info);
    // inline: GfBehaviorEnemyField's destructor disposes it in place
    ~GfFieldPitchRollController() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(const gmk::GmkRouteNavi& navi);
    void seqInit(const gmk::GmkRouteNavi& navi);
    void seqUpdate(const gmk::GmkRouteNavi& navi);

    CreateInfo m_info;
    void* pad_10;
    Seq m_seq;  // the step update runs; create starts it at seqInit
    unsigned long pad_28;
    unsigned short pad_30;
    unsigned char pad_32[0x6];
};
}  // namespace gf

#endif
