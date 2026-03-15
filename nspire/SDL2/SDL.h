/*
 * SDL2-to-SDL1.2 compatibility header for TI-Nspire (nSDL)
 *
 * SDLPoP uses SDL2 but nSDL is SDL 1.2. This header includes
 * the real SDL 1.2 headers and provides compatibility defines/types
 * for the SDL2 features used by SDLPoP.
 */

#ifndef NSPIRE_SDL2_COMPAT_H
#define NSPIRE_SDL2_COMPAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Include the real nSDL (SDL 1.2) header */
#include <SDL/SDL.h>

/* ---- Types that exist in SDL2 but not SDL1.2 ---- */

typedef void SDL_Window;
typedef void SDL_Renderer;
typedef void SDL_Texture;
typedef void SDL_GameController;
typedef void SDL_Haptic;

/* 64-bit types */
#ifndef Uint64
typedef unsigned long long Uint64;
#endif
#ifndef Sint64
typedef long long Sint64;
#endif
#ifndef int64_t
#include <stdint.h>
#endif

/* ---- SDL bool ---- */
/* SDL_bool already defined in nSDL's SDL_stdinc.h */
#ifndef SDL_TRUE
#define SDL_TRUE  1
#define SDL_FALSE 0
#endif

/* ---- SDL alpha constants ---- */
#ifndef SDL_ALPHA_OPAQUE
#define SDL_ALPHA_OPAQUE      255
#define SDL_ALPHA_TRANSPARENT 0
#endif

/* ---- SDL_SCANCODE compatibility ---- */
#define SDL_NUM_SCANCODES 256

#define SDL_SCANCODE_LEFT      0x50
#define SDL_SCANCODE_RIGHT     0x4F
#define SDL_SCANCODE_UP        0x52
#define SDL_SCANCODE_DOWN      0x51
#define SDL_SCANCODE_RSHIFT    0xE5
#define SDL_SCANCODE_LSHIFT    0xE1
#define SDL_SCANCODE_HOME      0x4A
#define SDL_SCANCODE_PAGEUP    0x4B
#define SDL_SCANCODE_RETURN    0x28
#define SDL_SCANCODE_ESCAPE    0x29
#define SDL_SCANCODE_SPACE     0x2C
#define SDL_SCANCODE_BACKSPACE 0x2A
#define SDL_SCANCODE_A         0x04
#define SDL_SCANCODE_B         0x05
#define SDL_SCANCODE_C         0x06
#define SDL_SCANCODE_D         0x07
#define SDL_SCANCODE_E         0x08
#define SDL_SCANCODE_F         0x09
#define SDL_SCANCODE_G         0x0A
#define SDL_SCANCODE_H         0x0B
#define SDL_SCANCODE_I         0x0C
#define SDL_SCANCODE_J         0x0D
#define SDL_SCANCODE_K         0x0E
#define SDL_SCANCODE_L         0x0F
#define SDL_SCANCODE_M         0x10
#define SDL_SCANCODE_N         0x11
#define SDL_SCANCODE_O         0x12
#define SDL_SCANCODE_P         0x13
#define SDL_SCANCODE_Q         0x14
#define SDL_SCANCODE_R         0x15
#define SDL_SCANCODE_S         0x16
#define SDL_SCANCODE_T         0x17
#define SDL_SCANCODE_U         0x18
#define SDL_SCANCODE_V         0x19
#define SDL_SCANCODE_W         0x1A
#define SDL_SCANCODE_X         0x1B
#define SDL_SCANCODE_Y         0x1C
#define SDL_SCANCODE_Z         0x1D
#define SDL_SCANCODE_0         0x27
#define SDL_SCANCODE_1         0x1E
#define SDL_SCANCODE_2         0x1F
#define SDL_SCANCODE_3         0x20
#define SDL_SCANCODE_4         0x21
#define SDL_SCANCODE_5         0x22
#define SDL_SCANCODE_6         0x23
#define SDL_SCANCODE_7         0x24
#define SDL_SCANCODE_8         0x25
#define SDL_SCANCODE_9         0x26
#define SDL_SCANCODE_F6        0x3F
#define SDL_SCANCODE_F9        0x42
#define SDL_SCANCODE_F12       0x45
#define SDL_SCANCODE_LCTRL     0xE0
#define SDL_SCANCODE_RCTRL     0xE4
#define SDL_SCANCODE_LALT      0xE2
#define SDL_SCANCODE_RALT      0xE6
#define SDL_SCANCODE_LGUI      0xE3
#define SDL_SCANCODE_RGUI      0xE7
#define SDL_SCANCODE_GRAVE     0x35
#define SDL_SCANCODE_LEFTBRACKET  0x2F
#define SDL_SCANCODE_RIGHTBRACKET 0x30
#define SDL_SCANCODE_BACKSLASH    0x31
#define SDL_SCANCODE_MINUS        0x2D
#define SDL_SCANCODE_EQUALS       0x2E
#define SDL_SCANCODE_TAB          0x2B
#define SDL_SCANCODE_DELETE       0x4C
#define SDL_SCANCODE_PAUSE        0x48
#define SDL_SCANCODE_CAPSLOCK     0x39
#define SDL_SCANCODE_SCROLLLOCK   0x47
#define SDL_SCANCODE_NUMLOCKCLEAR 0x53
#define SDL_SCANCODE_APPLICATION  0x65
#define SDL_SCANCODE_PRINTSCREEN  0x46
#define SDL_SCANCODE_VOLUMEUP     0x80
#define SDL_SCANCODE_VOLUMEDOWN   0x81
#define SDL_SCANCODE_MUTE         0x7F
#define SDL_SCANCODE_AUDIOMUTE    0x7E
#define SDL_SCANCODE_KP_MINUS     0x56
#define SDL_SCANCODE_KP_PLUS      0x57
#define SDL_SCANCODE_KP_2         0x5A
#define SDL_SCANCODE_KP_4         0x5C
#define SDL_SCANCODE_KP_5         0x5D
#define SDL_SCANCODE_KP_6         0x5E
#define SDL_SCANCODE_KP_7         0x5F
#define SDL_SCANCODE_KP_8         0x60
#define SDL_SCANCODE_KP_9         0x61
#define SDL_SCANCODE_CLEAR        0x9C

