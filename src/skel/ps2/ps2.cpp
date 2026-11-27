#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <libpad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "platform.h"
#include "skeleton.h"
#include "main.h"

static char padBuf[256] __attribute__((aligned(64)));

void ps2_init_hardware() {
    SifInitRpc(0);
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    padInit(0);
    padPortOpen(0, 0, padBuf);
}

int main(int argc, char *argv[]) {
    ps2_init_hardware();
    RsEventHandler(rsINITIALIZE, NULL);
    RsEventHandler(rsRWINITIALIZE, NULL);

    while (!RsGlobal.quit) {
	RsEventHandler(rsIDLE, NULL);
    }

    RsEventHandler(rsRWTERMINATE, NULL);
    RsEventHandler(rsTERMINATE, NULL);
    return 0;
}
