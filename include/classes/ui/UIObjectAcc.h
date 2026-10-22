#ifndef CLASSES_UI_UIOBJECTACC_H
#define CLASSES_UI_UIOBJECTACC_H

namespace ui { class UIObject; }
namespace mm { class Mat44; }
namespace mm { class Vec2; }
namespace mm { template <typename> class Pnt; }
namespace mm { template <typename> class Rect; }
namespace ui { class UIStr; }
namespace mm { class Col3; }

namespace ui {
// table 0x7100B75718
class UIObjectAcc {
public:
    UIObjectAcc(unsigned int handle);
    UIObjectAcc(unsigned int handle, const char* child);  // the child UIUtil::searchChild finds, if one is named
    virtual ~UIObjectAcc();  // slot 0
    void setDispChild(bool disp, const char* child);
    bool isTerm() const;
    void setMatrix(const mm::Mat44& matrix);
    void getMatrix(mm::Mat44& matrix);
    bool isText() const;
    void getRect(mm::Rect<short>& rect, unsigned short mode) const;
    void getPos(mm::Pnt<short>& pos) const;
    void setDisp(bool disp);
    bool isDisp() const;
    bool isDebugDraw() const;
    void getPosCenter(mm::Pnt<short>& pos) const;
    void getSize(bool scaled, short& width, short& height) const;
    void setPos(const mm::Pnt<short>& pos);
    void setPosCenter(const mm::Pnt<short>& pos);
    void getScale(mm::Vec2& scale);
    void setScale(const mm::Vec2& scale);
    void getRot(float& rot);
    void setRot(float rot);
    void getAlpha(float& alpha);
    void setAlpha(float alpha);
    void setText(const UIStr& text);
    void setTextFacePattern(unsigned int index);
    unsigned int getTextFacePatternIndex();
    unsigned int searchSibiling(const char* name);
    const char* getName() const;
    void setScreenAdjusting(bool adjusting);
    void getMulColor(mm::Col3& color);
    void setMulColor(const mm::Col3& color);
    void setAddColor(const mm::Col3& color);
    UIObject* m_object;      // UIUtil::getObject(m_handle): isTerm reads its flags, setTerm calls its setTerm
    unsigned int m_handle;   // what the constructor is given (or its named child's)
};
}  // namespace ui

#endif
