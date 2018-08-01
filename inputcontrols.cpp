#include "inputcontrols.h"

InputControls::InputControls()
{

}

void InputControls::captureInput()
{
    TCOD_key_t key;
    TCOD_mouse_t mouse;
    TCOD_event_t inputEvent =
            TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);

    if (inputEvent == TCOD_EVENT_KEY_PRESS) {
        if (key.vk == TCODK_SHIFT) { isShift = true; }
        if (isShift) { _runShiftedKeyPress(key, mouse); }
        if (!isShift) { _runUnmodifiedKeyPress(key, mouse); }
    }

    if (inputEvent == TCOD_EVENT_KEY_RELEASE) {
        if (key.vk == TCODK_SHIFT) { isShift = false; }
    }
}

void InputControls::_runShiftedKeyPress(TCOD_key_t &key, TCOD_mouse_t &mouse)
{
    Q_UNUSED(mouse);
    if (key.c == SaveKey && SaveModifierKey == TCODK_SHIFT) {
        qDebug() << "save key pressed";
    }
}

void InputControls::_runUnmodifiedKeyPress(TCOD_key_t &key, TCOD_mouse_t &mouse)
{
    Q_UNUSED(mouse);
    if (key.c == SaveKey && SaveModifierKey == TCODK_NONE) {
        qDebug() << "s key pressed";
    }
}