/* ---- SDL2 Keyboard modifier compat ---- */
#ifndef KMOD_SHIFT
#define KMOD_SHIFT (KMOD_LSHIFT | KMOD_RSHIFT)
#endif
#ifndef KMOD_CTRL
#define KMOD_CTRL (KMOD_LCTRL | KMOD_RCTRL)
#endif
#ifndef KMOD_ALT
#define KMOD_ALT (KMOD_LALT | KMOD_RALT)
#endif

/* ---- Window/Renderer stubs ---- */
#define SDL_CreateWindow(t,x,y,w,h,f)    ((SDL_Window*)NULL)
#define SDL_DestroyWindow(w)              ((void)0)
#define SDL_CreateRenderer(w,i,f)         ((SDL_Renderer*)NULL)
#define SDL_DestroyRenderer(r)            ((void)0)
#define SDL_CreateTexture(r,f,a,w,h)      ((SDL_Texture*)NULL)
#define SDL_DestroyTexture(t)             ((void)0)
#define SDL_CreateTextureFromSurface(r,s) ((SDL_Texture*)NULL)
#define SDL_SetRenderTarget(r,t)          (0)
#define SDL_RenderCopy(r,t,s,d)           (0)
#define SDL_RenderPresent(r)              ((void)0)
#define SDL_RenderClear(r)                (0)
#define SDL_SetTextureBlendMode(t,b)      (0)
#define SDL_GetRendererInfo(r,i)          (-1)
#define SDL_SetWindowSize(w,x,y)          ((void)0)
#define SDL_SetWindowTitle(w,t)           ((void)0)
#define SDL_SetWindowFullscreen(w,f)      (0)
#define SDL_GetWindowSize(w,pw,ph)        do { if(pw) *(pw)=320; if(ph) *(ph)=240; } while(0)
#define SDL_GetWindowFlags(w)             (0)
#define SDL_ShowCursor(toggle)            (0)
#define SDL_SetWindowIcon(w,icon)         ((void)0)
#define SDL_UpdateTexture(t,r,p,pitch)    (0)
#define SDL_RenderSetLogicalSize(r,w,h)   (0)
#define SDL_GetRendererOutputSize(r,w,h)  (-1)
#define SDL_RenderGetLogicalSize(r,w,h)   ((void)0)
#define SDL_RenderSetIntegerScale(r,e)    (0)
#define SDL_BlitScaled(s,sr,d,dr)         SDL_BlitSurface(s,sr,d,dr)

