#pragma once

#include "../game/game.hpp"

namespace Renderer {
enum class RenderResult { Continue, Quit };

bool init();
void shutdown();

RenderResult render(const Game::GameState &state);

} // namespace Renderer
