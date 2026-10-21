#include "classes/ai/AiData.h"
#include "classes/apps/FrameworkLauncher.h"
#include "classes/apps/LauncherApp.h"

namespace apps {

void FrameworkLauncher::rdkReaded(const char*, void*, int) {}

void LauncherApp::wkUpdate() {}

void LauncherApp::wkTail() {}

void LauncherApp::errcbCallback(ml::CPUID, unsigned long) {}

}  // namespace apps

namespace ai {

AiData::~AiData() {}

}  // namespace ai
