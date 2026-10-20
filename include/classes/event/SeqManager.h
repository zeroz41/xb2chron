#ifndef CLASSES_EVENT_SEQMANAGER_H
#define CLASSES_EVENT_SEQMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::SeqManager no evidence names yet
class TUnk_B3E238 {
public:
    virtual ~TUnk_B3E238();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::SeqManager no evidence names yet
class TUnk_B3E260 {
public:
    virtual ~TUnk_B3E260();
};
// table 0x7100B3E238; base at 0x0 unknown (TUnk_B3E238), base at 0x8 unknown (TUnk_B3E260)
class SeqManager : public TUnk_B3E238, public TUnk_B3E260 {
public:
    class end;
    class end_areajump;
    class end_change;
    class end_eff;
    class end_env_seam;
    class end_fadein;
    class end_fadewait;
    class end_notice;
    class end_stream;
    class end_wait;
    class exec;
    class exec_fadeout;
    class exec_grass;
    class play_next;
    class play_start;
    class start;
    class start_areajump;
    class start_capture_wait;
    class start_change;
    class start_env_seam;
    class start_fadeout;
    class start_form;
    class start_loading;
    class start_notice;
    class start_other;
    class start_streaming0;
    class start_streaming1;
    class start_weather;
    virtual ~SeqManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
