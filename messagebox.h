#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QString>
#include <QStringList>
#include <QtMath>
#include <QDebug>

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

    int Margin = 3;
    int Padding = 1;

    int MaxHeight = 10;
    int MaxWidth = 40;

    BoxPosition Postion = POS_MIDDLE_CENTER;

    QString Message;

    int PosX = 10;
    int PosY = 10;

    bool IsShowAcceptButton = true;
    bool IsShowCancelButton = false;

    MessageBox();
    void drawBox();
    void show();
    void hide();
    void continueBox();
    bool isNull();


private:
    QStringList _splitMessageIntoLines();
    void _drawContinueButton();
    QString _getContinuingText();
    QString _getLastLineText();
    bool _isContinued();
};

#endif // MESSAGEBOX_H
