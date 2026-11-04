#ifndef CLASSES_UI_UIGROUP_H
#define CLASSES_UI_UIGROUP_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/Vector.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIInputLayer; }
namespace ui { class UIObject; }
namespace ui { class UIObjectList; }
namespace ui { class UIResource; }

namespace ui {
// table 0x7100B75658; a group of root objects in a UIObjectList of its own, with the input layers attached to them.
// The field names are not the original's.
class UIGroup {
public:
    // a root object registObject listed (0x60 bytes)
    struct RootObjInfo {
        mm::mtl::FixStr<64> m_name;    // registObject's name
        unsigned int m_handle;         // the object's (UIObjectList::regist's); updateObject clears it on release
        unsigned short m_layer;        // registObject's; isActiveLayer and isAssignedLayer compare it
        UIResource* m_resource;        // registObject's, referenced while listed
        unsigned short m_releaseWait;  // updates left before the entry goes, once the object is released
        bool m_terminate;              // terminateObject's and terminateObjectAll's: the object is terminating
        bool m_release;                // the terminated object is released (terminateObject's flag, releaseObject's)
        bool m_disp;                   // applyObject's: the object's display flag while the group hides it
    };
    // an input layer attachInput registered for a root object (0x10 bytes)
    struct InputInfo {
        UIInputLayer* m_layer;     // referenced while attached
        unsigned int m_input;      // UIInputManager::registInputLayer's handle; 0 while suspended
        unsigned int m_handle;     // the root object's
    };

    UIGroup();
    virtual ~UIGroup();  // slot 0
    void clean();
    void setup(unsigned int count);
    void releaseInput(unsigned int handle);
    void disp(bool disp);
    void updateObject(const fw::UpdateInfo& info);
    void applyObject();
    unsigned int registObject(UIObject* object, const char* name, unsigned short layer, UIResource* resource);
    unsigned int searchObject(const char* name);
    // the root object listed under the handle, null when none is (inline: 1.0.0 has it out of line at 0x71006EFA3C,
    // resume inlines it in 3.0.1)
    RootObjInfo* getRootInfo(unsigned int handle) {
        for (RootObjInfo* it = m_rootObjs.begin(); it != m_rootObjs.end(); ++it) {
            if (it->m_handle == handle) {
                return it;
            }
        }
        return nullptr;
    }
    void terminateObject(const char* name, bool release);
    void readyTerminate(unsigned int handle);
    void terminateObjectAll(bool release);
    void releaseObject(const char* name);
    bool isActiveLayer(unsigned short layer);
    bool isAssignedLayer(const char* name, unsigned int layer);
    // 2.0.0's symbols name it. What it does: true when the root object the name finds (searchObject, inlined) is listed
    // and terminating (m_terminate set by terminateObject/terminateObjectAll). Its one caller is createLayerEx.
    bool isTerminating(const char* name);
    void attachInput(const char* name, UIInputLayer* layer);
    void suspend(bool stopApply);
    void resume();
    void reloadText();
    bool hasObject() const;

    UIObjectList* m_objList;  // setup's
    mm::mtl::Vector<RootObjInfo> m_rootObjs;
    mm::mtl::Vector<InputInfo> m_inputs;
    // bit 0: updateObject skips (suspend's); bit 1: applyObject skips (suspend(true)'s); bit 2: hidden (disp(false)'s)
    unsigned int m_flags;
};
}  // namespace ui

#endif
