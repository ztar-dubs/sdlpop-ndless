# SDLPoP-Ndless - Prince of Persia for TI-Nspire CX

Port of [SDLPoP](https://github.com/NagyD/SDLPoP) (Prince of Persia) for the TI-Nspire CX / CX CAS / CX II calculators via [Ndless](https://ndless.me/).

Based on SDLPoP v1.24 RC.

## Requirements

### To build

- [Ndless SDK](https://github.com/ndless-nspire/Ndless) with nspire-gcc toolchain
- nSDL (SDL 1.2 for Ndless)
- Make

### To run

- TI-Nspire CX, CX CAS, CX II, or CX II CAS calculator
- [Ndless](https://ndless.me/) installed on the calculator
- Original Prince of Persia DOS game data files (`.DAT` files)

## Installation on calculator

1. Copy the `prod/` directory content to your calculator:
   ```
   <calculator>/ndless/prince.tns
   <calculator>/ndless/data/*.DAT.tns
   ```
2. The executable (`prince.tns`) and the `data/` folder must be in the **same directory**.
3. Launch `prince.tns` from Ndless.

### Game data files

The `.DAT` files are from the original DOS Prince of Persia game. They are **not included** in this repository. You need to obtain them from a legal copy of the game. Audio files (`DIGISND*.DAT`, `IBM_SND*.DAT`, `MIDISND*.DAT`) are not needed (audio is disabled on Nspire).

## Controls

| Nspire Key                | Action                              |
| ------------------------- | ----------------------------------- |
| **Arrows** or **2/4/6/8** | Movement                            |
| **Ctrl**                  | Shift (grab / careful step / fight) |
| **7**                     | Jump up+left                        |
| **9**                     | Jump up+right                       |
| **Tab**                   | Quick save                          |
| **Del**                   | Quick load                          |
| **Enter**                 | Confirm / Start game                |
| **Esc**                   | Quit game                           |
| **Space**                 | Skip text / cutscene                |
| **R**                     | Restart level                       |
| **Menu**                  | Toggle 320x200 / 320x240 display    |

### Gameplay controls

- **Run**: Left/Right arrow (or 4/6)
- **Jump while running**: Direction + Up (or 8)
- **Standing jump**: Up
- **Crouch**: Down (or 2)
- **Careful step**: Ctrl + direction
- **Grab ledge**: Ctrl (hold)
- **Drink potion**: Ctrl in front of potion
- **Draw sword / Attack**: Ctrl (when enemy is near)
- **Parry**: Ctrl (when enemy attacks)

## Project Structure

```
sdlpop-ndless/
|-- Makefile              # Build system for Ndless
|-- src/                  # SDLPoP original source (modified with #ifdef NSPIRE)
|   |-- main.c            # Entry point (chdir to exe dir on Nspire)
|   |-- config.h          # Feature flags (audio, menu, replay etc. disabled)
|   |-- common.h          # Common includes (alloca, unaligned access fixes)
|   |-- types.h           # Type definitions (__attribute__((packed)) for ARM)
|   |-- data.h / data.c   # Global variables
|   |-- proto.h           # Function prototypes
|   |-- seg000.c          # Game init, title screen, main game flow
|   |-- seg001.c          # Cutscenes, princess room scenes
|   |-- seg002.c          # Character control, auto-moves
|   |-- seg003.c          # Level loading, game loop (play_level_2)
|   |-- seg004.c          # Character actions
|   |-- seg005.c          # Collision detection
|   |-- seg006.c          # Sequence table, animation playback
|   |-- seg007.c          # Tile mechanics (gates, traps, buttons)
|   |-- seg008.c          # Drawing: tiles, sprites, tables (hflip cache)
|   |-- seg009.c          # SDL interface: display, input, audio, file I/O
|   |-- seqtbl.c          # Animation sequence table data
|   |-- options.c         # INI parsing (skipped on Nspire)
|   |-- midi.c            # MIDI playback (compiled but audio disabled)
|   |-- opl3.c            # OPL3 FM synthesis (compiled but audio disabled)
|   |-- stb_vorbis.c      # Vorbis decoder (not compiled on Nspire)
|   |-- menu.c            # In-game menu (not compiled on Nspire)
|   |-- lighting.c        # Lighting effects (not compiled on Nspire)
|   |-- replay.c          # Replay recording (not compiled on Nspire)
|   +-- screenshot.c      # Screenshot capture (not compiled on Nspire)
|-- nspire/               # Nspire platform layer
|   |-- SDL2/SDL.h        # SDL2-to-SDL1.2 compatibility header
|   |-- SDL2/SDL_image.h  # SDL_image stub (not available on Nspire)
|   |-- nspire_compat.c   # Display (stretch, lcd_blit), input, audio stubs
|   |-- nspire_fopen.c    # File I/O wrapper (.tns extension, --wrap linker)
|   +-- nspire_stubs.c    # Stubs for disabled features
+-- prod/                 # Production output
    |-- prince.tns        # Compiled executable
    +-- data/             # Game data files (.DAT.tns)
```

## Technical Details

### Porting approach

The port uses `#ifdef NSPIRE` guards in the original SDLPoP source code to adapt for the TI-Nspire platform. The main changes are:

- **SDL2 to SDL1.2**: A compatibility header (`nspire/SDL2/SDL.h`) provides SDL2 API macros/stubs that map to nSDL (SDL 1.2). SDL2-specific features (renderer, textures, game controllers) are stubbed out.
- **File I/O**: All files on Nspire must have `.tns` extension. The `nspire_fopen.c` wrapper uses the `--wrap` linker flag to intercept `fopen()`, `open()`, `stat()`, and `access()` calls and automatically append `.tns`.
- **Display**: Game renders at 320x200 on a 16-bit RGB565 surface. The Nspire screen is 320x240. Display modes: centered (320x200 with black borders) or stretched (320x240 via precomputed lookup table). Output via `lcd_blit()`.
- **Input**: Nspire keypad is polled directly via `isKeyPressed()` from libndls. Key states are mapped to SDL scancodes used by the game engine.
- **Audio**: Completely disabled (`NO_AUDIO`). All sound loading/playing functions are stubbed.

### ARM unaligned access fixes

The TI-Nspire uses an ARM926EJ-S processor which does not support unaligned memory access. Several fixes were needed:

- All `#pragma pack(push,1)` structs use `__attribute__((packed))` on Nspire (via `PACKED_STRUCT()` macro) so GCC generates safe byte-wise access code.
- The `*(word*)` cast in `play_seq()` (seg006.c) is replaced with byte-by-byte reading (same fix as the PSP port).
- `do_auto_moves()` (seg002.c) reads packed struct fields via `memcpy()`.
- LTO (`-flto`) is disabled as it can lose packed struct information on ARM.
- `SDL_RLEACCEL` is NOT used with `SDL_SetColorKey` - it causes massive slowdown because the colorkey is toggled 40-240 times per frame, triggering full RLE re-encode each time.
- INI file parsing is skipped (the parser dereferences `word*` pointers to packed struct fields).

### Disabled features

The following SDLPoP features are disabled on Nspire (via `config.h`):

- Audio (no speaker on calculator)
- Fade/Flash effects
- In-game menu
- Replay recording/playback
- Screenshots
- Lighting effects
- Joystick/Gamepad support
- Copy protection
- Quick save/load
- Colored torches
- Teleports
- Fast forward
- Debug cheats

### Performance optimizations

- **hflip cache**: Horizontally flipped sprites are cached in the chtab (2x image slots). Computed once, then reused across frames.
- **No SDL_RLEACCEL**: Avoids costly RLE re-encoding on every `SDL_SetColorKey` call.
- **Stretch lookup table**: Vertical stretch 200->240 uses a precomputed `stretch_map[240]` array.
- **Direct LCD output**: Uses `lcd_blit()` for direct framebuffer writes.

### Known issues

- **Palette flicker on cutscenes/title screen**: SDLPoP uses VGA-style palette animation for fade effects. With 16-bit surfaces, palette changes don't affect already-drawn pixels, causing brief color flickering during screen transitions. Gameplay is not affected.
- **Font loading**: "Can't load sprites from resource 1000" message at startup is harmless - the game falls back to its built-in font.

## Credits

- **SDLPoP** by [David Nagy](https://github.com/NagyD/SDLPoP) - the original open-source port of Prince of Persia
- **Prince of Persia** by Jordan Mechner - the original game
- **Ndless** by the [ndless-nspire team](https://github.com/ndless-nspire/Ndless) - jailbreak and SDK for TI-Nspire
- **nSDL** - SDL 1.2 port for Ndless

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details. Same license as the original SDLPoP project.
