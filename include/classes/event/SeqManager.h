#ifndef CLASSES_EVENT_SEQMANAGER_H
#define CLASSES_EVENT_SEQMANAGER_H

#include "mm/mtl/FixStr.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3E238; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::SeqManager>
class SeqManager : public IManager, public mm::mtl::Singleton<SeqManager> {
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
    unsigned char pad_10[0x168];
    unsigned int m_flags;  // 0x178: cleared by clear(); end sets bit 1 (the name is not the original's)
    unsigned int m_dispFlags;  // 0x17C: setDisp/isDisp's bit 0 (1.0.0; the name is not the original's)
    mm::mtl::FixStr<128> m_seqName;  // 0x180: the running state's name (each state's update sets it; the name is not the original's)
};
}  // namespace event

#endif
