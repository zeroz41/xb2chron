#ifndef CLASSES_GF_GFPLAYCOMPLAYERDEAD_H
#define CLASSES_GF_GFPLAYCOMPLAYERDEAD_H
#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/IGfEvent.h"
namespace fw { class UpdateInfo; }
namespace gf { enum GfPlayerDead : int; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }
namespace gf { class GfDeadCamera; }
namespace gf {
// table 0x7100B58728 (the PtrSingleton's at +0x60, IGfEvent's at +0x80): the player's death, from the dead camera to
// the map jump to the landmark (GfPlayFactory::createPlayerDead). The destructor and getFuncName are inline (their
// bodies sit in the unit's tail with the table's thunks); start is the key function
class GfPlayComPlayerDead : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComPlayerDead>, public ::gf::IGfEvent {
public:
    explicit GfPlayComPlayerDead(GfPlayerDead dead)
        : GfPlayCom(0x20, false), m_deadType(dead), m_time(0.0f), m_waitTime(0.0f), m_voiceTime(15.0f),
          m_camera(nullptr), m_mapjumpReq(false), m_mapjumpDone(false), m_eventPlaying(false), m_dead(true) {}
    static GfPlayComPlayerDead* create(GfPlayerDead dead);
    static bool isDead();
    // a running death of another kind becomes kind 4 (GfPlayFactory::createPlayerDead asks first)
    static bool replaceDeadType(GfPlayerDead dead);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComPlayerDead() {}  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComPlayerDead";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    virtual void gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const& info);  // IGfEvent slot 42
    static mm::mtl::RTTI m_rtti;

    // the names below are not the original's
    // switches to the given kind: a dead camera and the death notice to the controlled mover (start and
    // replaceDeadType inline it)
    void setDeadType(GfPlayerDead dead);
    GfPlayerDead m_deadType;
    float m_time;        // update adds the frame time
    float m_waitTime;    // start sets 3 seconds: the time before the jump
    float m_voiceTime;   // 15 seconds a playing voice may delay the jump
    GfDeadCamera* m_camera;
    bool m_mapjumpReq;   // update requested the map jump
    bool m_mapjumpDone;  // gevMapjump's GEV 6
    // GfPlayComEvent::update sets it while its event is still playing
    bool m_eventPlaying;
    bool m_dead;         // isDead's answer; gevMapjump's GEV 4 clears it
};
}  // namespace gf
#endif
