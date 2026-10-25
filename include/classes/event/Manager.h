#ifndef CLASSES_EVENT_MANAGER_H
#define CLASSES_EVENT_MANAGER_H

#include "classes/ml/IWorkBackground.h"
#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace event { class Manager; }
namespace ml { class EventView; class Scn; }

namespace event {
// table 0x7100B3E2F8
class Manager : public ::mm::mtl::PtrSingleton< ::event::Manager>, public ::ml::IWorkEvent, public ::ml::IWorkBackground {
public:
    virtual ~Manager();  // slot 0
    virtual void OnKeyDown(ml::EventView*);  // slot 2
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
    bool end();  // returns whether an event was playing
    // GfGameEvent's: initialize creates it on its scene when there is none, finalize destroys it
    static void create(ml::Scn* scn);
    static void destroy();
    // GfGameEvent::update runs these three in turn, postUpdate runs post
    void update();
    void tail();
    void render();
    void post();
    void stop();  // GfGameEvent::stop's
    void finishNewGameWait();  // GfGameEvent::finishNewGameWait's
    bool isPlaying() const { return m_playing; }

    unsigned int m_playing : 1;  // end and stop act only while it is set; GfGameTalk::isPlaying returns it
    unsigned int pad_18_1 : 31;  // the rest of the word, which isPlaying loads whole
    unsigned char pad_1c[0x294 - 0x1C];
    // nonzero: GfEvtModelDriver's constructor then moves its init parameter in the theater; not known yet
    unsigned int pad_294;
};
}  // namespace event

#endif
