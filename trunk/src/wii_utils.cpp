#include "wii_utils.h"
#include <string.h>
#include <wiiuse/wpad.h>

Uint8 wpad_keyboard_mapping[SDLK_LAST];

void insert_rootdir_prefix(const char *path_in, char *path_out) 
{
    // 100 below is a magic number - The platform-dependent ROOTDIR_PREFIX
    // is never expected to exceed that many characters in length
    strncpy(path_out, ROOTDIR_PREFIX, 100); 
    strncat(path_out, path_in, strlen(path_in)); 
}

SDL_Surface * SDLCALL RootDirPrefix_IMG_Load(const char *file)
{
    char absFile[256];
    insert_rootdir_prefix(file, absFile);
    return IMG_Load(absFile);
}

Uint8 *WPAD_SDL_GetKeyState(int *numkeys)
{
    WPAD_ScanPads();
    u32 held = WPAD_ButtonsHeld(0);
    
    wpad_keyboard_mapping[SDLK_SPACE] = ((held & WIIMOTE_BUTTON_ONE) || (held & WIIMOTE_BUTTON_TWO)) ? 1 : 0;
    // Wiimote is placed sideways to play - therefore, the positions have to be changed
    wpad_keyboard_mapping[SDLK_LEFT] = (held & WIIMOTE_BUTTON_UP) ? 1 : 0;
    wpad_keyboard_mapping[SDLK_RIGHT] = (held & WIIMOTE_BUTTON_DOWN) ? 1 : 0;
    wpad_keyboard_mapping[SDLK_DOWN] = (held & WIIMOTE_BUTTON_LEFT) ? 1 : 0;
    wpad_keyboard_mapping[SDLK_UP] = (held & WIIMOTE_BUTTON_RIGHT) ? 1 : 0;
    wpad_keyboard_mapping[SDLK_ESCAPE] = (held & WIIMOTE_BUTTON_HOME) ? 1 : 0;   
    wpad_keyboard_mapping[SDLK_F1] = (held & WIIMOTE_BUTTON_PLUS) ? 1 : 0;
    wpad_keyboard_mapping[SDLK_BACKSPACE] = (held & WIIMOTE_BUTTON_MINUS) ? 1 : 0;
    
    // Check controller for P2
    held = WPAD_ButtonsHeld(1);
    wpad_keyboard_mapping[SDLK_LSHIFT] = ((held & WIIMOTE_BUTTON_ONE) || (held & WIIMOTE_BUTTON_TWO)) ? 1 : 0;
    wpad_keyboard_mapping[SDLK_a] = (held & WIIMOTE_BUTTON_UP) ? 1 : 0;
    wpad_keyboard_mapping[SDLK_d] = (held & WIIMOTE_BUTTON_DOWN) ? 1 : 0;        
    
    return wpad_keyboard_mapping;
}
   