/* ---- GameController stubs ---- */
#define SDL_GameControllerOpen(i)         ((SDL_GameController*)NULL)
#define SDL_GameControllerClose(c)        ((void)0)
#define SDL_IsGameController(i)           (0)
#define SDL_GameControllerName(c)         ("none")
#define SDL_GameControllerGetButton(c,b)  (0)
#define SDL_GameControllerGetAxis(c,a)    (0)
#define SDL_GameControllerFromInstanceID(id) ((SDL_GameController*)NULL)

/* ---- Haptic stubs ---- */
#define SDL_HapticOpen(i)                 ((SDL_Haptic*)NULL)
#define SDL_HapticClose(h)               ((void)0)
#define SDL_HapticRumbleInit(h)          (-1)
#define SDL_HapticRumblePlay(h,s,l)      (-1)
#define SDL_HapticRumbleSupported(h)     (0)

/* ---- Joystick extras ---- */
#define SDL_SetHint(name, value)         (0)
#define SDL_GameControllerAddMappingsFromFile(f) (0)

/* ---- Performance counter ---- */
#define SDL_GetPerformanceCounter()      ((Uint64)SDL_GetTicks())
#define SDL_GetPerformanceFrequency()    ((Uint64)1000)

/* ---- SDL Surface compat ---- */
#define SDL_SetSurfaceBlendMode(s,m)     (0)
#define SDL_SetSurfacePalette(s,p)       (0)
#define SDL_SetSurfaceAlphaMod(s,a)      (0)
/* SDL2 uses SDL_SetColorKey(surface, SDL_TRUE, key)
   SDL1.2 uses SDL_SetColorKey(surface, SDL_SRCCOLORKEY, key)
   Since SDL_TRUE==1 and SDL_SRCCOLORKEY is a flag, we remap */
/* Note: the existing code uses SDL_TRUE as the flag, which is 1.
   SDL_SRCCOLORKEY in SDL 1.2 is typically 0x00001000. We need a wrapper. */
static inline int SDL2_SetColorKey(SDL_Surface *surface, int flag, Uint32 key) {
    if (flag) return SDL_SetColorKey(surface, SDL_SRCCOLORKEY, key);
    else return SDL_SetColorKey(surface, 0, key);
}
/* Override SDL_SetColorKey to use our wrapper */
#undef SDL_SetColorKey
#define SDL_SetColorKey SDL2_SetColorKey

/* SDL_SetPaletteColors (SDL2) → SDL_SetColors (SDL1.2) */
static inline int SDL_SetPaletteColors(SDL_Palette *palette, const SDL_Color *colors, int firstcolor, int ncolors) {
    /* SDL1.2 SDL_SetColors takes surface, not palette. We need the surface.
       But SDLPoP calls it as: SDL_SetPaletteColors(image->format->palette, colors, 0, 16)
       In SDL 1.2, we can directly modify the palette entries. */
    if (!palette || !colors) return -1;
    for (int i = 0; i < ncolors && (firstcolor + i) < palette->ncolors; i++) {
        palette->colors[firstcolor + i].r = colors[i].r;
        palette->colors[firstcolor + i].g = colors[i].g;
        palette->colors[firstcolor + i].b = colors[i].b;
    }
    return 0;
}

/* SDL_Color: SDL1.2 has {r,g,b,unused}, SDL2 has {r,g,b,a}.
   We can't use #define a unused (too dangerous - breaks all code with variable 'a').
   Instead, we provide a macro for the specific .a access pattern used in SDLPoP. */

