#ifndef INPUTCONTROLS_H
#define INPUTCONTROLS_H

#include <QDebug>

#include "libtcod.hpp"

class InputControls
{
public:
    InputControls();
    bool isShift = false;

    char SaveKey = 's';
    TCOD_keycode_t SaveModifierKey = TCODK_SHIFT;


    /**
     * @brief captureInput
     *
     * Manages all user input
     *
     * @note Documentation requests that this all run after the
     * TCODConsole::flush call.
     */
    void captureInput();

private:
    void _runShiftedKeyPress(TCOD_key_t &key, TCOD_mouse_t &mouse);
    void _runUnmodifiedKeyPress(TCOD_key_t &key, TCOD_mouse_t &mouse);
};

#endif // INPUTCONTROLS_H
