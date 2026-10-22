#ifndef CLASSES_UI_UIOBJECTACC_H
#define CLASSES_UI_UIOBJECTACC_H

namespace ui { class UIObject; }
namespace ui { class UIShape; }
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
    unsigned int searchChild(const char* name);
    unsigned int getParentHandle();  // the handle of its child of that name
    void setTerm();
    bool isTerm() const;
    void setMatrix(const mm::Mat44& matrix);
    void getMatrix(mm::Mat44& matrix);
    bool isText() const;
    bool isStreaming() const;
    void getRect(mm::Rect<short>& rect, unsigned short mode) const;
    void getPos(mm::Pnt<short>& pos) const;
    void setDisp(bool disp);
    bool isDisp() const;
    void setSuspend(bool suspend);
    const char* getTextPtr() const;  // its text object's text, null when it is not a text
    bool isImage() const;
    bool isLayout() const;
    unsigned int getImageMax() const;  // its image object's number of images, 0 when it is not an image
    unsigned int getExtType();  // its image object's, 0 when it is not an image
    void setExtParam(float param);
    bool hasAnimation();
    void startAnimationFromIndex(unsigned int index, bool loop);
    float getAnimationPlaybackLength();
    void setAnimationPlaybackTime(float time);
    bool isPlayingAnimation();
    bool isPlaybackControl() const;
    void applyText(const char* text);
    bool isShapeSimpleFace();
    UIShape* getShape();  // its polygon object's shape
    bool isDebugDraw() const;
    void getPosCenter(mm::Pnt<short>& pos) const;
    void getSize(bool scaled, short& width, short& height) const;
    void setPos(const mm::Pnt<short>& pos);
    void setPosCenter(const mm::Pnt<short>& pos);
    void getScale(mm::Vec2& scale);
    void setScale(const mm::Vec2& scale);
    void getRot(float& rot);
    void setRot(float rot);
    void setSlopeRot(float rot);
    void startAnimation(const char* name, bool);
    void getAlpha(float& alpha);
    void setAlpha(float alpha);
    void setText(const UIStr& text);
    void setTextFacePattern(unsigned int index);
    void setImageIndex(unsigned int index);
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
