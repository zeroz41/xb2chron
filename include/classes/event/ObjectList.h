#ifndef CLASSES_EVENT_OBJECTLIST_H
#define CLASSES_EVENT_OBJECTLIST_H

#include "mm/mtl/FixStr.h"
namespace event { class Object; }

namespace event {
// table 0x7100B3E0F8
class ObjectList {
public:
    virtual ~ObjectList();  // slot 0
    // makes the object at the given path active (ScriptSetActive::doit tail-calls it)
    void setActivePath(const char* path);

    // each calls the object's virtual (clear, start, end, update, render, tail, isLoading), then recurses into its
    // children (1.0.0's names)
    void clearSub(Object* obj);
    void startSceneSub(Object* obj);
    void endSceneSub(Object* obj);
    void updateSub(Object* obj);
    // renders a loading object greyed out (0.5 each), others white at half alpha
    void renderSub(Object* obj);
    void tailSub(Object* obj);
    bool isLoadingSub(Object* obj) const;
    // the object below obj (obj included) with that name, else null (static: the original passes obj in x0)
    static Object* searchByNameSub(Object* obj, const char* name);
    Object* createCamera(const char* name, unsigned int id);
    Object* createEffect(const char* name);
    Object* createLight(const char* name, unsigned int id);
    // 1.0.0's constructor zeroes it, then stores its second argument (bool) in bit 0; the name is not the original's
    unsigned int m_flags;  // 0x8
    mm::mtl::FixStr<64> m_name;  // 0xc; 1.0.0's constructor copies its first argument in
    // the tree the constructor builds: a root object with four category objects below it (searchByName never
    // returns these five); the names are not the original's
    Object* m_root;  // 0x50
    // the four category objects (ObjectManager::getChara indexes the children of the first); the name is not the
    // original's
    Object* m_categories[4];  // 0x58
    // the object the script commands act on (ScriptSetActive's doit sets it); the name is not the original's
    Object* m_active;  // 0x78
};
}  // namespace event

#endif
