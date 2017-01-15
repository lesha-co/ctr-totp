#include <3ds.h>
#include <unistd.h>
#include "tests.h"
#include "TOTP.h"
int main(int argc, char **argv)
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// run once begin
    ///
    tests::testAll();
    TOTP* totp = new TOTP("JBSWY3DPEHPK3PXP", 0, 30, 6);

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

        TotpResult tr = totp ->get();
        printf("%s [%2d]\n",
               tr.totp.c_str(),
               tr.remaining_seconds);
        usleep(1000000);

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
