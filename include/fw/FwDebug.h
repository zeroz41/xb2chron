#ifndef FW_FWDEBUG_H
#define FW_FWDEBUG_H

// the framework's debug drawing switches (fw::debug; the header's name is not the original's)
namespace fw { namespace debug {
void drawCompareZ(bool on);  // GfManager::update turns it on each frame
}}  // namespace fw::debug

#endif
