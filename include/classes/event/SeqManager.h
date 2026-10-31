#ifndef CLASSES_EVENT_SEQMANAGER_H
#define CLASSES_EVENT_SEQMANAGER_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/CmdQueue.h"
#include "classes/event/ICmd.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; class Object; }

namespace event {
// table 0x7100B3E238; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::SeqManager>
// Singleton<SeqManager>::getPtr builds it in place (the constructor is inline, 1.0.0 had it out of line at
// 0x7100131134): one instance of every sequence state, the command queue, then the fields below.
class SeqManager : public IManager, public mm::mtl::Singleton<SeqManager> {
public:
    // table 0x7100B3EB50
    class play_start : public ::event::ICmd {
    public:
        virtual ~play_start() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EB88
    class play_next : public ::event::ICmd {
    public:
        virtual ~play_next() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EBC0
    class start : public ::event::ICmd {
    public:
        virtual ~start() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EBF8
    class start_fadeout : public ::event::ICmd {
    public:
        virtual ~start_fadeout() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EC30
    class start_areajump : public ::event::ICmd {
    public:
        virtual ~start_areajump() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
        unsigned char pad_8[0x8];
    };
    // table 0x7100B3EC68
    class start_notice : public ::event::ICmd {
    public:
        virtual ~start_notice() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3E920
    class start_loading : public ::event::ICmd {
    public:
        start_loading() : pad_8(0) {}
        virtual ~start_loading() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
        unsigned char pad_8;
    };
    // table 0x7100B3ECA0
    class start_other : public ::event::ICmd {
    public:
        virtual ~start_other() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
        // the objects update creates (createGfObjPcByWalkID's results); the name is not the original's
        mm::mtl::FixedVector<Object*, 8> m_objs;
    };
    // table 0x7100B3ECD8
    class start_form : public ::event::ICmd {
    public:
        virtual ~start_form() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3ED10
    class start_change : public ::event::ICmd {
    public:
        virtual ~start_change() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3ED48
    class start_env_seam : public ::event::ICmd {
    public:
        virtual ~start_env_seam() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3ED80
    class start_weather : public ::event::ICmd {
    public:
        virtual ~start_weather() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3E958
    class start_streaming0 : public ::event::ICmd {
    public:
        virtual ~start_streaming0() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3E990
    class start_capture_wait : public ::event::ICmd {
    public:
        virtual ~start_capture_wait() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3E9C8
    class start_streaming1 : public ::event::ICmd {
    public:
        virtual ~start_streaming1() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EA00
    class exec : public ::event::ICmd {
    public:
        exec() : pad_8(0), pad_9(0), pad_a(0), pad_c(0), pad_18(0) {}
        virtual ~exec() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
        unsigned char pad_8;  // SeqManager::OnEventProc sets it (msg 9) with a byte store
        unsigned char pad_9;
        unsigned char pad_a;
        unsigned int pad_c;
        unsigned char pad_10[0x8];
        unsigned int pad_18;
    };
    // table 0x7100B3EA38
    class exec_fadeout : public ::event::ICmd {
    public:
        virtual ~exec_fadeout() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EA70
    class exec_grass : public ::event::ICmd {
    public:
        virtual ~exec_grass() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EDB8
    class end_change : public ::event::ICmd {
    public:
        virtual ~end_change() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
        unsigned char pad_8[0x8];
    };
    // table 0x7100B3EAA8
    class end_eff : public ::event::ICmd {
    public:
        virtual ~end_eff() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EAE0
    class end_stream : public ::event::ICmd {
    public:
        virtual ~end_stream() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EB18
    class end_wait : public ::event::ICmd {
    public:
        end_wait() : pad_8(0), pad_c(0) {}
        virtual ~end_wait() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
        unsigned char pad_8;
        unsigned int pad_c;
    };
    // table 0x7100B3EDF0
    class end_areajump : public ::event::ICmd {
    public:
        virtual ~end_areajump() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
        unsigned char pad_8[0x8];
    };
    // table 0x7100B3EE28
    class end_env_seam : public ::event::ICmd {
    public:
        virtual ~end_env_seam() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EE60
    class end_fadewait : public ::event::ICmd {
    public:
        virtual ~end_fadewait() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EE98
    class end_fadein : public ::event::ICmd {
    public:
        virtual ~end_fadein() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EED0
    class end_notice : public ::event::ICmd {
    public:
        virtual ~end_notice() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    // table 0x7100B3EF08
    class end : public ::event::ICmd {
    public:
        virtual ~end() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
        virtual bool update(event::ICmd::Param const&);  // slot 3
    };
    SeqManager() : m_flags(0), m_dispFlags(0), pad_2718(0), pad_2760(0), pad_2764(0), pad_2768(0), pad_276c(0), pad_2770(""), pad_2778(0), pad_277c(0), pad_2780(""), pad_2788(0), pad_278c(0), pad_2790(0), pad_2794(0), pad_2798(0), pad_279c(0), pad_27a0(0), pad_27a8(0), pad_27b0(0), pad_27b4(0), pad_27b8(0), pad_27bc(0), pad_27c0(0), pad_27c8(0), pad_27d0(0), pad_27d8(1), pad_27d9(0), pad_27da(0), pad_27db(0), pad_27dc(0), pad_27dd(0), pad_27e4(0), pad_27e8(0), pad_27f0(0), pad_27f8(0), pad_2800(0), pad_2808(0), pad_280c(0), pad_2810(0), pad_2814(0), pad_2818(0), pad_2820(""), pad_2830(0), pad_2838(0), pad_2840(0), pad_2848(0) {}
    // inline: its D2/D0 are in the unit's inline tail (0x710014A6F4); OnEventProc is the key function
    virtual ~SeqManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    play_start m_playStart;  // 0x10 (the name is not the original's)
    play_next m_playNext;  // 0x18 (the name is not the original's)
    start m_start;  // 0x20 (the name is not the original's)
    start_fadeout m_startFadeout;  // 0x28 (the name is not the original's)
    start_areajump m_startAreajump;  // 0x30 (the name is not the original's)
    start_notice m_startNotice;  // 0x40 (the name is not the original's)
    start_loading m_startLoading;  // 0x48 (the name is not the original's)
    start_other m_startOther;  // 0x58 (the name is not the original's)
    start_form m_startForm;  // 0xA8 (the name is not the original's)
    start_change m_startChange;  // 0xB0 (the name is not the original's)
    start_env_seam m_startEnvSeam;  // 0xB8 (the name is not the original's)
    start_weather m_startWeather;  // 0xC0 (the name is not the original's)
    start_streaming0 m_startStreaming0;  // 0xC8 (the name is not the original's)
    start_capture_wait m_startCaptureWait;  // 0xD0 (the name is not the original's)
    start_streaming1 m_startStreaming1;  // 0xD8 (the name is not the original's)
    exec m_exec;  // 0xE0 (the name is not the original's)
    exec_fadeout m_execFadeout;  // 0x100 (the name is not the original's)
    exec_grass m_execGrass;  // 0x108 (the name is not the original's)
    end_change m_endChange;  // 0x110 (the name is not the original's)
    end_eff m_endEff;  // 0x120 (the name is not the original's)
    end_stream m_endStream;  // 0x128 (the name is not the original's)
    end_wait m_endWait;  // 0x130 (the name is not the original's)
    end_areajump m_endAreajump;  // 0x140 (the name is not the original's)
    end_env_seam m_endEnvSeam;  // 0x150 (the name is not the original's)
    end_fadewait m_endFadewait;  // 0x158 (the name is not the original's)
    end_fadein m_endFadein;  // 0x160 (the name is not the original's)
    end_notice m_endNotice;  // 0x168 (the name is not the original's)
    end m_end;  // 0x170 (the name is not the original's)
    unsigned int m_flags;  // 0x178: cleared by clear(); end sets bit 1 (the name is not the original's)
    unsigned int m_dispFlags;  // 0x17C: setDisp/isDisp's bit 0 (1.0.0; the name is not the original's)
    mm::mtl::FixStr<128> m_seqName;  // 0x180: the running state's name (each state's update sets it; the name is not the original's)
    CmdQueue<32, 0> m_cmdQueue;  // 0x208 (the name is not the original's)
    unsigned char pad_2718;  // 0x2718
    mm::mtl::FixStr<64> pad_271c;  // 0x271C
    unsigned int pad_2760;  // 0x2760
    unsigned int pad_2764;  // 0x2764
    unsigned int pad_2768;  // 0x2768
    int pad_276c;  // 0x276C (ObjectCamera::OnBouRender compares it signed: < 3)
    const char* pad_2770;  // 0x2770
    unsigned char pad_2778;  // 0x2778
    unsigned int pad_277c;  // 0x277C
    const char* pad_2780;  // 0x2780
    unsigned char pad_2788;  // 0x2788
    unsigned int pad_278c;  // 0x278C
    unsigned char pad_2790;  // 0x2790
    unsigned int pad_2794;  // 0x2794
    unsigned int pad_2798;  // 0x2798
    unsigned char pad_279c;  // 0x279C
    unsigned long pad_27a0;  // 0x27A0
    unsigned long pad_27a8;  // 0x27A8
    unsigned char pad_27b0;  // 0x27B0
    unsigned int pad_27b4;  // 0x27B4
    unsigned int pad_27b8;  // 0x27B8
    unsigned char pad_27bc;  // 0x27BC
    unsigned long pad_27c0;  // 0x27C0
    unsigned long pad_27c8;  // 0x27C8
    unsigned long pad_27d0;  // 0x27D0
    unsigned char pad_27d8;  // 0x27D8
    unsigned char pad_27d9;  // 0x27D9
    unsigned char pad_27da;  // 0x27DA
    unsigned char pad_27db;  // 0x27DB
    unsigned char pad_27dc;  // 0x27DC
    unsigned char pad_27dd;  // 0x27DD
    unsigned char pad_27de[0x6];  // 0x27DE
    unsigned char pad_27e4;  // 0x27E4
    unsigned long pad_27e8;  // 0x27E8
    unsigned long pad_27f0;  // 0x27F0
    unsigned long pad_27f8;  // 0x27F8
    unsigned long pad_2800;  // 0x2800
    unsigned char pad_2808;  // 0x2808
    unsigned int pad_280c;  // 0x280C
    unsigned int pad_2810;  // 0x2810
    unsigned int pad_2814;  // 0x2814
    unsigned int pad_2818;  // 0x2818
    unsigned char pad_281c[0x4];  // 0x281C
    const char* pad_2820;  // 0x2820
    unsigned char pad_2828[0x8];  // 0x2828
    unsigned long pad_2830;  // 0x2830
    unsigned long pad_2838;  // 0x2838
    unsigned long pad_2840;  // 0x2840
    unsigned int pad_2848;  // 0x2848
    unsigned char pad_284c[0x14];  // 0x284C
    unsigned int pad_2860;  // 0x2860: login sets it to 1 (the instance ends at 0x2868, where getPtr's guard is)
    // 1.0.0's out-of-line SeqManager::login/logout/clear (0x710013145C, 0x7100131494, 0x7100131404); 3.0.1 inlines
    // them in OnEventProc
    inline void login();
    inline void logout();
    inline void clear();
    void init();
    void setupScene();
    void startScene();
    void render();
    void end();
};
}  // namespace event

#endif
