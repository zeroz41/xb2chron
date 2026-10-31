#ifndef CLASSES_GF_GFFOBJDROPITEM_H
#define CLASSES_GF_GFFOBJDROPITEM_H

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; struct GfDropitemParam; }

namespace gf {
// table 0x7100B52910
class GfFobjDropitem {
public:
    GfFobjDropitem(GF_OBJ_HANDLE* handle);
    virtual ~GfFobjDropitem();  // slot 0
    void initialize();
    void destroy();
    void update(const fw::UpdateInfo& info);
    void setEventDisp(bool disp);
    bool applyGetItem(GF_OBJ_HANDLE* getter) const;
    // gives the item whose object is item (its user data 2 holds the GfFobjDropitem) to getter when getter's object
    // exists; false when item has no GfFobjDropitem (the argument names are not the original's)
    static bool applyGetItem(GF_OBJ_HANDLE* item, GF_OBJ_HANDLE* getter);
    // the drop resource row of an item id: which of the item tables holds it decides, three of them read it from the
    // row's "Category" or "DropRsc"; -1 when no table holds it
    // makes a field object dropping gold (row 10 to 14 of the field object table by the amount against the
    // thresholds of table 0x7B rows 8 to 11) and gives its setup the amount; the object's handle
    static GF_OBJ_HANDLE* emitDropgold(unsigned char paramId, unsigned int gold);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because emitDropitems calls it in
    // place of emitDropgold for its second kind of amount. What it does: makes the field object of row 30 (paramId
    // picks its "paramid<n>" column, as emitDropgold's) and gives its setup the amount (m_amount, which applyGetItem
    // hands to btl::Utility::fn_7100010900); returns the object's handle.
    static GF_OBJ_HANDLE* fn_7100287E30(unsigned char paramId, unsigned int amount);
    static int getResBdatIdFromItemId(int itemId);

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
