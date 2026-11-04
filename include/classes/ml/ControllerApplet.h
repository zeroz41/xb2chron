#ifndef CLASSES_ML_CONTROLLERAPPLET_H
#define CLASSES_ML_CONTROLLERAPPLET_H

namespace ml {

// the controller support applet (fw::PadManager::updateControlPadNo shows it)
class ControllerApplet {
public:
    // shows the applet in single-player mode and selects the chosen controller; true when it succeeded
    static bool showApplet();
};

// the shop applets next to it (gf::GfMenuObjAnnounce::MainListener::reciveEvent calls both; 2.0.0's symbols name
// the classes): show the add-on content list or the information page of one of two application ids picked by the
// flag; the flag's meaning is unknown
class ShopAddOnContentApplet {
public:
    static bool showApplet(int flag);
};

class ShopApplicationApplet {
public:
    static bool showApplet(int flag);
};

}  // namespace ml

#endif
