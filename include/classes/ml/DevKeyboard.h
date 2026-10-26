#ifndef CLASSES_ML_DEVKEYBOARD_H
#define CLASSES_ML_DEVKEYBOARD_H

namespace ml {
class DevKeyboard {
public:
    // FrameworkLauncher::destroy calls it with no object once the launcher is done
    static void clearKey();
};
}  // namespace ml

#endif
