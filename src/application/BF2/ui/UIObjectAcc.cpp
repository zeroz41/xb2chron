#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UITransform.h"
#include "classes/ui/UIObjectBase.h"
#include "classes/ui/UIObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/UIUtil.h"
#include "classes/ui/UILayoutObject.h"
#include "classes/ui/UITextObject.h"
#include "classes/ui/UIImageObject.h"
#include "classes/ui/UIColorLibrary.h"
#include "mm/Rect.h"
#include "mm/Mat44.h"
#include "mm/Vec2.h"
#include "layer/LayerAccObjBase.h"
#include "classes/ui/UIFontManager.h"
#include "classes/ui/UILayoutData.h"
#include "classes/ui/UIScreenObject.h"
#include "classes/ui/UIPolygonObject.h"

namespace ui {

UIObjectAcc::UIObjectAcc(unsigned int handle) : m_object(nullptr), m_handle(handle) {
    m_object = UIUtil::getObject(m_handle);
}

UIObjectAcc::UIObjectAcc(unsigned int handle, const char* child) : m_object(nullptr), m_handle(0) {
    if (child != nullptr) {
        handle = UIUtil::searchChild(handle, child);
    }
    m_handle = handle;
    m_object = UIUtil::getObject(m_handle);
}

UIObjectAcc::UIObjectAcc(const UIObjectAcc& other) : m_object(nullptr), m_handle(other.m_handle) {
    m_object = UIUtil::getObject(m_handle);
}

UIObjectAcc::~UIObjectAcc() {
    ;  // The original retains the class table store.
}

bool UIObjectAcc::isLayout() const {
    return m_object->m_type == 3;
}

bool UIObjectAcc::isText() const {
    return m_object->m_type == 1;
}

bool UIObjectAcc::isImage() const {
    switch (m_object->m_type) {
    case 2:
    case 4:
    case 5:
        return true;
    default:
        return false;
    }
}

void UIObjectAcc::getPos(mm::Pnt<short>& pos) const {
    if (m_object != nullptr) {
        m_object->getPos(pos);
    }
}

void UIObjectAcc::getSize(bool scaled, short& width, short& height) const {
    width = 0;
    height = 0;
    if (m_object != nullptr) {
        if (scaled) {
            width = m_object->m_displayInfo.m_pixelWidth * m_object->m_transform.m_scale.x;
            height = m_object->m_displayInfo.m_pixelHeight * m_object->m_transform.m_scale.y;
        } else {
            width = m_object->m_displayInfo.m_pixelWidth;
            height = m_object->m_displayInfo.m_pixelHeight;
        }
    }
}

void UIObjectAcc::getDisplayOffs(mm::Pnt<short>& offs) const {
    offs = mm::Pnt<short>(0, 0);
    if (m_object != nullptr) {
        m_object->getDisplayOffset(0, offs);
    }
}

void UIObjectAcc::getDisplayOffsCenter(mm::Pnt<short>& offs) const {
    offs = mm::Pnt<short>(0, 0);
    if (m_object != nullptr) {
        m_object->getDisplayOffset(1, offs);
    }
}

void UIObjectAcc::setDisp(bool disp) {
    if (m_object != nullptr) {
        m_object->m_displayInfo.setDisp(disp);
    }
}

void UIObjectAcc::setDispChild(bool disp, const char* child) {
    if (m_object != nullptr) {
        UIUtil::setDispChild(m_handle, disp, child);
    }
}

bool UIObjectAcc::isDisp() const {
    return m_object != nullptr && m_object->m_displayInfo.m_disp != 0;
}

bool UIObjectAcc::isControl() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(0);
    }
    return false;
}

bool UIObjectAcc::isDuplicate() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(4);
    }
    return false;
}

bool UIObjectAcc::isStreamImage() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(6);
    }
    return false;
}

bool UIObjectAcc::isStreamImage2nd() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(17);
    }
    return false;
}

bool UIObjectAcc::isStreaming() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(7);
    }
    return false;
}

bool UIObjectAcc::isNotInputTarget() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(9);
    }
    return false;
}

bool UIObjectAcc::isAlwaysInLayout() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(12);
    }
    return false;
}

bool UIObjectAcc::isIgnoreSize() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(13);
    }
    return false;
}

void UIObjectAcc::setTerm() {
    if (m_object != nullptr) {
        m_object->setTerm();
    }
}

bool UIObjectAcc::isTerm() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(3);
    }
    return true;
}

void UIObjectAcc::setSuspend(bool suspend) {
    if (!isTerm()) {
        m_object->setSuspend(suspend);
    }
}

unsigned short UIObjectAcc::getDuplicateIndex() const {
    return m_object != nullptr ? m_object->m_duplicateIndex : 0;
}

bool UIObjectAcc::isDebugDraw() const {
    return m_object != nullptr ? m_object->isDebugDraw() : true;
}

