#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QString>
#include <QStringList>
#include <QtMath>

#include "libtcod.hpp"

enum BoxPosition {POS_TOP_LEFT, POS_TOP_CENTER, POS_TOP_RIGHT, POS_MIDDLE_LEFT,
              POS_MIDDLE_CENTER, POS_MIDDLE_RIGHT, POS_BOTTOM_LEFT,
              POS_BOTTOM_CENTER, POS_BOTTOM_RIGHT, POS_ABSOLUTE};

class MessageBox
{
    bool isDisplayed = false;

public:
    char BorderHoriz = '-';
    char BorderVert = '|';
    char BorderTL = '+';
    char BorderTR = '+';
    char BorderBL = '+';
    char BorderBR = '+';
    char FillChar = ' ';

    TCODColor FillColor = TCODColor::grey;
    TCODColor FillBack = TCODColor::black;
    TCODColor BorderColor = TCODColor::grey;
    TCODColor BorderBack = TCODColor::black;
    TCODColor TextColor = TCODColor::white;
    TCODColor TextBack = TCODColor::black;

    int margin = 3;
    int padding = 1;

    int maxHeight = 10;
    int maxWidth = 40;

    int viewWidth = 106;
    int viewHeight = 60;

    BoxPosition position = POS_MIDDLE_CENTER;

    QString message;

    int dimX = 30;
    int dimY = 10;
    int posX = 10;
    int posY = 10;

    MessageBox();
    void drawBox();
    void show();
    void hide();

private:
    void _calcDimensions();
    void _calcPosition();
    QStringList _splitMessageIntoLines();
};

#endif // MESSAGEBOX_H
