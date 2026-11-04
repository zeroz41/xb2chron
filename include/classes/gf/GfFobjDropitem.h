#ifndef CLASSES_GF_GFFOBJDROPITEM_H
#define CLASSES_GF_GFFOBJDROPITEM_H

#include "mm/Vec3.h"
#include "mm/mtl/Vector.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; struct GfDropitemParam; }

namespace gf {
// one entry of GfFobjDropitem::EmitInfo's drop list (0x14 bytes by its Vector's indexing): emitDropitems reads an
// item id at 0x0, a count at 0x4 and the float it hands to emitDropitem at 0x10
struct GfDropitemInfo {
    unsigned char pad_0x0[0x14];
};

// table 0x7100B52910
class GfFobjDropitem {
public:
    // what emitDropitems drops and where (GfDropitemEmitter::seqWaitBeginDrop builds one from its CreateInfo; the
    // field names are not the original's)
    struct EmitInfo {
        EmitInfo()
            : m_pos(mm::Vec3::zero), m_angle(0.0f), m_angleRange(3.14159265f), m_dropDistance(0.0f),
              m_appearDelay(0.0f), m_appearDelayRange(0.0f), m_items(), pad_0x50(0), m_paramId(0), pad_0x55(false),
              pad_0x56(0) {}
        // fills m_items from count rows of items (the item and gold tables)
        void createDropitemInfos(unsigned char* items, int count);
        // 2.0.0's symbols name it. What it does: fills m_items (Vector<GfDropitemInfo>::expand) from count random rows
        // of a BDAT table (FixStr formats, ml::mtRand), checking GfItemUtil::getItemBoxCount; fn_71002862F8 is its
        // helper.
        void createDropitemInfosBattleChallenge(int count);

        mm::Vec3 m_pos;  // where the items drop from
        float m_angle;  // emitDropitems spreads the drops from m_angle - m_angleRange
        float m_angleRange;
        float m_dropDistance;  // copied into each item's setup (GfObjSetupFieldObj::m_dropDistance)
        // each item's setup gets m_appearDelay + m_appearDelayRange * a random [0, 1)
        // (GfObjSetupFieldObj::m_appearDelay)
        float m_appearDelay;
        float m_appearDelayRange;
        mm::mtl::Vector<GfDropitemInfo> m_items;  // the items to drop
        unsigned int pad_0x50;  // emitDropitems makes this many more drops after m_items' (a count)
        unsigned char m_paramId;  // emitDropitem/emitDropgold's paramId
        bool pad_0x55;  // emitDropitems tests it for item 0x61C3
        unsigned char pad_0x56;  // copied into each item's setup (0x90)
    };

    GfFobjDropitem(GF_OBJ_HANDLE* handle);
    virtual ~GfFobjDropitem();  // slot 0
    void initialize();
    void destroy();
    void update(const fw::UpdateInfo& info);
    void setEventDisp(bool disp);
    // whether getter is near enough to take the item (radius widens the item_get param's reach; the argument names
    // are not the original's)
    bool canGetItem(GF_OBJ_HANDLE* getter, float radius) const;
    void applyGetItem(GF_OBJ_HANDLE* getter) const;  // void: no path of the original sets w0
    // gives the item whose object is item (its user data 2 holds the GfFobjDropitem) to getter when getter's object
    // exists; false when item has no GfFobjDropitem (the argument names are not the original's)
    static bool applyGetItem(GF_OBJ_HANDLE* item, GF_OBJ_HANDLE* getter);
    // the drop resource row of an item id: which of the item tables holds it decides, three of them read it from the
    // row's "Category" or "DropRsc"; -1 when no table holds it
    // makes the field object of an item id (its row from getResBdatIdFromItemId; paramId picks its "paramid<n>"
    // column) and gives its setup the item's table and id and the float emitDropitems takes from its drop list
    // (setup 0x8c); an item of tables 0x9C/0x9D goes to the item box at once (createMenuPrecious) and returns -1
    // (the argument names are not the original's)
    static GF_OBJ_HANDLE* emitDropitem(unsigned char paramId, int itemId, float value);
    // makes a field object dropping gold (row 10 to 14 of the field object table by the amount against the
    // thresholds of table 0x7B rows 8 to 11) and gives its setup the amount; the object's handle
    static GF_OBJ_HANDLE* emitDropgold(unsigned char paramId, unsigned int gold);
    // 2.0.0's symbols name it. What it does: makes the field object of row 30 (paramId picks its "paramid<n>" column,
    // as emitDropgold's) and gives its setup the amount (m_amount, which applyGetItem hands to
    // btl::Utility::fn_7100010900); returns the object's handle.
    static GF_OBJ_HANDLE* emitDropEtherCube(unsigned char paramId, unsigned int amount);
    static int getResBdatIdFromItemId(int itemId);
    // drops info's items around info.m_pos; returns the longest appear delay it gave a drop (-1 when there is
    // nothing to drop)
    static float emitDropitems(const EmitInfo& info);

    // the item's row of the field object table (initialize reads them by name; the names are not the original's)
    // [0] "dropSE" (update plays it at the first bounce), [1] "getdropSE" (played when the item is taken); the
    // constructor zeroes both as one block
    unsigned short m_se[2];
    unsigned char m_limitType;  // "limitType"
    unsigned char pad_0xd[0x1];
    unsigned char m_rarity;  // the item's "Rarity" (initialize reads it when the item table has the member)
    // the item's object: GfFobjManager finds an item by it (listenerGfObj, leaveGameField) and destroys it
    // (GfObjUtil::destroy) (the name is not the original's)
    GF_OBJ_HANDLE* m_handle;
    unsigned char pad_0x18[0x8];
    // initialize sets it from the drop angles and the param's speeds; update moves the item by it, damps it each
    // bounce (the name is not the original's)
    float m_velocity[3];
    unsigned char pad_0x2c[0x4];
    int m_bounceCount;  // update counts the bounces up to the param's limit (the name is not the original's)
    float m_time;  // update adds each frame's time step; negative while waiting (the name is not the original's)
    // update adds each frame's time step and toggles the object's display 8 when it reaches the param's blink
    // interval, then resets it (the name is not the original's)
    float m_blinkTime;
    // update adds each frame's time step once the bounces reach the param's limit (the name is not the original's)
    float m_restTime;
    // the item's row of GfFobjManager's GfDropitemParams (initialize picks it; the name is not the original's)
    const GfDropitemParam* m_param;
    // initialize: the param's base plus a random part of its range (0x0/0x4); the jump's initial vertical speed
    // follows from it (the name is not the original's)
    float m_jumpHeight;
    // initialize: the setup's value plus the param's base and random range (0x8/0xc); the horizontal speed follows
    // from it (the name is not the original's)
    float m_jumpDistance;
    // update sets it when it sends SCOM_DESTROY_GAME_OBJ for the item, once (the name is not the original's)
    bool m_destroyRequested;
    unsigned int m_effect;  // the item's effect handle (destroy kills it, setEventDisp shows it; the name is not the original's)
    unsigned char pad_0x58[0x1];  // initialize copies a byte of the setup (0x90) into it
    unsigned char pad_0x59[0x60 - 0x59];  // GfObjFactory::createFieldObj allocates 0x60
};
}  // namespace gf

#endif