/* ---- Window flags ---- */
#define SDL_WINDOW_RESIZABLE             0x00000020
#define SDL_WINDOW_FULLSCREEN            0x00000001
#define SDL_WINDOW_FULLSCREEN_DESKTOP    0x00001001
#define SDL_WINDOW_ALLOW_HIGHDPI         0x00002000
#define SDL_WINDOWPOS_UNDEFINED          0
#define SDL_WINDOWPOS_CENTERED           0

/* ---- Renderer flags ---- */
#define SDL_RENDERER_ACCELERATED   0x00000002
#define SDL_RENDERER_PRESENTVSYNC  0x00000004
#define SDL_RENDERER_SOFTWARE      0x00000001
#define SDL_RENDERER_TARGETTEXTURE 0x00000008

/* ---- Blend mode ---- */
#ifndef SDL_BLENDMODE_NONE
#define SDL_BLENDMODE_NONE  0x00000000
#define SDL_BLENDMODE_BLEND 0x00000001
#endif

/* ---- Texture access ---- */
#define SDL_TEXTUREACCESS_STREAMING 1
#define SDL_TEXTUREACCESS_TARGET    2

/* ---- Pixel format ---- */
#define SDL_PIXELFORMAT_ARGB8888 0
#define SDL_PIXELFORMAT_RGB888   1
#define SDL_PIXELFORMAT_RGB24    2

/* ---- RendererInfo ---- */
typedef struct SDL_RendererInfo {
    const char *name;
    Uint32 flags;
    Uint32 num_texture_formats;
    Uint32 texture_formats[16];
    int max_texture_width;
    int max_texture_height;
} SDL_RendererInfo;

/* ---- Scale mode ---- */
#define SDL_SetTextureScaleMode(t,m) (0)

/* ---- Hints ---- */
#define SDL_HINT_RENDER_SCALE_QUALITY      "SDL_RENDER_SCALE_QUALITY"
#define SDL_HINT_RENDER_VSYNC              "SDL_RENDER_VSYNC"
#define SDL_HINT_GAMECONTROLLERCONFIG      "SDL_GAMECONTROLLERCONFIG"
#define SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING "SDL_WINDOWS_DISABLE_THREAD_NAMING"

/* ---- Init flags ---- */
#ifndef SDL_INIT_GAMECONTROLLER
#define SDL_INIT_GAMECONTROLLER 0
#endif
#ifndef SDL_INIT_HAPTIC
#define SDL_INIT_HAPTIC 0
#endif
#define SDL_InitSubSystem(flags) (0)

/* ---- Logging ---- */
#define SDL_Log(...) fprintf(stderr, __VA_ARGS__)

/* ---- Memory ---- */
#ifndef SDL_free
#define SDL_free free
#endif
#ifndef SDL_malloc
#define SDL_malloc malloc
#endif

/* ---- SDL_version ---- */
#ifndef SDL_GetVersion
typedef struct SDL_version_compat {
    Uint8 major;
    Uint8 minor;
    Uint8 patch;
} SDL_version_compat;
#define SDL_version SDL_version_compat
static inline void SDL_GetVersion(SDL_version *ver) {
    ver->major = 1; ver->minor = 2; ver->patch = 15;
}
#endif

/* ---- SDL_VERSION_ATLEAST ---- */
#ifndef SDL_VERSION_ATLEAST
#define SDL_VERSION_ATLEAST(X, Y, Z) (0)
#endif

/* ---- Audio stubs (NO_AUDIO) ---- */
#ifdef NO_AUDIO
typedef Uint16 SDL_AudioFormat;
#ifndef AUDIO_U8
#define AUDIO_U8     0x0008
#define AUDIO_S16SYS 0x8010
#endif
typedef struct SDL_AudioSpec_compat {
    int freq;
    SDL_AudioFormat format;
    Uint8 channels;
    Uint16 samples;
    void (*callback)(void *userdata, Uint8 *stream, int len);
    void *userdata;
} SDL_AudioSpec_compat;
#define SDL_AudioSpec SDL_AudioSpec_compat
#define SDL_OpenAudio(desired, obtained) (-1)
#define SDL_CloseAudio()                 ((void)0)
#define SDL_PauseAudio(pause_on)         ((void)0)
#define SDL_LockAudio()                  ((void)0)
#define SDL_UnlockAudio()                ((void)0)
#endif /* NO_AUDIO */

