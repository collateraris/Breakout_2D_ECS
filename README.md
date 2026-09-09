# Breakout 2D — OpenGL & ECS

**English** | [Русский](README.ru.md)

A C++17 implementation of Breakout built around a custom **Entity Component System (ECS)**. The repository combines a playable 2D game with engine modules for rendering, collision detection, input, audio, UI, resource loading, and memory management.

Move the paddle, keep the ball in play, and clear every destructible brick. The game includes four selectable levels, falling power-ups, a particle trail, and shader-based post-processing.

![Breakout gameplay, level selection, and post-processing effects](assets/readme/breakout.png)

[Features](#features) · [Controls](#controls) · [Build and run](#build-and-run) · [Architecture](#architecture) · [Configuration](#configuration) · [Level format](#level-format)

## Features

- **Classic Breakout gameplay:** solid and destructible bricks, paddle-dependent bounce direction, a lives counter, and win / game-over states.
- **Four selectable levels:** Standard, A few small gaps, Space invader, and Bounce galore.
- **Menus and pause:** choose a level before playing, pause a run, or return to the menu and reset it.
- **OpenGL rendering:** instanced sprites, a particle trail, framebuffer post-processing, and text rendered with FreeType.
- **Audio:** background music and collision sound effects through irrKlang.
- **Custom ECS:** per-type component pools, components shared through prefabs, and separate gameplay, physics, and rendering systems.
- **Editable assets and settings:** XML configuration and plain-text level grids.

## Controls

| Context | Key | Action |
| --- | --- | --- |
| Main menu | `A` / `D` | Select the previous / next level |
| Main menu | `Enter` / `Space` | Start the selected level |
| In game | `A` / `D` | Move the paddle left / right |
| In game | `Space` | Launch a ball attached to the paddle |
| In game | `Enter` / `Esc` | Pause |
| Paused | `Enter` | Resume |
| Paused | `Esc` | Reset the run and return to the main menu |
| Win / game-over screen | `Enter` / `Space` | Return to the main menu |

Close the game window to exit. Clearing all destructible bricks wins the selected level; losing all lives ends the run. The starting number of lives is configurable and is set to **5** in `assets/config.xml`.

### Power-ups

Catch falling pickups with the paddle. The code defines six types; their current behavior is:

| Type | Behavior |
| --- | --- |
| Sticky | The ball sticks on its next paddle collision; press `Space` to launch it again. |
| Pad Size Increase | Temporarily expands the paddle to 1.5 times its configured width. |
| Confuse | Temporarily flips the scene on both axes and inverts its colors. |
| Chaos | Temporarily applies an edge filter and animated texture offsets. |
| PassThrough | Temporarily disables the ball's collision responses with bricks and the paddle, including brick destruction. |
| Speed | The pickup and speed-changing functions exist, but activation is commented out and collecting it does not increase speed. |

See [PowerUpSystem.cpp](source/sys_gameplay/PowerUpSystem.cpp) for spawning, activation, and timers. The table describes the current implementation, including the unfinished Speed and PassThrough behavior.

## Build and run

### Requirements

- **Windows**, with an **x86 / Win32** build target.
- **Visual Studio 2019** with the **Desktop development with C++** workload, the **MSVC v142** toolset, and a Windows SDK. The supplied generator targets VS 2019.
- A graphics driver that supports **OpenGL 4.3 Core**; the shaders use GLSL 4.30.

Premake and the third-party headers, sources, libraries, and runtime DLLs used by the project are included in the repository. No package-manager installation step is required.

### Generate and build

1. Clone or extract the repository into a directory **without spaces**: the existing post-build commands contain unquoted paths.
2. From the repository root, run:

   ```powershell
   .\generate.bat
   ```

3. Open `.gen/prj/Breakout.sln`, or use the generated `Breakout.lnk` shortcut.
4. Set **Game** as the startup project.
5. Select **Release | Win32** or **Debug | Win32**, then build the solution.

Alternatively, after generation, build from a Visual Studio Developer Command Prompt:

```bat
msbuild .gen\prj\Breakout.sln /m /p:Configuration=Release /p:Platform=Win32
```

The bundled Premake is **5.0.0-alpha15**. If using a newer Visual Studio, open the generated VS 2019 solution and either install its v142 toolset or retarget the solution to an installed toolset and SDK. Keep the **Win32** platform: the supplied build scripts and binary dependencies target x86. The bundled Premake does not provide a `vs2022` action.

### Launch

The post-build step copies the executable, runtime DLLs, and `assets/` into `.bin/`. From the repository root, launch a Release build with:

```powershell
Set-Location .bin
.\Breakout.exe
```

For a Debug build, run `Breakout-d.exe` from the same directory.

**The working directory must contain `assets/`.** Configuration and resource paths are relative to it. When debugging in Visual Studio, `$(ProjectDir)` works after a successful build because the post-build step also copies assets into `.gen/prj/assets/`.

### Troubleshooting

| Symptom | Check |
| --- | --- |
| Missing MSVC toolset or Windows SDK | Install the toolset / SDK named by the generated solution, or retarget it in Visual Studio. |
| Linker reports an architecture mismatch | Use **Win32**, matching the bundled libraries. |
| Missing `irrKlang.dll`, `ikpMP3.dll`, or `freetype.dll` | Check that the post-build copy succeeded and the DLLs are beside the executable. |
| Configuration, textures, or levels cannot be loaded | Launch from `.bin/` and check that its `assets/` directory is present. |
| GLFW window creation or shader initialization fails | Check OpenGL 4.3 support in the active graphics driver. |
| Asset edits do not appear | Refresh the asset copy in the working directory, then restart the game. |

## Architecture

The entry point is [game.cpp](source/game/game.cpp). [GameEngine](source/game/gameEngine.cpp) initializes the window, resources, and systems, while [ECSBreakout](source/game/ECSBreakout.cpp) creates component pools, the game world, and keyboard-driven state transitions.

The main loop updates **physics → gameplay → rendering**, swaps the event buffers, then polls window events and swaps the display buffers. Physics and gameplay update only in the active game state. Rendering draws sprites and particles, applies post-processing, then draws the UI.

### How the ECS is organized

- **Entities** have numeric IDs and references to their components, managed by `EntityManager`.
- **Components** hold data such as transforms, colliders, movement, health, and sprite properties. `ComponentManager` stores each type in a fixed-capacity free-list pool.
- **Prefabs** allow several entities to reference one shared component. Bricks, for example, share sprite data while keeping individual transforms and, for destructible bricks, colors. The renderer batches these shared sprites into instanced draws.
- **Systems** implement behavior over component data. `SystemManager` creates system instances; the engine and its parent systems control their update order.
- **Events** use multicast delegates for notifications such as collisions and level changes, plus two alternating event buffers for queued events.

### Source map

| Path | Responsibility |
| --- | --- |
| [source/game/](source/game/) | Entry point, engine loop, game context, entity creation, level loading, and asset bindings |
| [source/sys_ecs/](source/sys_ecs/) | Entities, components, shared prefabs, and system management |
| [source/sys_gameplay/](source/sys_gameplay/) | Paddle and ball logic, brick destruction, lives, and power-ups |
| [source/sys_physics/](source/sys_physics/) | Circle–rectangle and rectangle–rectangle collision detection |
| [source/sys_animation/](source/sys_animation/) | Sprite and particle rendering, post-processing, and render orchestration |
| [source/lib_multimedia/OGLML/](source/lib_multimedia/OGLML/) | OpenGL wrappers for shaders, textures, sprites, text, particles, and framebuffers |
| [source/sys_input/](source/sys_input/), [source/sys_events/](source/sys_events/) | Keyboard input, delegates, and buffered events |
| [source/sys_gameState/](source/sys_gameState/), [source/sys_ui/](source/sys_ui/) | Game state transitions, menu canvases, and text widgets |
| [source/sys_config/](source/sys_config/), [source/sys_resource/](source/sys_resource/) | XML configuration, asset IDs, loading, and resource managers |
| [source/sys_audio/](source/sys_audio/), [source/sys_telemetry/](source/sys_telemetry/) | Music, sound effects, and console logging |
| [source/sys_memory/](source/sys_memory/) | Object pools and a linear allocator |
| [source/sys_profile/](source/sys_profile/) | Placeholder module for profiling |
| [assets/](assets/) | Configuration, levels, shaders, textures, fonts, sounds, music, and screenshots |
| [libraries/](libraries/) | Bundled third-party dependencies |
| [make/](make/) | Premake executable and Lua build definitions |

Generated projects, intermediate files, and binaries live in `.gen/`; `.bin/` contains the copied runtime files. Both directories are ignored by Git.

### Dependencies

| Dependency | Use in this project |
| --- | --- |
| OpenGL + GLEW | Graphics API and OpenGL function loading |
| GLFW | Window, graphics context, keyboard events, and timing |
| GLM | Graphics math |
| stb_image | Image decoding |
| FreeType | Font loading and glyph rasterization |
| irrKlang | Music and sound playback, including the MP3 plugin |
| tinyxml2 | XML parsing |
| Premake | Visual Studio solution and project generation |

## Configuration

[assets/config.xml](assets/config.xml) is loaded at startup. It contains:

| Section | Settings |
| --- | --- |
| `window` | Window title and dimensions; configured as 800 × 600 |
| `FPS` | Frame-pacing setting read by the main loop |
| `components` | Component type IDs and fixed pool capacities |
| `gameMaps` | Level entries and `.lvl` paths |
| `assets` | Shader, texture, font, sound, and music IDs and paths |
| `initData` | Paddle and ball sizes / velocities, pickup size / velocity, and starting lives |

For example, edit the existing `playerLives` entry to change the starting lives:

```xml
<init id="6" name="playerLives" val1="5" val2="0"></init>
```

Keep numeric IDs consistent with the C++ enums. Level entries are accessed by their position in `gameMaps`, so preserve their order as well. Source assets are copied during the game's post-build step; after editing them, rebuild the **Game** project or copy the changed files into the runtime `assets/` directory, then restart.

## Level format

Levels in [assets/levels/](assets/levels/) are rectangular grids of space-separated integers:

```text
1 1 1 1 1 1
2 2 0 0 2 2
3 3 4 4 3 3
5 5 5 5 5 5
```

| Value | Tile |
| --- | --- |
| `0` | Empty space |
| `1` | Solid, indestructible brick |
| `2` | Blue destructible brick |
| `3` | Green destructible brick |
| `4` | Yellow destructible brick |
| `5` | Orange destructible brick |

[GameMaps.cpp](source/game/GameMaps.cpp) scales the grid to the window width and the upper half of the window height. Use equal-length, non-empty rows and values from `0` to `5`.

Edit `1.lvl` through `4.lvl` to change the selectable levels. `0.lvl` is associated with the `None` enum value and is excluded from menu selection. Adding more selectable levels also requires updating `EGameMapLevels` in [GameMaps.h](source/game/GameMaps.h) and the ordered `gameMaps` entries in the configuration.

For larger maps, increase the relevant component pools, especially `Transform`, `Collider`, and `SpriteColor`, leaving room for the paddle, ball, background, and pickups. Pools have fixed capacities and do not grow automatically.

## Implementation notes

- The supplied build setup targets Windows and x86; other platforms need build and dependency changes.
- Speed activation is disabled, and PassThrough currently bypasses paddle collisions and brick destruction as described above.
- The renderer includes a Shake post-effect implementation, but normal gameplay does not currently activate it.
- `sys_profile` contains a placeholder rather than an implemented profiler.

## Inspiration

The original README credits:

- [LearnOpenGL — Breakout](https://learnopengl.com/In-Practice/2D-Game/Breakout)
- [Entity Component Systems & Data Oriented Design lecture](http://aras-p.info/texts/files/2018Academy%20-%20ECS-DoD.pdf)
