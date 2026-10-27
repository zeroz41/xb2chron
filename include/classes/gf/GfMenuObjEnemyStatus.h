#ifndef CLASSES_GF_GFMENUOBJENEMYSTATUS_H
#define CLASSES_GF_GFMENUOBJENEMYSTATUS_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf {
// table 0x7100B61CD0
class GfMenuObjEnemyStatus : public ::gf::GfMenuObject {
public:
    struct OpenParam {
        GF_OBJ_HANDLE* m_obj;  // the enemy whose status it shows (GfMenuManager::gevChangeTarget's target)
    };
    // the adapters initialize creates, that update hands each new target (the name is not the original's). An
    // aggregate the constructor value-initializes: it zeroes the whole room, then the vector's constructor runs
    struct AdapterList {
        mm::mtl::FixedVector<TUnk_B5C118*, 25> m_list;
    };
    GfMenuObjEnemyStatus(unsigned int handle);
    static void open(const OpenParam& param);  // 1.0.0 symbol
    static void close();  // 1.0.0 symbol
    static void disp(bool disp);  // 1.0.0 symbol
    class ElemListener;
    class MainListener;
    virtual ~GfMenuObjEnemyStatus();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's copy, fn_710045D1BC, is unnamed
    // too). A member because it sits in this class's unit and only MainListener::reciveEvent calls it. What it
    // does: when both objects exist and the first's layout has a rect "elem_%02d" (index), it starts a control on
    // the second's handle that moves it there (methods 0x80, 0.25 s).
    static void fn_71003F98A4(unsigned int layout, unsigned int handle, int index);

    GF_OBJ_HANDLE* m_target;      // 0x28: the target update last handed the adapters (-1: none)
    AdapterList m_adapters;       // 0x30
    int m_suspendCtrl;            // 0x100: ElemListener's control slot of "LAY_elem_time_suspend" (-1: none)
    unsigned char pad_104[4];
    GfMenuSequence<GfMenuObjEnemyStatus, 4> m_seq;  // 0x108
};
}  // namespace gf

#endif
