#ifndef CLASSES_ML_CONTROLLERAPPLET_H
#define CLASSES_ML_CONTROLLERAPPLET_H

namespace ml {

// the controller support applet (fw::PadManager::updateControlPadNo shows it)
class ControllerApplet {
public:
    // shows the applet in single-player mode and selects the chosen controller; true when it succeeded
    static bool showApplet();
};

}  // namespace ml

// the shop applet calls next to it (gf::GfMenuObjAnnounce::MainListener::reciveEvent calls both): show the add-on content list or the
// information page of one of two application ids picked by the flag; the flag's meaning and the names are unknown
bool fn_7100698EE0(int);
bool fn_7100698F20(int);

#endif
