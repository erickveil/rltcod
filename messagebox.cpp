#include "messagebox.h"

MessageBox::MessageBox()
{

}

void MessageBox::drawBox()
{
    if (!isDisplayed) { return; }

    /*
    _calcDimensions();
    _calcPosition();

    int textAreaXStart = posX + 1 + padding;
    int textAreaXEnd = (posX + dimX) - 1 - padding;
    int textAreaYStart = posY + 1 + padding;
    int textAreaYEnd = (posY + dimY) - 1 - padding;

    char printChar;
    for (int x = 0; x < dimX; ++x) {
        int drawPosX = posX + x;
        for (int y = 0; y < dimY; ++y) {
            int drawPosY = posY + y;
            bool isTopLeftCorner = (x == 0 && y == 0);
            bool isTopRightCorner = (x == dimX - 1 && y == 0);
            bool isBottomLeftCorner = (x == 0 && y == dimY - 1);
            bool isBottomRightCorner (x == dimX - 1 && y == dimY - 1);
            bool isTopBorder = (y == 0);
            bool isBottomBorder = (y == dimY - 1);
            bool isLeftBorder = (x == 0);
            bool isRightBorder = (x == dimX - 1);
            bool isTopPadding = (y > posY) && (y <= posY + padding);
            bool isBottomPadding =
                    (y < posY + dimX - 1) && (y > posY + dimX - 1 - padding);
            bool isLeftPadding = (x > posX + 1) && (x < posX + 1 + padding);
            bool isRightPadding;
            bool isPadding = isTopPadding || isBottomPadding || isLeftPadding
                    || isRightPadding;
            if (isTopLeftCorner) { printChar = BorderTL; }


            TCODConsole::root->putCharEx(drawPosX, drawPosY, BorderTL, BorderColor, BorderBack);
        }
    }
    */
    // Set Position
    if (position == POS_TOP_LEFT) {
        posX = margin;
        posY = margin;
    }
    else if (position == POS_TOP_CENTER) {
        posX = qRound(((float)viewWidth / 2.0f) - ((float)maxWidth / 2.0f));
        posY = margin;
    }
    else if (position == POS_TOP_RIGHT) {
        posX = viewWidth - maxWidth - margin;
        posY = margin;
    }
    else if (position == POS_BOTTOM_LEFT) {
        posX = margin;
        posY = viewHeight - maxHeight - margin;
    }
    else if (position == POS_BOTTOM_CENTER) {
        posX = qRound(((float)viewWidth / 2.0f) - ((float)maxWidth / 2.0f));
        posY = viewHeight - maxHeight - margin;
    }
    else if (position == POS_BOTTOM_RIGHT) {
        posX = viewWidth - maxWidth - margin;
        posY = viewHeight - maxHeight - margin;
    }
    else if (position == POS_MIDDLE_LEFT) {
        posX = margin;
        posY = qRound(((float)viewHeight / 2.0f) - ((float)maxHeight / 2.0f));
    }
    else if (position == POS_MIDDLE_CENTER) {
        posX = qRound(((float)viewWidth / 2.0f) - ((float)maxWidth / 2.0f));
        posY = qRound(((float)viewHeight / 2.0f) - ((float)maxHeight / 2.0f));
    }
    else if (position == POS_MIDDLE_RIGHT) {
        posX = viewWidth - maxWidth - margin;
        posY = qRound(((float)viewHeight / 2.0f) - ((float)maxHeight / 2.0f));
    }

    // Draw Box
    for (int x = 0; x < maxWidth + 1; ++x) {
        for (int y = 0; y < maxHeight; ++y) {
            bool isLeft = (x == 0);
            bool isRight = (x == maxWidth);
            bool isTop = (y == 0);
            bool isBottom = (y == maxHeight - 1);
            bool isTL = (isLeft && isTop);
            bool isTR = (isRight && isTop);
            bool isBL = (isLeft && isBottom);
            bool isBR = (isRight && isBottom);
            int boxPosX = x + posX;
            int boxPosY = y + posY;
            if (isTL) {
                TCODConsole::root->putCharEx(
                            boxPosX, boxPosY,
                            BorderTL, BorderColor, BorderBack );
            }
            else if (isTR) {
                TCODConsole::root->putCharEx(
                            boxPosX, boxPosY,
                            BorderTR, BorderColor, BorderBack );
            }
            else if (isBL) {
                TCODConsole::root->putCharEx(
                            boxPosX, boxPosY,
                            BorderBL, BorderColor, BorderBack );
            }
            else if (isBR) {
                TCODConsole::root->putCharEx(
                            boxPosX, boxPosY,
                            BorderBR, BorderColor, BorderBack );
            }
            else if (isTop || isBottom) {
                TCODConsole::root->putCharEx(
                            boxPosX, boxPosY,
                            BorderHoriz, BorderColor, BorderBack );
            }
            else if (isLeft || isRight) {
                TCODConsole::root->putCharEx(
                            boxPosX, boxPosY,
                            BorderVert, BorderColor, BorderBack );
            }
            else {
                TCODConsole::root->putCharEx(
                            boxPosX, boxPosY,
                            FillChar, FillColor, FillBack);
            }
        }
    }

    // Draw Text Area
    TCODConsole::setColorControl(
                TCOD_COLCTRL_1, TextColor, TextBack);
    QString printMsg = QString("%c") + message + "%c";
    int center = qFloor((float)maxWidth / 2.0f);
    int border = 1;
    int textAreaPosX = posX + center;
    int textAreaPosY = posY + border + padding;
    int textAreaMaxW = maxWidth - 2 - padding;
    int textAreaMaxH = maxHeight - 2 - (padding * 2);
    TCODConsole::root->printRectEx(
                textAreaPosX, textAreaPosY,
                textAreaMaxW, textAreaMaxH,
                TCOD_BKGND_SET,
                TCOD_CENTER,
                printMsg.toLocal8Bit(),
                TCOD_COLCTRL_1,
                TCOD_COLCTRL_STOP);



}

