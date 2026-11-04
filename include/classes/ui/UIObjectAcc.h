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
    // inline: UIObject::updatePlugin builds one on itself (3.0.1 has no out-of-line copy)
    explicit UIObjectAcc(UIObject* object);  // defined after UIObject (classes/ui/UIObject.h)
    UIObjectAcc(unsigned int handle, const char* child);  // the child UIUtil::searchChild finds, if one is named
    virtual ~UIObjectAcc();  // slot 0
    void setDispChild(bool disp, const char* child);
    unsigned int searchChild(const char* name);
    // a copy of its child of that name, added to the same parent (the copy's handle)
    unsigned int duplicateChild(const char* name);
    unsigned int getParentHandle();  // the handle of its child of that name
    // how many children match a name with a number (a format such as "LAY_x@%02d", numbered from `first`)
    int countChild(const char* format, unsigned int first);
    void setTerm();
    bool isTerm() const;
    void setMatrix(const mm::Mat44& matrix);
    void getMatrix(mm::Mat44& matrix);
    bool isText() const;
    bool isStreamImage() const;  // bit 6 of its object's flags at 0x98 (false without an object)
    bool isStreaming() const;
    void getRect(mm::Rect<short>& rect, unsigned short mode) const;
    void getPos(mm::Pnt<short>& pos) const;
    void setDisp(bool disp);
    bool isDisp() const;
    bool isIgnoreSize() const;  // left out of its layout's size (UILayoutObject::updateSize)
    bool isAlwaysInLayout() const;  // counted in its layout's size even while hidden (UILayoutObject::updateSize)
    bool isNotInputTarget() const;  // ui::UIInputPointer skips such an object
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
    void setStreamImage2nd();
    // 2.0.0's symbols name it. What it does: when m_object is a ui::UIImageObject (RTTI isKindOf
    // UIImageObject::m_rtti), sets bit 0x40000 of its u32 at 0x98. GfMenuObjHitonowa's setFaceStream and fn_710041E90C
    // call it.
    void setStreamImage3rd();
    // 2.0.0's symbols name it. What it does: when m_object is a ui::UIImageObject, clears bits 0x60000 of its u32 at
    // 0x98 (the bits setStreamImage2nd and setStreamImage3rd set). The same two callers call it first.
    void resetStreamImageEx();
    void stopAnimation();
    bool isPlaybackControl() const;
    void applyText(const char* text);
    bool isShapeSimpleFace();
    UIShape* getShape();  // its polygon object's shape
    bool isDebugDraw() const;
    void getPosCenter(mm::Pnt<short>& pos) const;
    void getDisplayOffs(mm::Pnt<short>& offs) const;  // its object's display offset (0, 0 without one)
    void getSize(bool scaled, short& width, short& height) const;
    void setPos(const mm::Pnt<short>& pos);
    void setPosCenter(const mm::Pnt<short>& pos);
    void getScale(mm::Vec2& scale);
    void setScale(const mm::Vec2& scale);
    void getRot(float& rot);
    void setRot(float rot);
    void setSlopeRot(float rot);
    void setTextAlignH(unsigned char align);  // its text object's horizontal alignment
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
    void getAddColor(mm::Col3& color);
    // a color UIColorLibrary has under that name (nothing for null or a name it does not have)
    void setMulColor(const char* name);
    void setAddColor(const char* name);
    void setDispPriority(unsigned short priority);
    void setLayoutViewport(mm::Rect<short> rect);
    // sets a layout of the object on another object (GfMenuObjBladeRelease::seqOpenImage: "bl_img01" on its image)
    void setLayout(unsigned int handle, const char* name);
    UIObjectAcc(const UIObjectAcc& other);
    void getDisplayOffsCenter(mm::Pnt<short>& offs) const;
    bool isControl() const;
    bool isDuplicate() const;
    bool isStreamImage2nd() const;
    // 2.0.0's symbols name it. What it does: bit 18 of its object's flags at 0x98 (false without an object), the bit
    // setStreamImage3rd sets and resetStreamImageEx clears. ui::UIStreamManager::start calls it.
    bool isStreamImage3rd() const;
    void setTexFilterNearest();  // its layer object's texture filter type 0 (on a fresh LayerAccObjBase)
    void setTextFacePattern(const char* name);  // the face pattern UIFontManager has under that name
    unsigned int getRenderIndex();  // its screen object's view index, 0 when it is not a screen
    unsigned short getDuplicateIndex() const;
    void saveDefColor();
    void loadDefColor();
    unsigned short getDispPriority() const;
    unsigned int searchDuplicatedChild(const char* name, unsigned short index);
    unsigned int duplicate(unsigned int parent);
    void setIgnoreSize(bool ignore);
    void getText(UIStr& text) const;
    void setBorderWeight(float weight);
    unsigned int getImageIndex() const;
    void setExtType(unsigned int type);
    void startAnimationFromID(unsigned int id, bool loop);
    void updateLayoutSize();
    // the rectangle of its layout's entry of that name (GfMenuObjMinimap2 reads "mini_map" and "mini_map2")
    bool getLayoutRect(const char* name, mm::Rect<short>& rect);  // false when it has no such entry
    // masked by the image object of that handle (GfMenuObjMinimap2's icons by "IMG_map_mask")
    void setMaskObject(unsigned int handle);
    // its object's on-memory buffer (a UIScreenObject's: fw::MovieManager draws its movie there)
    unsigned int getOnMemoryPixelSize();
    void* getOnMemoryBuffer();
    void swapOnMemoryBuffer();
    UIObject* m_object;      // UIUtil::getObject(m_handle): isTerm reads its flags, setTerm calls its setTerm
    unsigned int m_handle;   // what the constructor is given (or its named child's)
};
}  // namespace ui

#endif
