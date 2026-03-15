/*
 * SDL_image stub for TI-Nspire
 * SDLPoP uses SDL_image only for PNG screenshot saving.
 * On Nspire, screenshots are disabled, so this is empty.
 */

#ifndef NSPIRE_SDL_IMAGE_STUB_H
#define NSPIRE_SDL_IMAGE_STUB_H

/* No IMG_* functions needed - screenshot feature is disabled on Nspire */

#define IMG_SavePNG(surface, file) (-1)
#define IMG_Init(flags) (0)
#define IMG_Quit() ((void)0)

#endif /* NSPIRE_SDL_IMAGE_STUB_H */