void UIObjectAcc::getPosCenter(mm::Pnt<short>& pos) const {
    if (m_object != nullptr) {
        m_object->getPosCenter(pos);
    }
}

void UIObjectAcc::setPos(const mm::Pnt<short>& pos) {
    if (m_object != nullptr) {
        m_object->setPos(pos);
    }
}

void UIObjectAcc::setPosCenter(const mm::Pnt<short>& pos) {
    if (m_object != nullptr) {
        m_object->setPosCenter(pos);
    }
}

void UIObjectAcc::setScale(const mm::Vec2& scale) {
    if (m_object != nullptr) {
        m_object->m_transform.setScale(scale.x, scale.y);
    }
}

void UIObjectAcc::getRot(float& rot) {
    rot = 0.0f;
    if (m_object != nullptr) {
        rot = m_object->m_transform.m_rotation;
    }
}

void UIObjectAcc::setRot(float rot) {
    if (m_object != nullptr) {
        m_object->m_transform.m_rotation = rot;
    }
}

void UIObjectAcc::getAlpha(float& alpha) {
    alpha = 0.0f;
    if (m_object != nullptr) {
        alpha = m_object->m_displayInfo.getColorInfo()->m_mulColor.a;
    }
}

void UIObjectAcc::setAlpha(float alpha) {
    if (m_object != nullptr) {
        m_object->m_displayInfo.m_mulColor.a = alpha;
    }
}

void UIObjectAcc::setMulColor(const mm::Col3& color) {
    if (m_object != nullptr) {
        m_object->m_displayInfo.m_mulColor = mm::Col4(color.r, color.g, color.b, m_object->m_displayInfo.getColorInfo()->m_mulColor.a);
    }
}

void UIObjectAcc::getMulColor(mm::Col3& color) {
    color = mm::Col3(1.0f, 1.0f, 1.0f);
    if (m_object != nullptr) {
        const mm::Col4& value = m_object->m_displayInfo.getColorInfo()->m_mulColor;
        color = mm::Col3(value.r, value.g, value.b);
    }
}

void UIObjectAcc::setMulColor(const char* name) {
    if (name != nullptr && m_object != nullptr) {
        mm::Col4 color;
        if (UIColorLibrary::get()->find(name, color)) {
            getAlpha(color.a);
            m_object->m_displayInfo.m_mulColor = color;
        }
    }
}

void UIObjectAcc::setAddColor(const mm::Col3& color) {
    if (m_object != nullptr) {
        m_object->setAddColor(color);
    }
}

void UIObjectAcc::getAddColor(mm::Col3& color) {
    if (m_object != nullptr) {
        color = m_object->m_displayInfo.getColorInfo()->m_addColor;
    }
}

void UIObjectAcc::setAddColor(const char* name) {
    if (name != nullptr && m_object != nullptr) {
        mm::Col4 color;
        if (UIColorLibrary::get()->find(name, color)) {
            m_object->setAddColor(mm::Col3(color.r, color.g, color.b));
        }
    }
}

void UIObjectAcc::saveDefColor() {
    m_object->m_displayInfo.saveDefColor();
}

void UIObjectAcc::loadDefColor() {
    m_object->m_displayInfo.loadDefColor();
}

unsigned short UIObjectAcc::getDispPriority() const {
    return m_object != nullptr ? m_object->m_displayInfo.m_priority : 0;
}

void UIObjectAcc::setDispPriority(unsigned short priority) {
    if (m_object != nullptr) {
        m_object->setPriority(priority);
    }
}

const char* UIObjectAcc::getName() const {
    return m_object != nullptr ? m_object->m_name.m_str : "error";
}

unsigned int UIObjectAcc::getParentHandle() {
    return m_object != nullptr ? m_object->m_parent : 0;
}

int UIObjectAcc::countChild(const char* format, unsigned int first) {
    if (m_object != nullptr) {
        UILayoutObject* object = mm::mtl::rttiCast<UILayoutObject>(m_object);
        if (object != nullptr) {
            return object->countChild(format, first);
        }
    }
    return 0;
}

unsigned int UIObjectAcc::searchChild(const char* name) {
    if (m_object != nullptr) {
        UILayoutObject* object = mm::mtl::rttiCast<UILayoutObject>(m_object);
        if (object != nullptr) {
            return object->searchChild(name);
        }
    }
    return 0;
}

unsigned int UIObjectAcc::searchDuplicatedChild(const char* name, unsigned short index) {
    if (m_object != nullptr) {
        UILayoutObject* object = mm::mtl::rttiCast<UILayoutObject>(m_object);
        if (object != nullptr) {
            return object->searchDuplicatedChild(name, index);
        }
    }
    return 0;
}

