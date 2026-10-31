#ifndef CLASSES_ML_FONTLAYER_H
#define CLASSES_ML_FONTLAYER_H

namespace ml { enum FONT_STYLE : int; }
namespace mm { class Col4; }
namespace ml { class DevFontLayer; }

namespace ml {
// table 0x7100B763C0
class FontLayer {
public:
    // makes its DevFontLayer under DevFont when DevFont exists
    FontLayer();
    virtual ~FontLayer();  // slot 0

    void font(int x, int y, const char* format, ...);
    void fontStyle(FONT_STYLE style);
    // each records into the debug draw's command cache off the render thread (DebDraw::isNotRender), else goes
    // straight to DevFont
    void fontColor(const mm::Col4& col);
    void fontShadow(bool on);
    void fontFlush(bool on);
    void fontScale(float x, float y);
    // set the queue capacity of its DevFontLayer (FrameworkLauncher::mlthFnBuild's)
    void fontSetMaxQue(unsigned int max);
    // its DevFontLayer's font height through DevGraph::fontGetHeightSys, 0 without either
    unsigned int fontGetHeight() const;
    // 0x08 its DevFontLayer, made by the constructor when DevFont exists (the name is not the original's)
    DevFontLayer* m_devLayer;
};
}  // namespace ml

#endif
