#include "gui.h"
#include "roadrace.h"
#include "gamemodel.h"
#include "ui_roadrace.h"

#include "square.h"
#include "player.h"
#include <QLabel>

class Square;
class Player;

GuiManager *GuiManager::instance_ = NULL;

GuiManager& GuiManager::instance() {
    if (instance_ == NULL ) {
        instance_ = new GuiManager();
    }

    return *instance_;
}

void GuiManager::init() {
    fillResourceList();
    generateSquareGrid();
}

void GuiManager::fillResourceList(){
    if ( Game::instance().getCurPlayer() == NULL ) {
        std::cout << "There is no current player. Oopsies!" <<std::endl;
        return;
    }
    ui->Go1->setText(QString::fromStdString(to_string(Game::instance().getCurPlayer()->getGold())));
    ui->Wa1->setText(QString::fromStdString(to_string(Game::instance().getCurPlayer()->getWater())));
    ui->wo1->setText(QString::fromStdString(to_string(Game::instance().getCurPlayer()->getWood())));
    ui->Sto1->setText(QString::fromStdString(to_string(Game::instance().getCurPlayer()->getStone())));

}

void GuiManager::generateSquareGrid() {
    std::cout << getUi()->label->text().toStdString() << std::endl;


    ui->gameLayout->setContentsMargins(100,100,100,100);
    vector<vector<Square*>> squaresList = Game::instance().getSquares();


    vector<vector<Square*>> squares = Game::instance().getSquares();

    if ( squares.size() == 0) {
        return;
    }


    int border=5;
    int size = ui->gridLayoutWidget->width()/squares.size()/2;

    Square::setSize(size);
    Square::setBorder(border);

    for(size_t index = 0;index<squares.size();index++){
        for (size_t sub_index = 0; sub_index <squares.at(index).size(); sub_index++ ) {

            Square *proc = squares.at(index).at(sub_index);

            SquareLabel *lbl = new SquareLabel(proc,ui->gridLayoutWidget);

            proc->setLabel(lbl);
            QPixmap map = setmap(proc, size);
            lbl->setPixmap(map);
            lbl->setFixedHeight(size);
            lbl->setFixedWidth(size);
            Player *owner = proc->getOwner();
            std::string color = owner == NULL ? "black" : owner->getColor();
            lbl->setStyleSheet("border:" + QString::fromStdString(to_string(border)) +  "px solid " + QString::fromStdString(color) + ";\n");
            ui->gameLayout->addWidget(lbl,index,sub_index,0);


            proc->setX(index);
            proc->setY(sub_index);
            lbl->show();
        }
        //ui->gameLayout->set(index,size);
        //ui->gameLayout->setRowMinimumHeight(index,size);

    }
     ui->gameLayout->setSpacing(0);
}
QPixmap GuiManager::setmap(Square *sq, int size){
    string image = sq->getImage();

    if(image == "Fo"){
        QPixmap map(":/forrest");
        QPixmap result = map.scaled(QSize(size,size), Qt::KeepAspectRatio);

        return result;
    }
    if(image == "Ca"){
        QPixmap map(":/canyon");
        QPixmap result = map.scaled(QSize(size,size), Qt::KeepAspectRatio);
        return result;
    }
    if(image == "Ri"){
        QPixmap map(":/water");
          QPixmap result = map.scaled(QSize(size,size), Qt::KeepAspectRatio);
        return result;
    }
    if (image == "Mo"){
        QPixmap map(":/mountain");
          QPixmap result = map.scaled(QSize(size,size), Qt::KeepAspectRatio);
        return result;
    }
    if(image == "Pl"){
        QPixmap map(":/grass");
          QPixmap result = map.scaled(QSize(size,size), Qt::KeepAspectRatio);
        return result;
    }
}