unsigned int UIObjectAcc::searchSibiling(const char* name) {
    if (m_object != nullptr) {
        UIObject* parent = m_object->getParentPtr();
        if (parent != nullptr) {
            UILayoutObject* layout = mm::mtl::rttiCast<UILayoutObject>(parent);
            if (layout != nullptr) {
                return layout->searchChild(name);
            }
        }
    }
    return 0;
}

unsigned int UIObjectAcc::duplicate(unsigned int parent) {
    return m_object != nullptr ? m_object->duplicate(parent) : 0;
}

unsigned int UIObjectAcc::duplicateChild(const char* name) {
    if (m_object != nullptr) {
        UILayoutObject* object = mm::mtl::rttiCast<UILayoutObject>(m_object);
        if (object != nullptr) {
            unsigned int child = object->searchChild(name);
            if (child != 0) {
                return UIUtil::getObject(child)->duplicate(m_handle);
            }
        }
    }
    return 0;
}

void UIObjectAcc::setScreenAdjusting(bool adjusting) {
    if (m_object != nullptr) {
        m_object->m_flags.set(11, adjusting);
    }
}

void UIObjectAcc::setIgnoreSize(bool ignore) {
    // the object in a local: a second m_object read for the flag's store keeps a second load of the flags
    UIObject* object = m_object;
    if (object != nullptr && object->m_flags.test(13) != ignore) {
        object->m_flags.set(13, ignore);
        m_object->m_transform.m_changed = true;
    }
}

void UIObjectAcc::applyText(const char* text) {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            object->applyText(text);
        }
    }
}

void UIObjectAcc::setText(const UIStr& text) {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            object->setText(text);
        }
    }
}

void UIObjectAcc::getText(UIStr& text) const {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            text.copy(object->m_text);
        }
    }
}

const char* UIObjectAcc::getTextPtr() const {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            return object->m_text.c_str();
        }
    }
    return nullptr;
}

void UIObjectAcc::setTextAlignH(unsigned char align) {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            object->setTextAlignH(align);
        }
    }
}

void UIObjectAcc::setBorderWeight(float weight) {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            object->setBorderWeight(weight);
        }
    }
}

void UIObjectAcc::setSlopeRot(float rot) {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            object->setSlopeRot(rot * 0.0174532924f);
        }
    }
}

unsigned int UIObjectAcc::getTextFacePatternIndex() {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            if (m_object != nullptr) {
                return object->m_facePattern;
            }
        }
    }
    return 0;
}

void UIObjectAcc::setImageIndex(unsigned int index) {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->setImageIndex(index);
        }
    }
}

unsigned int UIObjectAcc::getImageIndex() const {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            return object->getImageIndex();
        }
    }
    return 0;
}

unsigned int UIObjectAcc::getImageMax() const {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            return object->getImageMax();
        }
    }
    return 0;
}

void UIObjectAcc::setExtType(unsigned int type) {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->setExtType(type);
        }
    }
}

unsigned int UIObjectAcc::getExtType() {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            return object->getExtType();
        }
    }
    return 0;
}

void UIObjectAcc::setExtParam(float param) {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->setExtParam(param);
        }
    }
}

bool UIObjectAcc::hasAnimation() {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            return object->hasAnimation();
        }
    }
    return false;
}

void UIObjectAcc::startAnimation(const char* name, bool loop) {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->startAnimation(name, loop);
        }
    }
}

void UIObjectAcc::startAnimationFromID(unsigned int id, bool loop) {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->startAnimationFromID(id, loop);
        }
    }
}

void UIObjectAcc::startAnimationFromIndex(unsigned int index, bool loop) {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->startAnimationFromIndex(index, loop);
        }
    }
}

void UIObjectAcc::stopAnimation() {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->stopAnimation();
        }
    }
}

bool UIObjectAcc::isPlayingAnimation() {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            return object->isPlayingAnimation();
        }
    }
    return false;
}

float UIObjectAcc::getAnimationPlaybackLength() {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            return object->getAnimationPlaybackLength();
        }
    }
    return 0.0f;
}

void UIObjectAcc::setAnimationPlaybackTime(float time) {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->setAnimationPlaybackTime(time);
        }
    }
}

bool UIObjectAcc::isPlaybackControl() const {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            return object->m_loop != 0;
        }
    }
    return false;
}

void UIObjectAcc::setLayoutViewport(mm::Rect<short> rect) {
    if (m_object != nullptr) {
        UILayoutObject* object = mm::mtl::rttiCast<UILayoutObject>(m_object);
        if (object != nullptr) {
            object->setViewport(rect);
        }
    }
}

void UIObjectAcc::updateLayoutSize() {
    if (m_object != nullptr) {
        UILayoutObject* object = mm::mtl::rttiCast<UILayoutObject>(m_object);
        if (object != nullptr) {
            object->updateSize();
        }
    }
}

