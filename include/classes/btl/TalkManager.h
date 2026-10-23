#ifndef CLASSES_BTL_TALKMANAGER_H
#define CLASSES_BTL_TALKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class TalkManager; }

namespace btl {
// table 0x7100B3BDE8
class TalkManager : public ::mm::mtl::PtrSingleton< ::btl::TalkManager> {
public:
    enum NARRATION_TYPE : int;
    void PlayNarrationVoice(NARRATION_TYPE type, int, int);
    virtual ~TalkManager();  // slot 0
    static void Create();
    static void Destroy();
};
}  // namespace btl

#endif