/* ---- Event types that exist in SDL2 but not SDL1.2 ---- */
#ifndef SDL_WINDOWEVENT
#define SDL_WINDOWEVENT         0x200
#define SDL_TEXTINPUT           0x303
#define SDL_CONTROLLERAXISMOTION    0x650
#define SDL_CONTROLLERBUTTONDOWN    0x651
#define SDL_CONTROLLERBUTTONUP      0x652
#define SDL_CONTROLLERDEVICEADDED   0x653
#define SDL_CONTROLLERDEVICEREMOVED 0x654
#define SDL_WINDOWEVENT_SIZE_CHANGED   1
#define SDL_WINDOWEVENT_EXPOSED        2
#define SDL_WINDOWEVENT_FOCUS_GAINED   3
#define SDL_WINDOWEVENT_MINIMIZED      4
#define SDL_WINDOWEVENT_RESTORED       5
#endif

/* SDL2 controller axis constants */
#define SDL_CONTROLLER_AXIS_LEFTX        0
#define SDL_CONTROLLER_AXIS_LEFTY        1
#define SDL_CONTROLLER_AXIS_RIGHTX       2
#define SDL_CONTROLLER_AXIS_RIGHTY       3
#define SDL_CONTROLLER_AXIS_TRIGGERLEFT  4
#define SDL_CONTROLLER_AXIS_TRIGGERRIGHT  5
#define SDL_CONTROLLER_BUTTON_A             0
#define SDL_CONTROLLER_BUTTON_B             1
#define SDL_CONTROLLER_BUTTON_X             2
#define SDL_CONTROLLER_BUTTON_Y             3
#define SDL_CONTROLLER_BUTTON_BACK          4
#define SDL_CONTROLLER_BUTTON_START         6
#define SDL_CONTROLLER_BUTTON_DPAD_UP       11
#define SDL_CONTROLLER_BUTTON_DPAD_DOWN     12
#define SDL_CONTROLLER_BUTTON_DPAD_LEFT     13
#define SDL_CONTROLLER_BUTTON_DPAD_RIGHT    14

/* ---- SDL_GetKeyboardState (SDL2) ---- */
#define SDL_GetKeyboardState(numkeys) SDL_GetKeyState(numkeys)

/* ---- SDL_ConvertSurfaceFormat stub ---- */
/* In SDL2, this converts surface pixel format. On Nspire, return the surface as-is. */
static inline SDL_Surface* SDL_ConvertSurfaceFormat(SDL_Surface* src, Uint32 pixel_format, Uint32 flags) {
    (void)pixel_format; (void)flags;
    /* Just increase the refcount and return the same surface (shallow copy) */
    /* Actually, we need to do a real copy. Use SDL_ConvertSurface with the same format. */
    return SDL_ConvertSurface(src, src->format, src->flags);
}

/* ---- SDL_PixelFormat compat ---- */
/* SDL2 SDL_PixelFormat has a 'format' field; SDL1.2 doesn't.
   We provide a macro that checks BitsPerPixel instead. */
#define SDL_ISPIXELFORMAT_INDEXED(fmt) (0) /* Simplified: on Nspire all our images are paletted/8bpp from DAT */

/* ---- Text input stubs ---- */
#define SDL_SetTextInputRect(rect)  ((void)0)
#define SDL_StartTextInput()        ((void)0)
#define SDL_StopTextInput()         ((void)0)

/* ---- SDL_MOUSEWHEEL event ---- */
#ifndef SDL_MOUSEWHEEL
#define SDL_MOUSEWHEEL 0x403
#endif

/* ---- IMG_Load_RW stub ---- */
#define IMG_Load_RW(rw, freesrc) ((SDL_Surface*)NULL)
#define IMG_GetError() "IMG not available on Nspire"
#define IMG_Load(file) ((SDL_Surface*)NULL)

/* ---- Nspire-specific ---- */
#include <libndls.h>

#endif /* NSPIRE_SDL2_COMPAT_H */
