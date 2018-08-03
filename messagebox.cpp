#include "messagebox.h"

MessageBox::MessageBox()
{

}

void MessageBox::drawBox()
{
    if (!isDisplayed) { return; }

    int viewWidth = TCODConsole::root->getWidth();
    int viewHeight = TCODConsole::root->getHeight();

    // Set Position of box
    if (Postion == POS_TOP_LEFT) {
        PosX = Margin;
        PosY = Margin;
    }
    else if (Postion == POS_TOP_CENTER) {
        PosX = qRound(((float)viewWidth / 2.0f) - ((float)MaxWidth / 2.0f));
        PosY = Margin;
    }
    else if (Postion == POS_TOP_RIGHT) {
        PosX = viewWidth - MaxWidth - Margin;
        PosY = Margin;
    }
    else if (Postion == POS_BOTTOM_LEFT) {
        PosX = Margin;
        PosY = viewHeight - MaxHeight - Margin;
    }
    else if (Postion == POS_BOTTOM_CENTER) {
        PosX = qRound(((float)viewWidth / 2.0f) - ((float)MaxWidth / 2.0f));
        PosY = viewHeight - MaxHeight - Margin;
    }
    else if (Postion == POS_BOTTOM_RIGHT) {
        PosX = viewWidth - MaxWidth - Margin;
        PosY = viewHeight - MaxHeight - Margin;
    }
    else if (Postion == POS_MIDDLE_LEFT) {
        PosX = Margin;
        PosY = qRound(((float)viewHeight / 2.0f) - ((float)MaxHeight / 2.0f));
    }
    else if (Postion == POS_MIDDLE_CENTER) {
        PosX = qRound(((float)viewWidth / 2.0f) - ((float)MaxWidth / 2.0f));
        PosY = qRound(((float)viewHeight / 2.0f) - ((float)MaxHeight / 2.0f));
    }
    else if (Postion == POS_MIDDLE_RIGHT) {
        PosX = viewWidth - MaxWidth - Margin;
        PosY = qRound(((float)viewHeight / 2.0f) - ((float)MaxHeight / 2.0f));
    }

    // Draw Box
    for (int x = 0; x < MaxWidth + 1; ++x) {
        for (int y = 0; y < MaxHeight; ++y) {
            bool isLeft = (x == 0);
            bool isRight = (x == MaxWidth);
            bool isTop = (y == 0);
            bool isBottom = (y == MaxHeight - 1);
            bool isTL = (isLeft && isTop);
            bool isTR = (isRight && isTop);
            bool isBL = (isLeft && isBottom);
            bool isBR = (isRight && isBottom);
            int boxPosX = x + PosX;
            int boxPosY = y + PosY;
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
    QString printMsg = QString("%c") + Message + "%c";
    int center = qFloor((float)MaxWidth / 2.0f);
    int border = 1;
    int textAreaPosX = PosX + center;
    int textAreaPosY = PosY + border + Padding;
    int textAreaMaxW = MaxWidth - 2 - Padding;
    int textAreaMaxH = MaxHeight - 2 - (Padding * 2);
    TCODConsole::root->printRectEx(
                textAreaPosX, textAreaPosY,
                textAreaMaxW, textAreaMaxH,
                TCOD_BKGND_SET,
                TCOD_CENTER,
                printMsg.toLocal8Bit(),
                TCOD_COLCTRL_1,
                TCOD_COLCTRL_STOP);

    // Continue button
    if (isContinued()) { _drawContinueButton(); }

    // Accept button
    if (!isContinued()) { _drawAcceptButton(); }

    // Cancel button
    if (!isContinued() && IsCancelable) { _drawCancelButton(); }

}

void MessageBox::show()
{
    isDisplayed = true;
}

void MessageBox::hide()
{
    isDisplayed = false;
}

void MessageBox::continueBox()
{
    if (!isContinued()) { return; }
    QString nextMessage = _getContinuingText();
    Message = nextMessage;
}

bool MessageBox::isNull()
{
    return Message.isEmpty();
}

QStringList MessageBox::_splitMessageIntoLines()
{
    QStringList lineList;
    int textLength = Message.size();
    int textAreaWidth = MaxWidth - (Padding * 2) - 2;
    if(textLength > textAreaWidth) {
        QStringList wordList = Message.split(" ");
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
        lineList.append(Message);
    }
    return lineList;
}

void MessageBox::_drawContinueButton()
{
    int buttonX = PosX + 1;
    int buttonY = PosY + MaxHeight - 1;
    TCODConsole::root->print(buttonX, buttonY, "[Space]");

}

void MessageBox::_drawAcceptButton()
{
    int buttonX = PosX + MaxWidth - 1;
    int buttonY = PosY + MaxHeight - 1;
    TCODConsole::root->printEx(buttonX, buttonY, TCOD_BKGND_NONE, TCOD_RIGHT,
                               "[Enter]");
}

void MessageBox::_drawCancelButton()
{
    int buttonX = PosX + MaxWidth - 8;
    int buttonY = PosY + MaxHeight - 1;
    TCODConsole::root->printEx(buttonX, buttonY, TCOD_BKGND_NONE, TCOD_RIGHT,
                               "[Esc]");

}

QString MessageBox::_getContinuingText()
{
    QString lastLine = _getLastLineText();
    QString originalMsg = Message;

    int strPos = originalMsg.indexOf(lastLine);
    strPos += lastLine.size();

    QString newMsg = originalMsg.mid(strPos);
    return newMsg;
}

QString MessageBox::_getLastLineText()
{
    int lineStartX = PosX + 1 + Padding;
    int lineStartY = PosY + MaxHeight - 2 - Padding;
    int textWidth = MaxWidth - 2 - (Padding * 2);

    QString lastLine;
    for (int i = 0; i < textWidth; ++i) {
        int x = lineStartX + i;
        int y = lineStartY;
        char c = TCODConsole::root->getChar(x, y);
        lastLine.append(c);
    }
    lastLine = lastLine.trimmed();

    //qDebug() << lastLine;
    return lastLine;

}

bool MessageBox::isContinued()
{
    int border = 1;
    int textAreaPosX = PosX + border + Padding;
    int textAreaPosY = PosY + border + Padding;
    int textAreaMaxW = MaxWidth - 2 - Padding;
    int textAreaMaxH = MaxHeight - 2 - (Padding * 2);

    int lineHeight = TCODConsole::root->getHeightRect(
                textAreaPosX, textAreaPosY,
                textAreaMaxW, textAreaMaxH,
                Message.toLocal8Bit());

    return (lineHeight > textAreaMaxH);
}

void MessageBox::setCallback(std::function<void()> callback)
{
    _callback = callback;
    IsCallbackSet = true;
}

void MessageBox::runCallback()
{
    if (!IsCallbackSet) { return; }
    _callback();
}
