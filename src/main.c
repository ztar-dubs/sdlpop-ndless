/*
SDLPoP, a port/conversion of the DOS game Prince of Persia.
Copyright (C) 2013-2025  Dávid Nagy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

The authors of this program may be contacted at https://forum.princed.org
*/

#include "common.h"

#ifdef NSPIRE
#include <libndls.h>
#endif

#ifdef __amigaos4__
static const char version[] = "\0$VER: SDLPoP " SDLPOP_VERSION " (" __AMIGADATE__ ")";
static const char stack[] = "$STACK:200000";
#endif

#ifdef __PSP__
#include <psppower.h>
#endif

#ifdef NSPIRE
/* On Nspire, we need to chdir to the directory containing the executable
   because the default CWD is /documents/ */
static void nspire_chdir_to_exe(int argc, char* argv[]) {
	if (argc > 0 && argv[0] != NULL) {
		char path[256];
		strncpy(path, argv[0], sizeof(path) - 1);
		path[sizeof(path) - 1] = '\0';
		/* Find last '/' */
		char* last_slash = NULL;
		for (char* p = path; *p; p++) {
			if (*p == '/') last_slash = p;
		}
		if (last_slash != NULL) {
			*last_slash = '\0';
			chdir(path);
		}
	}
}
#endif

int main(int argc, char *argv[])
{
	#ifdef __PSP__
	scePowerSetClockFrequency(333,333,166);
	#endif

	#ifdef NSPIRE
	nspire_chdir_to_exe(argc, argv);
	#endif

	g_argc = argc;
	g_argv = argv;
	pop_main();
	return 0;
}

