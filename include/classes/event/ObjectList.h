#ifndef CLASSES_EVENT_OBJECTLIST_H
#define CLASSES_EVENT_OBJECTLIST_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
namespace event { class Object; }
namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3E0F8
class ObjectList {
public:
    // 0x7100127994 (1.0.0's ObjectList(const char*, bool)): ObjectManager::createScene passes m_flags bit 0
    ObjectList(const char* name, bool flag);
    virtual ~ObjectList();  // slot 0
    // empties the effect category (ObjectManager::OnEventProc)
    void startPage();
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
    // 1.0.0's names (0x710011C018, 0x710011C0C4; 3.0.1 inlines them): whether an effect of the list is alive,
    // and stop every effect (category 2 holds the ObjectEffects)
    inline bool isUsingEffect();
    inline void stopEffect();
    // the object below obj (obj included) with that name, else null (static: the original passes obj in x0)
    static Object* searchByNameSub(Object* obj, const char* name);
    // a character object for an existing gf object, added to category 0
    Object* createGfObj(const char* name, gf::GF_OBJ_HANDLE* handle);
    // the driver (blade) of the event party whose blade (driver) has that bdat id, else the party leader driver
    // (getDriverByBlade) / -1 (getBladeByDriver)
    gf::GF_OBJ_HANDLE* getDriverByBlade(unsigned int bladeId);
    gf::GF_OBJ_HANDLE* getBladeByDriver(unsigned int driverId);
    // the id-th object of the camera (light) category, created when the category holds fewer
    Object* createCamera(const char* name, unsigned int id);
    Object* createEffect(const char* name);
    Object* createLight(const char* name, unsigned int id);
    // appends the bdat id of every character object whose gf object has that type (clears the list first unless
    // append is set)
    void listupObject(mm::mtl::FixedVector<unsigned int, 256>& list, unsigned int type, bool append);
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
    // zeroed with m_active by the destructor; the gf object creators store the new object here while it is null
    Object* pad_80;  // 0x80
    // how many objects each category holds: the creators count up (createGfObjPcByWalkID: [0]), startPage and the
    // destructor zero them while emptying the category; the name is not the original's
    unsigned int m_counts[4];  // 0x88 (sizeof 0x98: ObjectManager::createScene allocates 0x98)
};
}  // namespace event

#endif
