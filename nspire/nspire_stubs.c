/*
 * nspire_stubs.c - Stub implementations for disabled features on Nspire
 *
 * These functions are referenced from other source files but come from
 * modules we don't compile (menu.c, replay.c, lighting.c, screenshot.c).
 * The #ifdef guards in the calling code don't always cover every reference,
 * so we provide no-op stubs here.
 */

#include "common.h"

/* ---- Lighting stubs ---- */
void init_lighting(void) {}
void redraw_lighting(void) {}
void update_lighting(const rect_type* source_rect_ptr) { (void)source_rect_ptr; }

/* ---- Screenshot stubs ---- */
void save_screenshot(void) {}
void auto_screenshot(void) {}
bool want_auto_screenshot(void) { return false; }
void init_screenshot(void) {}
void save_level_screenshot(bool want_extras) { (void)want_extras; }

/* ---- Menu stubs ---- */
void init_menu(void) {}
void menu_scroll(int y) { (void)y; }
void draw_menu(void) {}
void clear_menu_controls(void) {}
void process_additional_menu_input(void) {}
int key_test_paused_menu(int key) { return key; }
void load_ingame_settings(void) {}
void menu_was_closed(void) {}

/* Small font data - normally in menu.c */
byte hc_small_font_data[1] = {0};

/* ---- Replay stubs ---- */
void start_with_replay_file(const char *filename) { (void)filename; }
void init_record_replay(void) {}
void replay_restore_level(void) {}
int restore_savestate_from_buffer(void) { return 0; }
void start_recording(void) {}
void add_replay_move(void) {}
void stop_recording(void) {}
void start_replay(void) {}
void end_replay(void) {}
void do_replay_move(void) {}
int save_recorded_replay_dialog(void) { return 0; }
int save_recorded_replay(const char* full_filename) { (void)full_filename; return 0; }
void replay_cycle(void) {}
int load_replay(void) { return 0; }
void key_press_while_recording(int* key_ptr) { (void)key_ptr; }
void key_press_while_replaying(int* key_ptr) { (void)key_ptr; }

/* ---- Audio speed (from USE_FAST_FORWARD) ---- */
int audio_speed = 1;

/* ---- load_sound_names ---- */
/* This is normally in seg009.c but it's inside #ifndef NSPIRE audio block */
void load_sound_names(void) {}
