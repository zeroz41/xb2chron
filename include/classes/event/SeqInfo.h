#ifndef CLASSES_EVENT_SEQINFO_H
#define CLASSES_EVENT_SEQINFO_H

#include "mm/mtl/FixStr.h"

class CBdatWrapper;

namespace event {
// the event a sequence plays, read from its EVT_listList seat table (0x138 bytes, no table): SeqManager holds one at
// 0x2718; setup(const char*) / setup(int) look the event up by name or id and hand the seat table and row to
// setup(const CBdatWrapper&, const char*, int), or reset it when no seat has it. The field meanings are not known
// yet (the constructor, SeqManager's inline copy, sets each of them)
struct SeqInfo {
    SeqInfo()
        : pad_0(0), pad_48(0), pad_4c(0), pad_50(0), pad_54(0), pad_58(""), pad_60(0), pad_64(0), pad_68(""),
          pad_70(0), pad_74(0), pad_78(0), pad_7c(0), pad_80(0), pad_84(0), pad_88(0), pad_90(0), pad_98(0),
          pad_9c(0), pad_a0(0), pad_a4(0), pad_a8(0), pad_b0(0), pad_b8(0), pad_c0(1), pad_c1(0), pad_c2(0),
          pad_c3(0), pad_c4(0), pad_c5(0), pad_cc(0), pad_d0(0), pad_d8(0), pad_e0(0), pad_e4(0), pad_e8(0),
          pad_ec(0), pad_f0(0), pad_f4(0), pad_f8(0), pad_fc(0), pad_100(0), pad_108(""), pad_118(0), pad_120(0),
          pad_128(0), pad_130(0) {}

    // the reset setup(const char*) and setup(int) inline when no seat has the event: every field the constructor
    // sets, back to its initial value (the name is not the original's)
    void clear() {
        pad_0 = 0;
        pad_4 = "";
        pad_48 = 0;
        pad_4c = 0;
        pad_50 = 0;
        pad_54 = 0;
        pad_58 = "";
        pad_60 = 0;
        pad_64 = 0;
        pad_68 = "";
        pad_70 = 0;
        pad_74 = 0;
        pad_78 = 0;
        pad_7c = 0;
        pad_80 = 0;
        pad_84 = 0;
        pad_88 = 0;
        pad_90 = 0;
        pad_98 = 0;
        pad_9c = 0;
        pad_a0 = 0;
        pad_a4 = 0;
        pad_a8 = 0;
        pad_b0 = 0;
        pad_b8 = 0;
        pad_c0 = 1;
        pad_c1 = 0;
        pad_c2 = 0;
        pad_c3 = 0;
        pad_c4 = 0;
        pad_c5 = 0;
        pad_cc = 0;
        pad_d0 = 0;
        pad_d8 = 0;
        pad_e0 = 0;
        pad_e4 = 0;
        pad_e8 = 0;
        pad_ec = 0;
        pad_f0 = 0;
        pad_f4 = 0;
        pad_f8 = 0;
        pad_fc = 0;
        pad_100 = 0;
        pad_108 = "";
        pad_118 = 0;
        pad_120 = 0;
        pad_128 = 0;
        pad_130 = 0;
    }
    void setup(const char* name);
    void setup(int id);
    void setup(const CBdatWrapper& seat, const char* name, int id);

    unsigned char pad_0;
    // the event name: SeqManager::checkSkipClear compares it with "qst202609"
    mm::mtl::FixStr<64> pad_4;
    // the event id: SeqManager::checkSkipClear looks it up in EVT_listBf
    int pad_48;
    unsigned int pad_4c;
    unsigned int pad_50;
    // the event kind: SeqManager::render shows "NONE", "TEV", "FEV", "SEV", "CS " or "MOV" for 0..5;
    // ObjectCamera::OnBouRender compares it signed (< 3)
    int pad_54;
    const char* pad_58;
    unsigned char pad_60;
    unsigned int pad_64;
    const char* pad_68;
    unsigned char pad_70;
    unsigned int pad_74;
    unsigned char pad_78;
    int pad_7c;  // start_fadeout converts it to float as a signed int (VolumeSeamless::start)
    unsigned int pad_80;
    unsigned char pad_84;
    unsigned long pad_88;
    unsigned long pad_90;
    unsigned char pad_98;
    unsigned int pad_9c;
    unsigned int pad_a0;
    unsigned char pad_a4;
    unsigned long pad_a8;
    unsigned long pad_b0;
    unsigned long pad_b8;
    unsigned char pad_c0;
    unsigned char pad_c1;
    unsigned char pad_c2;
    unsigned char pad_c3;
    unsigned char pad_c4;
    unsigned char pad_c5;
    unsigned char pad_c6[0x6];
    unsigned char pad_cc;
    unsigned long pad_d0;
    unsigned long pad_d8;
    unsigned int pad_e0;
    // SeqManager::checkSkipClear's tests: pad_e4 (an EVT_listBf event), pad_ec (theater mode) and pad_e8 must be 0
    int pad_e4;
    int pad_e8;
    int pad_ec;
    unsigned char pad_f0;
    unsigned int pad_f4;
    unsigned int pad_f8;
    unsigned int pad_fc;
    unsigned int pad_100;
    unsigned char pad_104[0x4];
    const char* pad_108;
    unsigned char pad_110[0x8];
    unsigned long pad_118;
    unsigned long pad_120;
    unsigned long pad_128;
    unsigned int pad_130;
    unsigned char pad_134[0x4];
};
}  // namespace event

#endif
