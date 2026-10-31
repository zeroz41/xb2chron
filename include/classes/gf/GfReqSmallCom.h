#ifndef CLASSES_GF_GFREQSMALLCOM_H
#define CLASSES_GF_GFREQSMALLCOM_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"


namespace gf { class GfReqSmallCom; class SCOM; class GF_SCOM_HANDLE; class GF_OBJ_HANDLE; enum SCOM_TYPE : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x710056A3FC, gf_req_scom's unit). A
// free function: its callers (TUnk_B535D0::RuleTable::fn_7100290598, fn_7100290BAC) pass a rule row's id, which it
// does not read. What it does: unless GfGameManager::isStartGame, when fn_71002AC598 holds, item 0x6363 is in the
// item box and the local flag 0x8A09 is set, goes on to request work (not recovered).
void fn_710056A3FC(unsigned int id);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x7100569228, gf_req_scom's unit). A
// free function: it takes nothing and reads no object. What it does: passes fn_7100568E1C a stack list of the two
// strings "670105" and "670106" (count 2). Callers: TUnk_B62AA0::fn_710042537C (when the Hitonowa menu's result
// is closed) and fn_7100447D88.
void fn_7100569228();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x710056B988, gf_req_scom's unit). A
// free function: it reads no object, only its argument. What it does: GfGameVoice::playVoice(6, 0xDC3,
// table 0x7100B6AD58[row][ml::mtRand(4)], CV_PRIO 3) (rows of four const char*). Caller: TUnk_28E618::fn_710028EF70
// with TUnk_28E618::fn_710028E7DC's count.
void fn_710056B988(unsigned int row);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x710056B914, gf_req_scom's unit). A
// free function: it reads only its arguments and PtrSingleton<TUnk_B535D0>'s instance. What it does: when the arena
// exists, sends it MsgUnk_1000034 type 0x12 with a and b in pad_34 / pad_38 and id in pad_3C (recieveMessage).
// Caller: btl::TUnk_B3A9C8::fn_7100025920 (0.0, 0.2 and 0x82 or 0x71, as Ghidra reads the call).
void fn_710056B914(float a, float b, unsigned int id);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x710056B9CC, gf_req_scom's unit). A
// free function: it reads only its arguments. What it does: for the first count handles that are valid drivers of
// BDAT id 1..6 or 9, plays one of two voices (ml::mtRand(2)) from the tables at 0x7100B6ADD8.. (the row picked by
// flag) through GfGameVoice::playVoice. Caller: TUnk_28E618::fn_710028F00C (handles of party drivers 0..2).
void fn_710056B9CC(GF_OBJ_HANDLE* const* handles, unsigned int count, bool flag);

// table 0x7100B6AF20; GfReqManager makes one (0x1B078 bytes, 3.0.1's new) and updates it after its own commands
class GfReqSmallCom : public ::mm::mtl::PtrSingleton< ::gf::GfReqSmallCom> {
public:
    typedef mm::mtl::FixedList<SCOM*, 2048> RequestList;

    GfReqSmallCom();
    virtual ~GfReqSmallCom();  // slot 0
    void update(const fw::UpdateInfo& info);
    bool updateParallel(const fw::UpdateInfo& info);  // runs every parallel request; returns true
    static bool isExistCommand();
    static bool isExistCommandWithoutParallel();  // a request is queued in m_list (the parallel lists not counted)
    static bool isExistCommand(SCOM_TYPE type);  // a request of that type is queued or running
    bool isValid(GF_SCOM_HANDLE* handle);  // the request is still queued or running

    // inline: the create functions queue their request in place, then return its handle
    static unsigned long addRequest(SCOM* request);
    static unsigned long addRequestParallel(SCOM* request);
    // a new request's handle: the next count, never -1 (the name is not the original's)
    unsigned long newHandle() {
        unsigned long handle = m_handleCount++;
        if (handle == static_cast<unsigned long>(-1)) {
            handle = m_handleCount++;
        }
        return handle;
    }

    // the names below are not the original's: addRequest queues to m_list, addRequestParallel to m_parallelList
    // (m_subParallelList while m_isSubParallel is set)
    RequestList m_list;
    RequestList m_parallelList;
    RequestList m_subParallelList;
    unsigned long m_handleCount;
    bool m_isSubParallel;
    unsigned char pad_1B071[0x7];
};
}  // namespace gf

namespace gf {
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions: they fill
// gf/request/gf_req_scom.cpp next to the SCOM_*::create functions, but the requests they make have classes nothing
// names. What they do: without value -1; else they allocate a 0x20-byte request (fn_7100558D28: table
// 0x7100B6AFA0, fn_7100558BAC: table 0x7100B6AF70; the new cites "gf/request/gf_req_scom.cpp"), keep value at 0x1C,
// queue it with a new handle and return the handle. Their only callers are the challenge battle unit's
// TUnk_B3A9C8::fn_7100026CBC / fn_7100026C28 (a BDAT 78 "Score" value) and fn_7100026CF0.
unsigned long fn_7100558D28(int value);
unsigned long fn_7100558BAC(int value);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code at 0x7100558E88, right after
// fn_7100558D28). A free function: it takes no this. What it does: passes value straight to GfWeapon's unit's
// fn_71002DA5E4 (a type-0x10 MsgUnk_1000034 to the arena game mode), with no request. Its one caller is the challenge
// battle unit's fn_7100025920 (an unsigned value it compares with a GfGameManager::fn_71002AC5D8 field).
void fn_7100558E88(unsigned int value);
}  // namespace gf

#endif
