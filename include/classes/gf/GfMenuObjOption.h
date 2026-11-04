#ifndef CLASSES_GF_GFMENUOBJOPTION_H
#define CLASSES_GF_GFMENUOBJOPTION_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "gf/SDataOption.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class SDataOption; class GfMenuCallContext; }
namespace ui { class UISelectObjList; class UICtrlCursorSelect; }

namespace gf {
// table 0x7100B63CA8
class GfMenuObjOption : public ::gf::GfMenuObject {
public:
    class ItemListListener;
    class ItemSettingListener;
    class MainListener;
    class SubMenuListener;
    // one setting of a category's list (1.0.0's convLevelListToOptionData and getDefaultLevel take a
    // FixedVector<Level, 32>): 3 bytes; initOptionData scales m_level / m_max to the gamma (the field names are not
    // the original's)
    struct Level {
        unsigned char m_level;
        unsigned char m_max;
        unsigned char m_byte2;
    };
    GfMenuObjOption(unsigned int handle);
    // TitleMenu::setupOption attaches the option menu object to its call context: true when the object is there
    static bool attach(GfMenuCallContext* context);
    static void initOptionData(SDataOption& option);
    static void getDefaultLevel(unsigned int category, mm::mtl::FixedVector<Level, 32>& levels, bool);
    static void convLevelListToOptionData(unsigned int category, const mm::mtl::FixedVector<Level, 32>& levels,
                                          SDataOption& option);
    // 2.0.0's symbols name them (new in 3.0.1's line: 1.0.0 has getVolumeLevel, getGammaLevel, getVolumeValue and
    // getGammaValue there, with other signatures). What they do: they read one of two lists of values, 2 long
    // ({1, 0}) or, when GfMenuObjUtil::isValidExpansion(3) and GfGameManager::isClearGame hold or
    // GfGameUtil::isAdvancedDifficulity does, 4 long ({1, 0, 2, 4}).
    // getDifficultyIndex: the index of value in the list (0 when it is not there)
    static unsigned int getDifficultyIndex(unsigned int value);
    // getDifficultyMax: the list's length, 2 or 4
    static unsigned int getDifficultyMax();
    // getDifficultyFromIndex: the list's value at index (0 past its end)
    static int getDifficultyFromIndex(unsigned int index);
    virtual ~GfMenuObjOption();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    void dispItemBase(unsigned int category, unsigned int index, bool disp);
    void updateInfo(unsigned int index);
    bool seqSave();
    bool seqSaveWait();

    // the field names are not the original's
    unsigned char pad_24[0x4];
    ui::UISelectObjList* m_mainList;           // 0x28
    ui::UISelectObjList* m_itemList;           // 0x30
    ui::UICtrlCursorSelect* m_cursor;          // 0x38
    unsigned char* m_capBdat;                  // 0x40 the bdat updateInfo reads "cap_id" from
    unsigned int m_infoHandle;                 // 0x48 the object updateInfo sets the caption text of
    unsigned int m_settingHandle;              // 0x4C
    mm::mtl::FixedVector<Level, 32> m_levels;  // 0x50
    mm::mtl::FixedVector<unsigned char, 16> m_itemTypes;  // 0xB8
    SDataOption m_option;                      // 0xD0
    GfMenuCallContext* m_callContext;          // 0x158
    GfMenuSequence<GfMenuObjOption, 8> m_seq;  // 0x160
    bool m_flag3F0;
    unsigned char pad_3F1[0x3];
    unsigned int m_saveReq;                    // 0x3F4 seqSave's GfReqCommand::reqSaveOption request
    bool m_byte3F8;
    bool m_guideFlag;                          // 0x3F9 setGuideText's argument
    signed char m_category;                    // 0x3FA -1: none
    bool m_flag3FB;
    bool m_flag3FC;
};
}  // namespace gf

#endif
