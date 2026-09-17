#pragma once

namespace Input {
enum class Action {
  None,

  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,

  Shoot,
  Reload,

  Quit
};

Action poll();

} // namespace Input
