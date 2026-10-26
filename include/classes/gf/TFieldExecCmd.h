#ifndef CLASSES_GF_TFIELDEXECCMD_H
#define CLASSES_GF_TFIELDEXECCMD_H

#include "mm/mtl/FixStr.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table none; a field command an object's animation component (T: GfComAsm, GfComEvtAnim) executes: the mob, NPC and
// enemy states hold one and start it with the command name FLD_NpcMobMotionId's "cmdName" column gives
// (create, update, execCmd: StateFieldWalk's unit). The field names are not the original's.
template <typename T>
class TFieldExecCmd {
public:
    // what create takes: the object, the command and how long it may take to start
    struct CreateInfo {
        CreateInfo() : handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), timeout(5.0f) {}
        // the object and a command named at run time (StateReaction::beginReaction: a BDAT cell)
        CreateInfo(GF_OBJ_HANDLE* handle_, const char* name, float timeout_ = 5.0f)
            : handle(handle_), cmdName(name), timeout(timeout_) {}
        GF_OBJ_HANDLE* handle;
        mm::mtl::FixStr<32> cmdName;
        float timeout;
    };

    TFieldExecCmd() : m_time(0.0f), m_done(false), m_executed(false) {}
    ~TFieldExecCmd() {
        m_executed = false;
        clear();
    }
    // forgets the command (inline: create, update and the states' destructors inline it)
    void clear() {
        m_done = false;
        m_time = 0.0f;
        m_info = CreateInfo();
    }
    void create(const CreateInfo& info);
    void update(float dt);
    bool execCmd(T& com, const char* name) const;

    CreateInfo m_info;
    float m_time;     // time since create (update adds dt)
    bool m_done;      // update stops once the command ran
    bool m_executed;  // whether this update ran the command
};
}  // namespace gf

#endif