void MessageBox::show()
{
    isDisplayed = true;
}

void MessageBox::hide()
{
    isDisplayed = false;
}

void MessageBox::_calcDimensions()
{
    // set box width
    int textLength = message.size();
    int textAreaWidth = maxWidth - (padding * 2) - 2;
    int boxWidth = (textLength > textAreaWidth)
            ? maxWidth
            : textLength + (padding * 2) + 2;

    // cut the message into lines
    QStringList lineList = _splitMessageIntoLines();

    // set box height
    int textAreaHeight = maxHeight - (padding * 2) - 2;
    int boxHeight = (lineList.size() < textAreaHeight)
            ? lineList.size() + (padding * 2) + 2
            : maxHeight;
    dimX = boxWidth;
    dimY = boxHeight;
}

void MessageBox::_calcPosition()
{
    int x = 0;
    int y = 1;

    _calcDimensions();
    int width = dimX;
    int height = dimY;
    int pos[2];

    switch(position) {
    case POS_TOP_LEFT:
        pos[x] = margin;
        pos[y] = margin;
        break;
    case POS_TOP_CENTER:
        pos[y] = margin;
        pos[x] = (qRound((float)viewWidth / 2.0f)) - (qRound((float)width / 2.0f));
        break;
    case POS_TOP_RIGHT:
        pos[y] = margin;
        pos[x] = viewWidth - width - margin;
        break;
    case POS_MIDDLE_LEFT:
        pos[x] = margin;
        pos[y] = (qRound((float)viewHeight / 2.0f)) - (qRound((float)height / 2.0f));
        break;
    case POS_MIDDLE_CENTER:
        pos[x] = (qRound((float)viewWidth / 2.0f)) - (qRound((float)width / 2.0f));
        pos[y] = (qRound((float)viewHeight / 2.0f)) - (qRound((float)height / 2.0f));
        break;
    case POS_MIDDLE_RIGHT:
        pos[x] = viewWidth - width - margin;
        pos[y] = (qRound((float)viewHeight / 2.0f)) - (qRound((float)height / 2.0f));
        break;
    case POS_BOTTOM_LEFT:
        pos[x] = margin;
        pos[y] = viewHeight - height - margin;
        break;
    case POS_BOTTOM_CENTER:
        pos[x] = (qRound((float)viewWidth / 2.0f)) - (qRound((float)width / 2.0f));
        pos[y] = viewHeight - height - margin;
        break;
    case POS_BOTTOM_RIGHT:
        pos[x] = viewWidth - width - margin;
        pos[y] = viewHeight - height - margin;
        break;
    default:
        pos[x] = margin;
        pos[y] = margin;
    }
    posX = pos[x];
    posY = pos[y];
}

QStringList MessageBox::_splitMessageIntoLines()
{
    QStringList lineList;
    int textLength = message.size();
    int textAreaWidth = maxWidth - (padding * 2) - 2;
    if(textLength > textAreaWidth) {
        QStringList wordList = message.split(" ");
        QString testLine;
        QString finalLine;
        for (int i = 0; i < wordList.size(); ++i) {
            testLine.append(lineList[i]);
            if (testLine.size() > textAreaWidth) {
                --i;
                lineList.append(finalLine);
                finalLine = "";
                testLine = "";
            }
            else {
                finalLine = testLine + " ";
            }
        }
    }
    else {
        lineList.append(message);
    }
    return lineList;
}

