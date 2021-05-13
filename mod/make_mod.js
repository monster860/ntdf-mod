const path = require('path');
const fs = require('fs');
const {create_mod, make_pnach, patch_file, make_c_loader} = require('../elf_processor.js');

create_mod(path.join(__dirname, "mod.o"), 0x3043B0, {"memset": 0x2BFE8C}).then(mod => {
	mod.patches.push({addr: 0x111074, int_data: 0x0c000000 | (mod.symbols["do_mod"].abs_addr >> 2)});
	mod.patches.push({addr: 0x17D170, int_data: 0x08000000 | (mod.symbols["IsDebugMode"].abs_addr >> 2)});
	mod.patches.push({addr: 0x1A17C0, int_data: 0x08000000 | (mod.symbols["ResumeGameHook"].abs_addr >> 2)});
	mod.patches.push({addr: 0x218EFC, int_data: 0x0C000000 | (mod.symbols["SwapTransitionHook"].abs_addr >> 2)});
	mod.patches.push({addr: 0x218F30, int_data: 0x0C000000 | (mod.symbols["SwapExteriorHook"].abs_addr >> 2)});
	mod.patches.push({addr: 0x318F04, int_data: mod.symbols["WorldControlsHook"].abs_addr});
	mod.patches.push({addr: 0x1B25D0, int_data: 0}); // always show cursor on map
	mod.patches.push({addr: 0x2DD1F8, int_data: mod.symbols["MapScreenHook"].abs_addr});
	mod.patches.push({addr: 0x2DD1D4, int_data: mod.symbols["LoadScreenHook"].abs_addr});
	mod.patches.push({addr: 0x2DD1D8, int_data: mod.symbols["SaveScreenHook"].abs_addr});
	fs.writeFile(path.join(__dirname, "934F9081.pnach"), make_pnach(mod), () => {
		console.log("pnach written");
	});
	/*patch_file(mod, "SCUS_973.67", "df_hack_raw.elf", -1048448).then(() => {
		console.log("elf written");
	});*/
	fs.writeFile(path.join(__dirname, "./loader/patch.c"), make_c_loader(mod), () => {
		console.log("patch c file written");
	});
});