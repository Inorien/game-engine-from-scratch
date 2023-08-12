# Game Engine From Scratch in 2 weeks

Why:
----
I like games and thought it would be a fun project to see if I could write one from nothing in two weeks.

This project has only OpenGL as an external dependency.

I have never written a game engine before and am approaching the challenge based on some experience with Unity and intuition.

What:
----
 - Renderer (IMPLEMENTED)
 - Keyboard control (IMPLEMENTED via gl callbacks)
 - Mouse control (disabled pending refactor)
 - Sound (not implemented)
 - Engine config (not implemented)
 - Sample game (not implemented)

Todo:
----
 - ~~everything up to now~~
 - player-controllable icon rendered
   - icon interaction with map element (collision,)
 - UI
 - the faintest hint of game logic
 - 


Improvements/bugfixes:
-----
- Fix camera bug (?) where mouse left/right is randomly inverted on startup
- Improve marshalling of render data, reduce overhead
- organise class methods into startup/runtime/shutdown sections