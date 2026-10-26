#ifndef FW_FRAMEWORKCONFIG_H
#define FW_FRAMEWORKCONFIG_H

namespace fw {
// how the framework is set up (fw::Framework::initialize's first; apps::FrameworkLauncher keeps a copy at 0x200 and
// its AppletCreateParam another). Copies of it move 0x3D bytes (its data ends at the bool at 0x3C), so it is
// trivially copyable. Only the fields the launcher's code reads have names; none is the original's.
class FrameworkConfig {
public:
    FrameworkConfig()
        : pad_0(0xffffff), m_frameRate(30.0f), m_memorySize(0x400), m_procMemSize(0x1d00000), m_procMemAlignment(0x20),
          pad_1c(0x400), pad_20(0x400), pad_24(0x400), pad_28(0x800), pad_2c(0x600), pad_30(0x1000), pad_34(0x4a),
          m_lang(0), m_flag(false) {}

    unsigned int pad_0;
    float m_frameRate;  // 0x04 30 by default (the name is not the original's)
    // 0x08 FrameworkMemory::initialize's second (the launcher's build thread; the name is not the original's)
    unsigned int m_memorySize;
    // 0x10, 0x18 the size and alignment of the memory section 5 the build thread makes (MemorySectionInfo's
    // m_size and m_alignment; the names are not the original's)
    unsigned long m_procMemSize;
    unsigned int m_procMemAlignment;
    unsigned int pad_1c;
    unsigned int pad_20;
    unsigned int pad_24;
    unsigned int pad_28;
    unsigned int pad_2c;
    unsigned int pad_30;
    unsigned int pad_34;
    // 0x38 the language Framework::initialize selects when "bdat/jp.bin" is there (the name is not the original's)
    unsigned int m_lang;
    // 0x3C set: Framework::initialize selects the device's language (DevSettingNx's mode 2) and its update thread runs
    // ColiManager::postUpdate (the name is not the original's)
    bool m_flag;
};
}  // namespace fw

#endif
