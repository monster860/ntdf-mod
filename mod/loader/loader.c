#include <debug.h>
#include <kernel.h>
#include <stdlib.h>
#include <ps2sdkapi.h>
#include <loadfile.h>
#include <sifrpc.h>
#include <iopcontrol.h>
#include <iopheap.h>
#include <libpad.h>

char *path = "cdrom0:\\SCUS_973.67;1";

static char pad_thingy[256] __attribute__((aligned(64)));

void apply_ntdf_patch(void);

int main(int argc, char *argv[])
{
	init_scr();
	unsigned int old_paddata = 0;
	while(1) {
		static t_ExecData elfdata;
		int ret;
		SifInitRpc(0);
		while(!SifIopReset("", 0)){};
		while(!SifIopSync()){};

		SifInitRpc(0);
		SifLoadFileInit();
		SifInitIopHeap();

		SifLoadModule("rom0:SIO2MAN", 0, NULL);
		SifLoadModule("rom0:PADMAN", 0, NULL);

		padInit(0);
		padPortOpen(0, 0, pad_thingy);

		scr_clear();
		scr_printf("\n\nNeopets: The Darkest Faerie hack\n");
		scr_printf("By monster860\n\n");
		scr_printf("Source code at:\n");
		scr_printf("https://github.com/monster860/ntdf-mod\n\n");
		scr_printf("Loading game disc\n");

		ret = SifLoadElf(path, &elfdata);

		if(ret == 0) {
			while(!SifIopReset("", 0)){};
			while(!SifIopSync()){};
			SifExitRpc();
			FlushCache(0);
			FlushCache(2);

			scr_printf("Applying patch\n");
			apply_ntdf_patch();
			scr_printf("Starting up\n");

			ExecPS2((void *)elfdata.epc, (void *)elfdata.gp, 1, &path);
			return 0;
		} else {
			scr_printf("Load failed.\nPress X to try again\nPress triangle to exit\n");
			SifLoadFileExit();
			while(1) {
				
				struct timespec ts;
				ts.tv_sec = 0;
				ts.tv_nsec = 16683350;
				nanosleep(&ts, &ts);

				struct padButtonStatus buttons;
				unsigned int paddata = 0;
				if (padRead(0, 0, &buttons) != 0) {
					paddata = 0xffff ^ buttons.btns;
				}
				unsigned int masked_pad = paddata & ~old_paddata;
        		old_paddata = paddata;
				if(masked_pad & 0x4000) {
					padPortClose(0, 0);
					SifExitRpc();
					break;
				} else if(masked_pad & 0x1000) {
					scr_printf("Exiting\n");
					sleep(1);
					return 0;
				}
			}
		}
	}
}
