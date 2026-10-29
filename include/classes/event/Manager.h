#ifndef CLASSES_EVENT_MANAGER_H
#define CLASSES_EVENT_MANAGER_H

#include "classes/ml/IWorkBackground.h"
#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/IManager.h"

namespace event { class Manager; }
namespace ml { class EventView; class Scn; }

namespace event {
// table 0x7100B3E2F8
class Manager : public ::mm::mtl::PtrSingleton< ::event::Manager>, public ::ml::IWorkEvent, public ::ml::IWorkBackground {
public:
    explicit Manager(ml::Scn* scn);  // 0x7100145A44 (create's)
    virtual ~Manager();  // slot 0
    virtual bool OnKeyDown(ml::EventView*);  // slot 2 (returns false)
    virtual void bkgHomeMenu(bool);  // slot 3
    // the language a scene's text follows (the evt plugin's beginJP/beginUS pass 1/2, endJP/endUS 0); the
    // enumerator names are not the original's
    enum LANGUAGE_MODE : int {
        LANGUAGE_MODE_NONE = 0,
        LANGUAGE_MODE_JP = 1,
        LANGUAGE_MODE_US = 2,
    };
    // the evt script plugin's commands: each returns true when done, false when the script must wait
    bool init(const char* name);
    bool setupScene(const char* name);
    bool setupSceneEnd();
    bool startScene(const char* name, int no);
    bool startPage(const char* name, int no, float frame);
    bool endScene();
    void setLanguageMode(bool enable, LANGUAGE_MODE mode);
    // 0x7100149334; evt_obj.select only queues its command when it returns true
    bool checkLanguageMode() const;
    // GfGameEvent and GfGameTalk::play ask it: DebugManager's play-once debug flag
    bool isDebugPlayOnetime() const;
    bool end();  // returns whether an event was playing
    // GfGameEvent's: initialize creates it on its scene when there is none, finalize destroys it
    static Manager* create(ml::Scn* scn);  // returns the new manager (its callers ignore it)
    static void destroy();
    // GfGameEvent::update runs these three in turn, postUpdate runs post
    void update();
    void tail();
    void render();
    void post();
    void stop();  // GfGameEvent::stop's
    void finishNewGameWait();  // GfGameEvent::finishNewGameWait's
    bool isPlaying() const { return m_playing; }
    // sends msg to every manager in turn; the name is not the original's (no symbol: inline everywhere)
    void sendMessage(event::MSG_TYPE msg) {
        for (unsigned int i = 0; i < m_managers.size(); i++) {
            m_managers[i]->OnEventProc(msg);
        }
    }

    unsigned int m_playing : 1;  // end and stop act only while it is set; GfGameTalk::isPlaying returns it
    unsigned int pad_18_1 : 31;  // the rest of the word, which isPlaying loads whole
    // bit 0: tail sends messages 18 and 19 (else only 19); bit 1: setupSceneEnd sent message 6 and waits for the
    // SeqManager; bit 5: end sent message 11 (the name is not the original's)
    unsigned int m_flags;  // 0x1c
    // the managers each message goes to, in order (the name is not the original's)
    mm::mtl::FixedVector<IManager*, 64> m_managers;  // 0x20
    ml::Scn* m_scn;  // 0x228 the constructor's argument; BouManager::clear reaches the view through it (the name is not the original's)
    unsigned char pad_230[0x254 - 0x230];
    // the scene name setupScene/startScene copy their name argument into (evt_setup's setSeamlessReadPos/Axis pass
    // it to SeamlessManager::addFirstSeamPoint); the name is not the original's
    mm::mtl::FixStr<32> m_sceneName;  // 0x254
    unsigned char pad_278[0x294 - 0x278];
    // nonzero: GfEvtModelDriver's constructor then moves its init parameter in the theater; not known yet
    unsigned int pad_294;
    unsigned char pad_298[0x2B4 - 0x298];
    // set by setLanguageMode (NONE when disabled), tested by checkLanguageMode; the name is not the original's
    LANGUAGE_MODE m_languageMode;  // 0x2b4
    unsigned char pad_2b8[0x2C0 - 0x2B8];  // create allocates 0x2C0 bytes
};
}  // namespace event

#endif