bool UIObjectAcc::fn_7100690ED4() const {
    if (m_object != nullptr) {
        return m_object->m_flags.test(18);
    }
    return false;
}

void UIObjectAcc::setMatrix(const mm::Mat44& matrix) {
    if (m_object != nullptr) {
        layer::LayerAccObjBase acc(m_object->m_layer);
        acc.setMatrix(matrix);
    }
}

void UIObjectAcc::getMatrix(mm::Mat44& matrix) {
    matrix = mm::Mat44::identity;
    if (m_object != nullptr) {
        layer::LayerAccObjBase acc(m_object->m_layer);
        matrix = acc.getMatrix();
    }
}

void UIObjectAcc::setTexFilterNearest() {
    layer::LayerAccObjBase acc(m_object->m_layer);
    acc.setTexFilterType(static_cast<layer::LayerTexFilterType>(0));
}

void UIObjectAcc::setTextFacePattern(const char* name) {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            if (m_object != nullptr && name != nullptr) {
                unsigned int index;
                if (mm::mtl::PtrSingleton<UIFontManager>::get()->findFacePattern(name, index)) {
                    object->setTextFacePattern(index);
                }
            }
        }
    }
}

void UIObjectAcc::setTextFacePattern(unsigned int index) {
    if (m_object != nullptr) {
        UITextObject* object = mm::mtl::rttiCast<UITextObject>(m_object);
        if (object != nullptr) {
            if (m_object != nullptr) {
                object->setTextFacePattern(index);
            }
        }
    }
}

void UIObjectAcc::setMaskObject(unsigned int handle) {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->setMaskObject(UIUtil::getImageObject(handle));
        }
    }
}

void UIObjectAcc::setStreamImage2nd() {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->m_flags.set(17, true);
        }
    }
}

void UIObjectAcc::fn_7100691FD0() {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->m_flags.set(18, true);
        }
    }
}

void UIObjectAcc::fn_710069201C() {
    if (m_object != nullptr) {
        UIImageObject* object = mm::mtl::rttiCast<UIImageObject>(m_object);
        if (object != nullptr) {
            object->m_flags.reset(17);
            object->m_flags.reset(18);
        }
    }
}

void UIObjectAcc::setLayout(unsigned int handle, const char* name) {
    if (m_object != nullptr) {
        UILayoutObject* layout = mm::mtl::rttiCast<UILayoutObject>(m_object);
        if (layout != nullptr) {
            UILayoutData* data = layout->m_layoutData;
            UIObject* object = UIUtil::getObject(handle);
            if (data != nullptr && object != nullptr) {
                data->attachLayout(name, object);
            }
        }
    }
}

bool UIObjectAcc::getLayoutRect(const char* name, mm::Rect<short>& rect) {
    if (m_object != nullptr) {
        UILayoutObject* layout = mm::mtl::rttiCast<UILayoutObject>(m_object);
        if (layout != nullptr && layout->m_layoutData != nullptr) {
            return layout->m_layoutData->getLayoutRect(name, rect);
        }
    }
    return false;
}

unsigned int UIObjectAcc::getRenderIndex() {
    if (m_object != nullptr) {
        UIScreenObject* object = mm::mtl::rttiCast<UIScreenObject>(m_object);
        if (object != nullptr) {
            return object->m_viewIndex;
        }
    }
    return 0;
}

unsigned int UIObjectAcc::getOnMemoryPixelSize() {
    if (m_object != nullptr) {
        UIScreenObject* object = mm::mtl::rttiCast<UIScreenObject>(m_object);
        if (object != nullptr) {
            return object->getOnMemoryPixelSize();
        }
    }
    return 0;
}

void* UIObjectAcc::getOnMemoryBuffer() {
    if (m_object != nullptr) {
        UIScreenObject* object = mm::mtl::rttiCast<UIScreenObject>(m_object);
        if (object != nullptr) {
            return object->getOnMemoryBuffer();
        }
    }
    return nullptr;
}

void UIObjectAcc::swapOnMemoryBuffer() {
    if (m_object != nullptr) {
        UIScreenObject* object = mm::mtl::rttiCast<UIScreenObject>(m_object);
        if (object != nullptr) {
            object->swapOnMemoryBuffer();
        }
    }
}

bool UIObjectAcc::isShapeSimpleFace() {
    if (m_object != nullptr) {
        UIPolygonObject* object = mm::mtl::rttiCast<UIPolygonObject>(m_object);
        if (object != nullptr) {
            return object->m_info.m_shapeType == 1;
        }
    }
    return false;
}

UIShape* UIObjectAcc::getShape() {
    if (m_object != nullptr) {
        UIPolygonObject* object = mm::mtl::rttiCast<UIPolygonObject>(m_object);
        if (object != nullptr) {
            return object->m_shape;
        }
    }
    return nullptr;
}

}  // namespace ui
