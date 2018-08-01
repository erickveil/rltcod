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
    TCODConsole::root->setAlignment(TCOD_CENTER);
    TCODConsole::root->setColorControl(TCOD_COLCTRL_1, TextColor, TextBack);
    TCODConsole::root->printRect(posX, posY, maxWidth, maxHeight,
                           "String with a %cred%c word.",
                           TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);



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

