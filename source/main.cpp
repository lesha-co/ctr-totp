#include <3ds.h>
#include <unistd.h>
#include "tests.h"
#include "TOTP.h"
#include "NTPClock.h"


const s32 TZOFFSET = 3*60*60;
u32 getUnixEpochTime(){
    return (u32)time(0) - TZOFFSET;
}
int main(int argc, char **argv)
{
    gfxInitDefault();
    PrintConsole top, bottom;
    consoleInit(GFX_BOTTOM, &bottom);
    consoleInit(GFX_TOP, &top);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// run once begin
    ///
    consoleSelect(&top);
    tests::testAll();
    TOTP* totp = new TOTP("JBSWY3DPEHPK3PXP", 0, 30, 6);
    s32 ntp_offset = 0;

    printf("Trying NTP sync...\n");
    char domain[] =  "129.6.15.28";
    NTPClock* clock = new NTPClock(domain);
    if (clock->initialized()){
        printf("clock initialized\n");
        s32 ntp_time = clock->getNetworkTime();
        std::time_t localtime = std::time(nullptr);
        ntp_offset = localtime-ntp_time ;
        printf("NTP: %ld, LOCAL: %ld, OFFSET: %ld", ntp_time, localtime, ntp_offset);
    } else {
        printf("failed");
    }

    usleep(30000000);

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
        consoleSelect(&top);
        consoleClear();
        std::time_t result = std::time(nullptr);
        printf("local time is %s\nTZ offset is %+ld \nNTP offset is %+ld \n",
               std::asctime(std::localtime(&result)),
               TZOFFSET,
               ntp_offset
        );




        consoleSelect(&bottom);

        TotpResult tr = totp ->get(getUnixEpochTime());
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
    delete(clock);
    delete(totp);
    gfxExit();

    return 0;
}
