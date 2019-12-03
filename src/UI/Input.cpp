#include "Input.hpp"

#include "Debugging/Log.hpp"

/*glm::vec2 Input::GetMousePosition() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return conv::screenCoordFromPixelCoord(x, y);
}*/

bool Input::KeyIsDown(Key key) {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//if (auto specialKey = std::get_if<SpecialKey>(&key)) { //Check if it's a special key
		//switch (*specialKey)
		switch(key)
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
		default:
			spdlog::error("[Input::keyIsDown] reached default case");
			return false;
			break;
		}
	//}
	//spdlog::error("[Input::keyIsDown] char keys not supported yet");
}