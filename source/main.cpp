// setting up libnds dependencies //
// image of the bootrom error screen //

#include <nds.h>
#include <stdio.h>

#include "logo.h"

int main(void)
{
// sets up MODE_5 for the DS' 3 background layers 
	videoSetMode(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	
// 3rd layer setting up for the bottom screen
	videoSetModeSub(MODE_5_2D);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);

// top-screen background layer
    int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
    dmaCopy(logoBitmap, bgGetGfxPtr(bg3), 256*256);		// background image
    dmaCopy(logoPal, BG_PALETTE, 256*2);				// background palette specified
	
// sub-screen (bottom screen) background layer 
	int bg3sub = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
    dmaCopy(logoBitmap, bgGetGfxPtr(bg3sub), 256*256);  // background image
    dmaCopy(logoPal, BG_PALETTE_SUB, 256*2);			// background palette specified


    while(1) {
        swiWaitForVBlank();
        scanKeys();
        if (keysDown()&KEY_START) break;    // exits back into nds-hbmenu (start button) 
    }
	
    return 0;    // loop
}