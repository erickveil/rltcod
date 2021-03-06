#include "inputcontrols.h"

InputControls::InputControls()
{

}

void InputControls::captureInput()
{
    if (CurrentMode == INPUT_MODE_STANDARD) { _runStandardInputMode(); }
    else if (CurrentMode == INPUT_MODE_MSGBOX) { _runMsgBoxInputMode(); }

}

void InputControls::setMessageBox(MessageBox *msgBox)
{
    _currentMessageBox = msgBox;
}

void InputControls::_runStandardInputMode()
{
    TCOD_key_t key;
    TCOD_mouse_t mouse;
    TCOD_event_t inputEvent =
            TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);

    if (inputEvent == TCOD_EVENT_KEY_PRESS) {
        if (key.vk == TCODK_SHIFT) { _isShift = true; }
        if (_isShift) { _runShiftedKeyPress(key, mouse); }
        if (!_isShift) { _runUnmodifiedKeyPress(key, mouse); }
    }

    if (inputEvent == TCOD_EVENT_KEY_RELEASE) {
        if (key.vk == TCODK_SHIFT) { _isShift = false; }
    }
}

void InputControls::_runMsgBoxInputMode()
{
    TCOD_key_t key;
    TCOD_mouse_t mouse;
    TCOD_event_t inputEvent =
            TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
    char continueKey = ' ';
    TCOD_keycode_t acceptKey = TCODK_ENTER;
    TCOD_keycode_t cancelKey = TCODK_ESCAPE;

    if (inputEvent == TCOD_EVENT_KEY_PRESS) {
        if (!_validateMessageBox()) { return; }

        if (key.c == continueKey) { _currentMessageBox->continueBox(); }
        if (key.vk == acceptKey
                && !_currentMessageBox->isContinued()) {
            _currentMessageBox->hide();
            CurrentMode = INPUT_MODE_STANDARD;
            if (_currentMessageBox->IsCallbackSet) {
                _currentMessageBox->runCallback();
            }
        }
        if (key.vk == cancelKey
                && _currentMessageBox->IsCancelable
                && !_currentMessageBox->isContinued()) {
            _currentMessageBox->hide();
            CurrentMode = INPUT_MODE_STANDARD;
        }
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

bool InputControls::_validateMessageBox()
{
    if (_currentMessageBox->isNull()) {
        qWarning() << "No message box supplied in Message Box Input mode.";
        return false;
    }
    return true;
}

