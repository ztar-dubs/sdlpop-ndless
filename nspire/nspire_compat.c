/*
 * nspire_compat.c - Nspire-specific replacements for SDL2 functions
 *
 * This file provides Nspire implementations for:
 * - Display initialization (SDL_SetVideoMode instead of SDL2 renderer)
 * - Screen update (SDL_Flip instead of SDL2 textures)
 * - Input handling (Nspire keypad polling)
 * - Audio stubs
 */

#include "common.h"
#include <libndls.h>

/* ---- Nspire screen surface ---- */
static SDL_Surface* nspire_screen = NULL;

/* Flag to block screen updates during transitions */
int nspire_block_update = 0;

/* 0 = 320x200 centered (default), 1 = 320x240 stretched */
static int nspire_stretch_mode = 0;

/* Vertical stretch 200→240: lookup table mapping dst_y → src_y */
static Uint8 stretch_map[240];

/* LCD hardware framebuffer pointer (cached at init) */
static Uint16* lcd_base = NULL;

/* ---- Display ---- */

void nspire_set_gr_mode(byte grmode) {
    (void)grmode;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "ERROR: SDL_Init failed\n");
        exit(1);
    }

    nspire_screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
    if (nspire_screen == NULL) {
        fprintf(stderr, "ERROR: SetVideoMode failed\n");
        exit(1);
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_LockSurface(nspire_screen);
    memset(nspire_screen->pixels, 0, 320 * 240 * 2);
    SDL_UnlockSurface(nspire_screen);

    /* Build vertical stretch lookup: 240 screen lines → 200 game lines */
    for (int dy = 0; dy < 240; dy++) {
        stretch_map[dy] = (Uint8)(dy * 200 / 240);
    }

    /* Cache LCD framebuffer address */
    lcd_base = (Uint16*)REAL_SCREEN_BASE_ADDRESS;

    /* 16-bit RGB565 onscreen surface, matching the screen format.
     * 8-bit sprite images are converted to 16-bit by SDL during blit
     * using each sprite's own palette (set in decode_image). */
    onscreen_surface_ = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 200, 16,
        nspire_screen->format->Rmask,
        nspire_screen->format->Gmask,
        nspire_screen->format->Bmask, 0);
    if (onscreen_surface_ == NULL) {
        fprintf(stderr, "ERROR: CreateRGBSurface failed\n");
        exit(1);
    }

    graphics_mode = gmMcgaVga;

#ifdef USE_TEXT
    extern void load_font(void);
    load_font();
#endif
}

void nspire_update_screen(void) {
    if (nspire_screen == NULL || onscreen_surface_ == NULL) return;

    if (nspire_stretch_mode) {
        /* 320x240 stretched */
        SDL_LockSurface(onscreen_surface_);
        SDL_LockSurface(nspire_screen);
        Uint8* src = (Uint8*)onscreen_surface_->pixels;
        Uint8* dst = (Uint8*)nspire_screen->pixels;
        int sp = onscreen_surface_->pitch;
        int dp = nspire_screen->pitch;
        for (int dy = 0; dy < 240; dy++) {
            memcpy(dst + dy * dp, src + stretch_map[dy] * sp, 640);
        }
        SDL_UnlockSurface(nspire_screen);
        SDL_UnlockSurface(onscreen_surface_);
    } else {
        /* 320x200 centered */
        SDL_Rect dst_rect = {0, 20, 320, 200};
        SDL_BlitSurface(onscreen_surface_, NULL, nspire_screen, &dst_rect);
    }
    SDL_Flip(nspire_screen);
}

/* ---- Input ---- */

/* Helper macro: update a key state with edge detection.
 * Uses macro because t_key (KEY_NSPIRE_*) is a struct, not passable as int. */
#define UPDATE_KEY(nspire_key, scancode) do { \
    if (isKeyPressed(nspire_key)) { \
        if (!(key_states[scancode] & KEYSTATE_HELD)) { \
            key_states[scancode] |= KEYSTATE_HELD | KEYSTATE_HELD_NEW; \
            last_key_scancode = scancode; \
            last_any_key_scancode = scancode; \
        } \
    } else { \
        key_states[scancode] &= ~KEYSTATE_HELD; \
    } \
} while(0)

