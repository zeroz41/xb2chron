#ifndef CLASSES_EVENT_OBJECTMANAGER_H
#define CLASSES_EVENT_OBJECTMANAGER_H

#include "classes/mm/mtl/Singleton.h"
#include "classes/event/Object.h"
#include "classes/event/ObjectList.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/IManager.h"

namespace event { enum MSG_TYPE : int; enum CHARA_TYPE : int; class ObjectChara; }

namespace event {
// table 0x7100B3E118; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::ObjectManager>; the instance is
// mm::mtl::Singleton<event::ObjectManager>::getPtr's static
class ObjectManager : public IManager, public mm::mtl::Singleton<ObjectManager> {
public:
    // out of line (0x710012A11C; 1.0.0 0x710011C8C0): the evt_setup plugin's Singleton<ObjectManager>::getPtr calls it; the event unit
    // that defines it (application/BF2/CharaObj) inlines it into its own getPtr
    ObjectManager();
    virtual ~ObjectManager();  // slot 0
    // each creates an event::ObjectChara (createGfObjTalk: new ObjectChara(name)) and links it in; called by the
    // evt_setup script plugin (application/BF2/ScriptPlayText), names from 1.0.0's symbols
    event::Object* createGfObjTalk(const char* name);
    event::Object* createGfObjPcByWalkID(const char* name, unsigned int walkId, unsigned int);
    event::Object* createGfObjPcByBladeID(const char* name, unsigned int bladeId, unsigned int);
    event::Object* createGfObjBlByWalkID(const char* name, unsigned int walkId, unsigned int);
    event::Object* createGfObjBladeByPcID(const char* name, unsigned int pcId, unsigned int);
    event::Object* createGfObj(const char* name, event::CHARA_TYPE type, unsigned int id, unsigned int, unsigned int);
    event::Object* createGfObjPartyIn(const char* name, event::CHARA_TYPE type, unsigned int id, unsigned int, unsigned int);
    event::Object* createModel(const char* name, const char* model, unsigned int, unsigned int);
    event::Object* createCamera(const char* name, unsigned int id);
    event::Object* createEffect(const char* name);
    event::Object* createLight(const char* name, unsigned int id);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // the object of the current scene with that name, else null (the evt_chara script commands test its m_type)
    Object* searchByName(const char* name);
    // the object of the given type (Object::m_type) and id, else null (evt_chara's setWeaponDispByBladeID passes
    // type 3 and GfDataBlade::getCreator's result)
    Object* searchByID(unsigned int type, unsigned int id);
    // a character object (evt_eff.play reads its m_chara)
    ObjectChara* getChara(unsigned int id);
    // the current scene's active object when it is of the given type (Object::m_type), else null; the current
    // scene is not updated first (the script commands' undo and redo inline it); the name is not the original's
    Object* getActive(int type) const {
        if (m_current != 0) {
            Object* obj = m_current->m_active;
            if (obj != 0 && obj->m_type == type) {
                return obj;
            }
        }
        return 0;
    }

    // makes the scene named m_sceneName current (ScriptSetActive calls it before reading m_current)
    void updateCurrent();
    // the scene named name, else null (1.0.0's searchScene 0x710011DC28; 3.0.1 inlines it into updateCurrent)
    ObjectList* searchScene(const char* name) const {
        for (unsigned long i = 0; i < m_scenes.size(); i++) {
            if (strcmp(name, m_scenes[i]->m_name.m_str) == 0) {
                return m_scenes[i];
            }
        }
        return nullptr;
    }
    // 1.0.0's isDisp (0x7100111004; 3.0.1 inlines it: render)
    bool isDisp() const { return m_dispFlags & 1; }
    // renders the current scene when anything is shown (OnEventProc)
    void render();
    // 1.0.0's init, clear, setupScene, startScene, startPage, endScene, update, tail (0x710011CAC0..0x710011CFE8);
    // 3.0.1 inlines them into OnEventProc (defined inline in CharaObj.cpp)
    inline void init();
    inline void clear();
    inline void setupScene();
    inline void startScene();
    inline void startPage();
    inline void endScene();
    inline void update();
    inline void tail();
    // a new scene (an ObjectList named name, m_flags bit 0 passed on), added to m_scenes (1.0.0's name)
    ObjectList* createScene(const char* name);
    // 1.0.0's names (0x710011D99C, 0x710011C900; 3.0.1 inlines them): the current scene's effects alive, and
    // every scene's effects stopped (SeqManager::end_eff)
    inline bool isUsingEffect();
    inline void stopEffect();

    // bit 0 is passed to each new ObjectList (1.0.0's createScene); 1.0.0's setCloneMode(bool) sets it; the name is
    // not the original's
    unsigned int m_flags;  // 0x10
    // bit 0: 1.0.0's setDisp(bool)/isDisp; zeroed with m_flags (one 64-bit store with the second table pointer); the
    // name is not the original's
    unsigned int m_dispFlags;   // 0x14
    // the scenes 1.0.0's createScene adds and updateCurrent searches by name; the name is not the original's
    mm::mtl::FixedVector<ObjectList*, 16> m_scenes;  // 0x18 (size 0x98)
    // the scene updateCurrent makes current ("default" at first); the name is not the original's
    mm::mtl::FixStr<64> m_sceneName;               // 0xa0
    // the name of the current scene (updateCurrent copies m_sceneName here); the name is not the original's
    mm::mtl::FixStr<64> m_currentName;             // 0xe4
    ObjectList* m_current;                         // 0x128 (1.0.0's getCurrent returns it)
};
}  // namespace event

#endif
