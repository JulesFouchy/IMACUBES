#include "Input.hpp"
#include "Debugging/Log.hpp"
#include "Locator/Locate.hpp"
#include "Renderer/Renderer.hpp"

float Input::m_horizontalDPI;
float Input::m_verticalDPI;

void Input::Initialize()
{
    SDL_GetDisplayDPI(0, nullptr, &m_horizontalDPI, &m_verticalDPI);
}

glm::vec2 Input::MousePositionInInches()
{
    return MousePositionInPixels() / glm::vec2(m_horizontalDPI, m_verticalDPI);
}

glm::vec2 Input::MousePositionInPixels()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(x, Locate::renderer().getHeight() - y);
}

bool Input::KeyIsDown(SpecialKey key)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    switch (key)
    {
    case ALT:
        return state[SDL_SCANCODE_LALT] || state[SDL_SCANCODE_RALT];
        break;
    case CTRL:
        return state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL];
        break;
    case SHIFT:
        return state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT];
        break;
    case SPACE:
        return state[SDL_SCANCODE_SPACE];
        break;
    default:
        spdlog::error("[Input::keyIsDown] reached default case");
        return false;
        break;
    }
}

bool Input::KeyIsDown(SDL_Scancode key)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[key];
}

bool Input::KeyIsDown(char key)
{
    int code = (int)SDL_SCANCODE_A + int(key) - int('a');
    if (code > -1)
        return KeyIsDown((SDL_Scancode)code);
}