/* Helper macro: update key from two alternative nspire keys (OR) */
#define UPDATE_KEY2(nspire_key1, nspire_key2, scancode) do { \
    if (isKeyPressed(nspire_key1) || isKeyPressed(nspire_key2)) { \
        if (!(key_states[scancode] & KEYSTATE_HELD)) { \
            key_states[scancode] |= KEYSTATE_HELD | KEYSTATE_HELD_NEW; \
            last_key_scancode = scancode; \
            last_any_key_scancode = scancode; \
        } \
    } else { \
        key_states[scancode] &= ~KEYSTATE_HELD; \
    } \
} while(0)

/* Map Nspire keys to SDLPoP scancodes and update key_states[] */
void nspire_poll_input(void) {
    /* Arrow keys + numpad 2/4/6/8 */
    UPDATE_KEY2(KEY_NSPIRE_LEFT,  KEY_NSPIRE_4, SDL_SCANCODE_LEFT);
    UPDATE_KEY2(KEY_NSPIRE_RIGHT, KEY_NSPIRE_6, SDL_SCANCODE_RIGHT);
    UPDATE_KEY2(KEY_NSPIRE_UP,    KEY_NSPIRE_8, SDL_SCANCODE_UP);
    UPDATE_KEY2(KEY_NSPIRE_DOWN,  KEY_NSPIRE_2, SDL_SCANCODE_DOWN);

    /* Shift key (action/grab) → RSHIFT in game.
     * Mapped to CTRL on nspire keypad */
    UPDATE_KEY(KEY_NSPIRE_CTRL, SDL_SCANCODE_RSHIFT);

    /* Nspire Tab or 7 → jump up+left (Home) */
    UPDATE_KEY2(KEY_NSPIRE_TAB, KEY_NSPIRE_7, SDL_SCANCODE_HOME);

    /* Nspire Shift or 9 → jump up+right (PageUp) */
    UPDATE_KEY2(KEY_NSPIRE_SHIFT, KEY_NSPIRE_9, SDL_SCANCODE_PAGEUP);

    /* Enter → confirm */
    UPDATE_KEY(KEY_NSPIRE_ENTER, SDL_SCANCODE_RETURN);

    /* ESC → quit game (Ctrl+Q) */
    if (isKeyPressed(KEY_NSPIRE_ESC)) {
        if (!(key_states[SDL_SCANCODE_ESCAPE] & KEYSTATE_HELD)) {
            key_states[SDL_SCANCODE_ESCAPE] |= KEYSTATE_HELD | KEYSTATE_HELD_NEW;
            last_key_scancode = SDL_SCANCODE_Q | WITH_CTRL;
            last_any_key_scancode = SDL_SCANCODE_ESCAPE;
        }
    } else {
        key_states[SDL_SCANCODE_ESCAPE] &= ~KEYSTATE_HELD;
    }

    /* Space → advance text/skip */
    UPDATE_KEY(KEY_NSPIRE_SPACE, SDL_SCANCODE_SPACE);

    /* 'R' on nspire → Ctrl+A (restart level) */
    if (isKeyPressed(KEY_NSPIRE_R)) {
        if (!(key_states[SDL_SCANCODE_A] & KEYSTATE_HELD)) {
            key_states[SDL_SCANCODE_A] |= KEYSTATE_HELD | KEYSTATE_HELD_NEW;
            last_key_scancode = SDL_SCANCODE_A | WITH_CTRL;
            last_any_key_scancode = SDL_SCANCODE_A;
        }
    } else {
        key_states[SDL_SCANCODE_A] &= ~KEYSTATE_HELD;
    }

    /* Menu key → toggle 320x200 / 320x240 stretch */
    {
        static int menu_was_pressed = 0;
        if (isKeyPressed(KEY_NSPIRE_MENU)) {
            if (!menu_was_pressed) {
                nspire_stretch_mode = !nspire_stretch_mode;
                if (!nspire_stretch_mode) {
                    /* Clear borders when switching back to 320x200 */
                    SDL_FillRect(nspire_screen, NULL, 0);
                }
                menu_was_pressed = 1;
            }
        } else {
            menu_was_pressed = 0;
        }
    }
}

/* ---- Audio stubs ---- */

int nspire_digi_unavailable = 1;
