#ifndef CLASSES_TL_TITLEMENU_H
#define CLASSES_TL_TITLEMENU_H

namespace gf { class GfMenuCallContext; }

namespace tl {
// The title screen's menus (title, event theater, option) and the call context they report through. TitleMain
// holds one at +0x198 (TitleStateMainScreen::dispTitleMenu passes title + 0x198 to setupTitle). Its size is not
// known: only +0x8 is read by its functions.
class TitleMenu {
public:
    void destroyMenuCallContext();
    void openTitle(bool flag);
    bool isOpenTitle() const;
    void setupTitle();
    bool hasResultSelect() const;
    int getResult() const;
    void closeTitle(bool flag0, bool flag1);
    bool isCloseTitle() const;
    void openEventTheater();
    bool isOpenEventTheater() const;
    void setupEventTheater();
    bool hasResultEventTheater() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 goes from hasResultEventTheater
    // to openOption). A member because it sits in TitleMenu's run and reads TitleMenu's call context. What it
    // does: false without a context, else the context's isTerm().
    bool fn_7100153350() const;
    void openOption();
    bool isOpenOption() const;
    void setupOption();
    // Placeholder name: new in 3.0.1 (where 1.0.0 has hasResultOption, which reads the result count instead).
    // A member for the same reason as fn_7100153350; same body: false without a context, else isTerm().
    bool fn_71001533B8() const;
    void exitOption();
    int getPlayEventID() const;
    void exitEventTheater();
    void fadeoutEventTheater();

    unsigned char pad_0[0x8];
    gf::GfMenuCallContext* m_context;  // made on first use, released by destroyMenuCallContext
};
}  // namespace tl

#endif
