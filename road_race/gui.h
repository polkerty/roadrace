#ifndef GUI_H
#define GUI_H

#include "ui_roadrace.h"
#include "roadrace.h"
#include "gamemodel.h"

#include "square.h"

class Square;

class GuiManager {

private:
    static GuiManager *instance_;
    Ui::RoadRace *ui;

    GuiManager(){}
 public:
    static GuiManager& instance();
    void setUi ( Ui::RoadRace *ui_ ) { ui = ui_; }
    Ui::RoadRace *getUi ( ) { return ui; }

    ~GuiManager() { delete instance_; }

    void init();
    void generateSquareGrid();
    void fillResourceList();
    QPixmap setmap(Square *sq, int size);
};


#endif // GUI_H
