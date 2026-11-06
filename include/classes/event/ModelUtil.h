#ifndef CLASSES_EVENT_MODELUTIL_H
#define CLASSES_EVENT_MODELUTIL_H

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// model helpers (no table; the symbols name the class and its function)
class ModelUtil {
public:
    // out of line (0x71000BA6FC, not written yet); MdlstmObj readies a built model's handle with it
    static void setupRenderState(gf::GF_OBJ_HANDLE* handle);
};
}  // namespace event

#endif
