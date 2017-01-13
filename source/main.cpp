#include <3ds.h>
#include <cstdio>
#include "sha1.hpp"
#include "base32.h"
#include "hmac.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// run once begin
    ///

    vector<u8> v_key = base32::decode("JBSWY3DPEHPK3PXP");
    vector<u8> v_message = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
    vector<u8> bytes = hmac::encode(v_key, v_message);
    for (u8 byte : bytes) {
        printf("%x", byte);
    }
    printf("\n");


    /*  const string b32 = "JBSWY3DPEHPK3PXP";

      vector<u8> bytes = base32::decode(b32);
      for (u8 byte : bytes) {
          printf("%x", byte);
      }
      printf("\n");
  */
    ///
    /// run once end
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break; // break in order to return to hbmenu
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// run loop begin
        ///
        

       
        ///
        /// run loop end
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();

        //Wait for VBlank
        gspWaitForVBlank();
    }

    // Exit services
    gfxExit();

    return 0;
}
