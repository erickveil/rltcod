#ifndef INPUTCONTROLS_H
#define INPUTCONTROLS_H

#include <QDebug>
#include <QtGlobal>

#include "libtcod.hpp"

#include "messagebox.h"

class InputControls
{
    bool _isShift = false;
    MessageBox _currentMessageBox;

public:
    enum InputMode { INPUT_MODE_STANDARD, INPUT_MODE_MSGBOX };
    InputMode CurrentMode = INPUT_MODE_STANDARD;

    char SaveKey = 's';
    TCOD_keycode_t SaveModifierKey = TCODK_SHIFT;



    InputControls();

    /**
     * @brief captureInput
     *
     * Manages all user input
     *
     * @note Documentation requests that this all run after the
     * TCODConsole::flush call.
     */
    void captureInput();
    void setMessageBox(MessageBox &msgBox);

private:
    void _runStandardInputMode();
    void _runMsgBoxInputMode();
    void _runShiftedKeyPress(TCOD_key_t &key, TCOD_mouse_t &mouse);
    void _runUnmodifiedKeyPress(TCOD_key_t &key, TCOD_mouse_t &mouse);
    bool _validateMessageBox();
};

#endif // INPUTCONTROLS_H
