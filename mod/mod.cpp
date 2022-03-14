#define sprintf ((void (*)(char *, const char *, ...))0x2c1480)
#define printf ((void (*)(const char *, ...))0x2ca710)
#define DisplayScreenMessage ((void (*)(char *, float, float, float))0x179620)
#define DisplayWorldString ((void (*)(int, u128, char*, bool))0x1729b0)
#define FloatToChar ((void (*)(float, int, char*))0x1796c0)
#define draw_debug_text ((void (*)(const char *, bool, const char *, int, void*, void*, float, float, float))0x255618)
//#define get_sound_ptr ((void*(*)())0x286c90)
//#define sound_thingy (*((void**)0x35C7BC));
//#define playsound ((void (*)(void*, void*, int, int, int, int, int, int, float, float))0x2878e8)
// playsound(get_sound_ptr(), sound_thingy, 0x95, 0, 0, -1, 0, 0, 0.0f, 0.0f);
#define playmenusound ((void (*)(int))0x253118)
#define StartExteriorReplacementLoad ((void (*)(int, int, char*))0x17b2b0)
#define StartEnterInterior ((void (*)(int, int, int, char*))0x17b0c0)
#define GiveItemToHero ((void (*)(int, int, bool))0x176440)
#define load_area ((void (*)(int, int, int, int, int, int, int, char*, int, int))0x120ba8)
#define get_area_file ((int(*)(int))0x21a6c8)
#define DisplayDialogText ((void (*)(const char *))0x1794F8)
#define QueryGameState ((bool (*)(int))0x176DA0)
#define SetGameState ((void (*)(int, bool))0x176DC0)
#define KillBothHeroes ((void (*)())0x175CA8)
#define GetZoneMapCoordinates ((bool (*)(void *, int *, int *, float, float))0x21b040)
#define GetZoneMapEntry ((void* (*)(void *, int, int))0x21aff0)
#define get_floor_height ((float (*)(int, int*, void *, float, float, float))0x217b20)
#define handle_world_controls ((void (*)(int))0x1E2C10)

#define resume_game_ptr_1 (*((char**)0xB41594))
#define resume_game_ptr_2 (*((char**)0xB415A4))
#define selected_select_item (*((short*)0xb3b5ac))
#define controller_buttons (*((int*)0x4553D8))
#define controller_buttons_instant (*((int*)0x4553DC))
#define controller_buttons_digital_instant (*((int*)0x4553D4))
#define savegame_filename_ptr (((char*)0x385444))
#define load_flag (*((int*)0x2DCFF8))
#define save_flag (*((int*)0x2DCFFC))

extern "C" float sqrtf(float f) {
	__asm("sqrt.s $f00, $f12\n\tjr $31\n\tnop");
}

typedef unsigned int u128 __attribute__(( mode(TI) ));

typedef void *(*HandleResumeGamePtr)(int, int, int, int, int);
typedef void *(*HandleScreenPtr)(int, int, int, int, int);
typedef void (*MapSwapPtr)(int,int,int,int);
//HandleResumeGamePtr HandleResumeGame = (HandleResumeGamePtr)0x1a17c0;
int HandleResumeGameTrampolineBytes[] = {
	0x27bdffb0,
	0x080685f2,
	0x3c020036
};
const HandleResumeGamePtr HandleResumeGameTrampoline = (HandleResumeGamePtr)HandleResumeGameTrampolineBytes;
const HandleResumeGamePtr HandleViewMap = (HandleResumeGamePtr)0x1a1688;

const MapSwapPtr SwapTransition = (MapSwapPtr)0x219ac8;
const MapSwapPtr SwapExterior = (MapSwapPtr)0x219848;

const HandleScreenPtr HandleMapScreen = (HandleScreenPtr)0x1a7348;
const HandleScreenPtr HandleGameScreen = (HandleScreenPtr)0x1a3190;
const HandleScreenPtr HandleLoadScreen = (HandleScreenPtr)0x1a62b0;
const HandleScreenPtr HandleSaveScreen = (HandleScreenPtr)0x1a6600;
const HandleScreenPtr HandleTitleScreen = (HandleScreenPtr)0x1a1128;

typedef void (*draw_text_ptr)(const char *, void *, const char *, int *, float, float, float, float, float, float, float);
int draw_text_buf[] = {0x0809681E, 0xc7b20000};
draw_text_ptr draw_text = (draw_text_ptr)/*draw_text_buf*/0x25a078;

// Color formatting codes are like so: \x01\x03\x09\x02\x03 followed by the color.
// 0xFD is represented as \xFD\x02 and values < 0x20 are done with \xFD follwoed by the value + 0x40

unsigned char map_type_table[] = {
	0x0,0x0,0x0,0x0,0x0,0x11,0xaa,0x56,0x99,0xaa,0x46,0x40,0x14,0xa1,0x2a,0x51,0x15,0x95,0x5a,0x56,0x15,0xaa,0x19,0x55,0x51,0x44,0x15,0x85,0x9a,0x6a,0xaa,0x59,0x15,0x54,0x55,0x65,0x40,0x55,0x55,0x54,0x45,0x5,0x15,0x94,0x9a,0xaa,0x4a,0x6a,0x2
};
char *char_buf = (char*)0x70000080;
const int char_buf_len = 0x400;
char *textbox_buf = (char*)0x70000480;
const int textbox_buf_len = 0x400;
bool debug_mode_on = false;
bool suppress_loads = false;
bool coords_display = false;
bool alignment_display = false;

float *old_map_matrix = (float*)0x70000000;
float *old_map_matrix_ptr;
int zone_map_last_exterior = 0;
int zone_map_last_interior = 0;
int zone_map_last_transition = 0;
int zone_map_last_active = 0;
bool need_zone_map_update = false;
float map_origin_x = 0;
float map_origin_z = 0;
float map_scale_x = 640/4 * 0.005;
float map_scale_z = 448/3 * 0.005;

float player_last_x = 0;
float player_last_z = 0;

char *alignment_strings[] = {
	"None",
	"Fire",
	"Earth",
	"Light",
	"Water",
	"Air",
	"Darkness",
	"Rainbow"
};

// Hack menu includes:
char *hack_menu_items[] = {
	"Load Area\n",
	"Give Item\n",
	"Edit NP\n",
	"Edit Flags\n",
	"Options\n",
	"Zone Map\n",
	"Save Game\n",
	"Cancel\n",
};
char *hex_digits = "0""\0""1""\0""2""\0""3""\0""4""\0""5""\0""6""\0""7""\0""8""\0""9""\0""a""\0""b""\0""c""\0""d""\0""e""\0""f";
char fade_color[] = {0x80, 0x0, 0x80, 0x0};

const int NUM_OPTIONS = 4;
char *options_menu_items[] = {
	"Debug Mode",
	"Suppress Loads",
	"Show Coordinates",
	"Show Alignments"
};
char *options_menu_description[] = {
	"Enables the debug mode\n"
	"that's part of the game.\n"
	"Usually requires reloading\n"
	"the current area to take effect.",
	
	"Disables any seamless load\n"
	"triggers. However, this does\n"
	"not affect any that work via,\n"
	"for example, pressing square.",

	"Enables the coordinate display\n"
	"Warning: can cause game crashes\n"
	"if there's too much text on the\n"
	"screen.",

	"Displays alignemtns of enemies\n"
	"Can causes crashes if there's\n"
	"too much text on the screen.\n"
};
bool *options_menu_flags[] = {
	&debug_mode_on,
	&suppress_loads,
	&coords_display,
	&alignment_display,
};

char *save_game_text = "Save Game (01)";
unsigned char save_page = 1;

short hacks_menu_idx = 0;

int load_area_id = 0;
short load_area_digit = 0;
bool loading_area_now = false;
int give_item_id = 0;
int give_item_page = 0;
int give_item_amount = 1;
short give_item_amount_digit = 0;
short neopoints_digit = 0;
int flag_id;
short flag_digit;

int last_player_state = 0;
int num_jumps_in_a_row = 0; 
int time_since_last_jump = 0;
int consequence_number = 0;

int current_ledge_fly = 0;
int ledge_fly_consequence = 0;
int load_delay = 0;

enum MenuState {
	MENU_OFF, MENU_MAIN, MENU_LOAD_AREA, MENU_GIVE_ITEM_ID, MENU_GIVE_ITEM_AMT, MENU_EDIT_NP, MENU_EDIT_FLAGS, MENU_OPTIONS
};
MenuState state;

int swizzle(int x, int y, int width) {
	return (((y & 2) >> 1)| ((x & 8) >> 2) | ((x & 3) << 2) | (((x & 4) ^ (y & 4) ^ ((y & 2) << 1)) << 2) | ((x & ~15) << 1)) + (((y & 1) | ((y & ~3) >> 1)) * width * 2);
}

void append_str(char *to, const char *from, int size) {
	char *end = to + size - 1;
	while(*to != 0 && to <= end) to++;
	while(*from != 0 && to < end) {
		*to = *from;
		from++;
		to++;
	}
	*to = 0;
}

void editable_number(int &number, short &sel_digit, int cbi, short min_digits, short max_digits, int radix, int max_val) {
	unsigned long long bcd = 0;
	unsigned int dived = number;
	int num_digits = 0;
	while(dived != 0) {
		bcd |= (dived % radix) << (num_digits << 2);
		dived /= radix;
		num_digits++;
	}
	if(sel_digit >= num_digits) num_digits = sel_digit+1;
	if(min_digits > num_digits) num_digits = min_digits;

	if(cbi & 0x2000) {
		sel_digit--;
		if(sel_digit < 0) sel_digit = max_digits-1;
		playmenusound(0x1);
	} else if(cbi & 0x8000) {
		sel_digit++;
		if(sel_digit >= max_digits) sel_digit = 0;
		playmenusound(0x1);
	}
	if(hacks_menu_idx != 0) {
		int digit_div = 1;
		for(int i = 0; i < sel_digit; i++) digit_div *= radix;
		int after_digit = number % digit_div;
		number /= digit_div;
		int digit = number % radix;
		number -= digit;
		digit -= hacks_menu_idx;
		if(digit < 0) digit = radix-1;
		if(digit >= radix) digit = 0;
		number += digit;
		number *= digit_div;
		number += after_digit;

		if(number > max_val) {
			if(hacks_menu_idx > 0) number = max_val;
			else number = 0;
		}
		if(number < 0) number = 0;

		hacks_menu_idx = 0;
	}
	for(int i = num_digits-1; i >= 0; i--) {
		if(i == sel_digit) append_str(char_buf, "\x01\x03\x09\x02\x03\xc8\x73\x32\x80", char_buf_len);
		append_str(char_buf, hex_digits + (((bcd >> (4*i)) & 0xF) << 1), char_buf_len);
		if(i == sel_digit) append_str(char_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80", char_buf_len);
	}
}

void CancelLedgeFly(bool exterior) {
	if(*((int*)(*((int*)0x35c7d4) + 0x144)) != 0x25) return; // don't be overzealous.
	*((int*)(*((int*)0x35c7d4) + 0x144)) = 1; // actually cancel it.
	load_delay = 30; // keep the map loader turned off for half a second.
	// now to give the player a snarky message for not ledge flying correctly.
	current_ledge_fly = 0;
	switch(ledge_fly_consequence) {
		case 0:
			textbox_buf[0] = 0;
			append_str(textbox_buf, "OwO... what's this?\x01\x02\x04\x04\x02You know, you have to be more careful when ledge flying.\x01\x02\x04\x04\x02Your ledge fly started on a ledge in the ", textbox_buf_len);

			if(exterior)
				append_str(textbox_buf, "\x01\x03\x09\x02\x03\x40\xa0\x40\x80""exterior", textbox_buf_len);
			else
				append_str(textbox_buf, "\x01\x03\x09\x02\x03\xa0\x40\x40\x80transition", textbox_buf_len);
			append_str(textbox_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80.\x01\x02\x04\x04\x02However, you carelessly flew over a bit of ", textbox_buf_len);
			if(exterior)
				append_str(textbox_buf, "\x01\x03\x09\x02\x03\xa0\x40\x40\x80transition", textbox_buf_len);
			else
				append_str(textbox_buf, "\x01\x03\x09\x02\x03\x40\xa0\x40\x80""exterior", textbox_buf_len);
			append_str(textbox_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80.\x01\x02\x04\x04\x02If I hadn't stopped you just in time...\x01\x02\x04\x04\x02Let's just say that switching between transition and exterior like that \x01\x03\x09\x02\x03\xa0\x40\x40\x80""crashes your game\x01\x03\x09\x02\x03\x80\x80\x80\x80.\x01\x02\x04\x04\x02You know how long this game takes to start up do you? \x01\x02\x04\x04\x02""Be more careful. I won't always be there to save you. \x01\x02\x04\x04\x02Love,\n    monster860", textbox_buf_len);
			DisplayDialogText(textbox_buf);
			break;
		case 1:
			DisplayDialogText("Well, well. Another ledge fly into the wrong place.\x01\x02\x04\x04\x02You really need to \x01\x03\x09\x02\x03\xa0\xa0\x40\x80""be more careful\x01\x03\x09\x02\x03\x80\x80\x80\x80 where you ledge fly.\x01\x02\x04\x04\x02Love,\n    monster860");
			break;
		case 2:
			for(int i = 0; i < 20000000; i++) QueryGameState(0);
			DisplayDialogText("\x01\x03\x09\x02\x03\xa0\x40\x40\x80Wait!\x01\x03\x09\x02\x03\x80\x80\x80\x80 Don't reset your console just yet!.\x01\x02\x04\x04\x02Your game didn't \x01\x03\x09\x02\x03\xa0\x40\x40\x80""actually\x01\x03\x09\x02\x03\x80\x80\x80\x80 crash.\x01\x02\x04\x04\x02I was able to save your game just from the brink of crashing once again!\x01\x02\x04\x04\x02Seriously though, if this was an actual run you'd probably be yelling some profanities right about now.\x01\x02\x04\x04\x02Luckily, this is not an actual run.\x01\x02\x04\x04\x02Right...........?\x01\x02\x04\x04\x02Love,\n    monster860");
			break;
		case 3:
			DisplayDialogText("Okay, since you keep coming back here, I guess I'll give you some free advice.\x01\x02\x04\x04\x02Whenever you ledge fly, you want to wait until the screen goes \x01\x03\x09\x02\x03\xa0\x40\x40\x80""all the way white\x01\x03\x09\x02\x03\x80\x80\x80\x80, and then \x01\x03\x09\x02\x03\x40\x60\xa0\x80hold ^\x01\x03\x09\x02\x03\x80\x80\x80\x80.\x01\x02\x04\x04\x02This will maximize the chances of your ledge fly being succesful!\x01\x02\x04\x04\x02Of course this won't prevent your game from crashing - that requires good aim.\x01\x02\x04\x04\x02""Anyways, if you already know this, I apologize, I am simply a piece of code, I can't read your mind.\x01\x02\x04\x04\x02Love,\n    monster860");
			break;
		default:
			DisplayDialogText("SCREEEEEEEEEEEEEEEEEEEEEE\x01\x02\x04\x04\x02You ledge flew into the wrong place again, and I stopped your game from crashing again.\x01\x02\x04\x04\x02Love,\n    monster860");
			break;
		}
		ledge_fly_consequence++;
}

extern "C" void SwapExteriorHook(int a0, int map, int a2, int a3) {
	if(/*map != *((int*)0x33F570) && */current_ledge_fly == 0x33F570) {
		CancelLedgeFly(true);
	}
	if(suppress_loads) return;
	if(load_delay > 0) {
		load_delay--;
		return;
	}
	SwapExterior(a0, map, a2, a3);
}

extern "C" void SwapTransitionHook(int a0, int map, int a2, int a3) {
	if(/*map != *((int*)0x339C20) && */current_ledge_fly == 0x339C20) {
		CancelLedgeFly(false);
	}
	if(suppress_loads) return;
	if(load_delay > 0) {
		load_delay--;
		return;
	}
	SwapTransition(a0, map, a2, a3);
}

void UpdateSavePage() {
	save_game_text[12] = (save_page % 10) + '0';
	save_game_text[11] = (save_page / 10) + '0';
	savegame_filename_ptr[10] = (save_page % 10) + '0';
	savegame_filename_ptr[9] = (save_page / 10) + '0';
}

bool HandleSavePaging(bool is_save) {
	int cbi = controller_buttons_instant;
	if(cbi & 0x8000) {
		save_page--;
		if(save_page < 1) save_page = 99;
		playmenusound(0x1);
		UpdateSavePage();
		return true;
	} else if(cbi & 0x2000) {
		save_page++;
		if(save_page > 99) save_page = 1;
		playmenusound(0x1);
		UpdateSavePage();
		return true;
	}
	return false;
}

extern "C" void *LoadScreenHook(int a0, int a1, int a2, int a3, int t0) {
	save_game_text[0] = 'L';
	save_game_text[1] = 'o';
	save_game_text[2] = 'a';
	save_game_text[3] = 'd';
	*((char**)0xB41AD4) = save_game_text;
	if(load_flag != 1 && HandleSavePaging(false)) {
		load_flag = 0;
	}
	return HandleLoadScreen(a0, a1, a2, a3, t0);
}

extern "C" void *SaveScreenHook(int a0, int a1, int a2, int a3, int t0) {
	save_game_text[0] = 'S';
	save_game_text[1] = 'a';
	save_game_text[2] = 'v';
	save_game_text[3] = 'e';
	*((char**)0xB41B04) = save_game_text;
	if(save_flag != 1 && HandleSavePaging(true)) {
		save_flag = 0;
	}
	return HandleSaveScreen(a0, a1, a2, a3, t0);
}

extern "C" void *MapScreenHook(int a0, int a1, int a2, int a3, int t0) {
	bool is_zone_map = *((int*)0x39ABD8) == (*((int*)(*((int*)0x39A37C) + 0x60)) + (0x14 * (0x1F + 0x27)));
	if(is_zone_map) {
		int retained = *((int*)(a3 + 0x89C)) & 0xF9B0; // Suppress triangle, square, circle, directionals, and start/select
		int retained2 = *((int*)(a3 + 0x894)) & 0xF9B0;
		int retained3 = *((int*)(a3 + 0x19C)) & 0xF9B0;
		int retained4 = *((int*)(a3 + 0x194)) & 0xF9B0;
		*((int*)(a3 + 0x89C)) &= ~retained;
		*((int*)(a3 + 0x894)) &= ~retained2;
		*((int*)(a3 + 0x19C)) &= ~retained3;
		*((int*)(a3 + 0x194)) &= ~retained4;
		HandleGameScreen(a0, a1, a2, a3, t0);
		*((int*)(a3 + 0x89C)) |= retained;
		*((int*)(a3 + 0x894)) |= retained2;
		*((int*)(a3 + 0x19C)) |= retained3;
		*((int*)(a3 + 0x194)) |= retained4;
	}

	int retained = *((int*)(a3 + 0x89C)) & 0x43; // Suppress L2, R2, and X
	int retained2 = *((int*)(a3 + 0x894)) & 0x43;
	if(is_zone_map) {
		*((int*)(a3 + 0x89C)) &= ~retained;
		*((int*)(a3 + 0x894)) &= ~retained2;
	}
	void *ret = HandleMapScreen(a0, a1, a2, a3, t0);
	if(is_zone_map) {
		*((int*)(a3 + 0x89C)) |= retained;
		*((int*)(a3 + 0x894)) |= retained2;
	}
	return ret;
}

extern "C" void WorldControlsHook(int a0) {
	int a3 = 0x455240;
	bool is_zone_map = *((int*)0x39ABD8) == (*((int*)(*((int*)0x39A37C) + 0x60)) + (0x14 * (0x1F + 0x27)));
	int retained = *((int*)(a3 + 0x89C)) & 0xF9B0; // Suppress triangle, square, circle, directionals, and start/select
	int retained2 = *((int*)(a3 + 0x894)) & 0xF9B0;
	int retained3 = *((int*)(a3 + 0x19C)) & 0xF9B0;
	int retained4 = *((int*)(a3 + 0x194)) & 0xF9B0;
	if(is_zone_map) {
		
		*((int*)(a3 + 0x89C)) &= ~retained;
		*((int*)(a3 + 0x894)) &= ~retained2;
		*((int*)(a3 + 0x19C)) &= ~retained3;
		*((int*)(a3 + 0x194)) &= ~retained4;
	}
	handle_world_controls(a0);
	if(is_zone_map) {
		*((int*)(a3 + 0x89C)) |= retained;
		*((int*)(a3 + 0x894)) |= retained2;
		*((int*)(a3 + 0x19C)) |= retained3;
		*((int*)(a3 + 0x194)) |= retained4;
	}
}

extern "C" void *ResumeGameHook(int a0, int a1, int a2, int a3, int t0) {
	if(loading_area_now) return (void*)0;
	int cbi = controller_buttons_instant;
	if(state == MENU_OFF) {
		if(cbi & 0x40) {
			state = MENU_MAIN;
			hacks_menu_idx = 0;
			playmenusound(0x5);
			cbi = 0;
		} else {
			return (void*)0;
		}
	}
	*((unsigned short*)(a3 + 0x89C)) &= ~0x10; // suppress triangle.
	char_buf[0] = 0;
	append_str(char_buf, "                                   Hack Menu\n", char_buf_len);
	if(state == MENU_MAIN) {
		if(cbi & 0x10) {
			playmenusound(0x6);
			state = MENU_OFF;
			return (void*)0;
		}
		if(hacks_menu_idx < 0) hacks_menu_idx = 7;
		if(hacks_menu_idx > 7) hacks_menu_idx = 0;
		for(int i = 0; i < 8; i++) {
			if(i == hacks_menu_idx) append_str(char_buf, "\x01\x03\x09\x02\x03\xc8\x73\x32\x80", char_buf_len);
			append_str(char_buf, hack_menu_items[i], char_buf_len);
			if(i == hacks_menu_idx) append_str(char_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80", char_buf_len);
		}
		if(cbi & 0x40) {
			switch(hacks_menu_idx) {
			case 0:
				playmenusound(0x5);
				state = MENU_LOAD_AREA;
				hacks_menu_idx = 0;
				break;
			case 1:
				playmenusound(0x5);
				state = MENU_GIVE_ITEM_ID;
				hacks_menu_idx = give_item_id;
				break;
			case 2:
				playmenusound(0x5);
				state = MENU_EDIT_NP;
				hacks_menu_idx = 0;
				break;
			case 3:
				playmenusound(0x5);
				state = MENU_EDIT_FLAGS;
				hacks_menu_idx = 0;
				break;
			case 4:
				state = MENU_OPTIONS;
				hacks_menu_idx = 0;
				playmenusound(0x5);
				break;
			case 5:
				HandleViewMap(a0, a1, a2, a3, t0); // opens the map hopefully
				if(*((int*)0x2dce4c) < 0) {
					*((int*)0x2dce4c) = 0x27; // If there's no map image thingy then point to the food chute.
				}
				need_zone_map_update = true; // and we'll have to update it later.
				int player_pointer;
				player_pointer = *((int*)(*((int*)0x35c7d4) + 0x16C));
				map_origin_x = *((float*)(player_pointer + 0x50));
				map_origin_z = *((float*)(player_pointer + 0x58));
				playmenusound(0x5);
				return (void*)(*((int*)(*((int*)0x39A37C) + 0x60)) + (0x14 * (0x1F + 0x27))); // but we return the map thingy for the food chute.
				break;
			case 6:
				playmenusound(0x5);
				return (void*)0xB3B6E0;
			default:
				playmenusound(0x6);
				state = MENU_OFF;
				break;
			}
			return (void*)0;
		}
	} else if(state == MENU_LOAD_AREA) {
		int map_type = (map_type_table[load_area_id >> 2] >> ((load_area_id & 0x3) << 1)) & 0x3;
		if(cbi & 0x10) {
			playmenusound(0x6);
			state = MENU_MAIN;
			hacks_menu_idx = 0;
			return (void*)0;
		} else if(cbi & 0x40) {
			loading_area_now = true;
			return HandleResumeGameTrampoline(a0, a1, a2, a3, t0);
		}
		append_str(char_buf, "ID: 0x", char_buf_len);
		/*if(load_area_digit) append_str(char_buf, "\x01\x03\x09\x02\x03\xc8\x73\x32\x80", char_buf_len);
		append_str(char_buf, hex_digits + ((load_area_id & 0xF0) >> 3), char_buf_len);
		if(load_area_digit) append_str(char_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80", char_buf_len);
		if(!load_area_digit) append_str(char_buf, "\x01\x03\x09\x02\x03\xc8\x73\x32\x80", char_buf_len);;
		append_str(char_buf, hex_digits + ((load_area_id & 0xF) << 1), char_buf_len);
		if(!load_area_digit) append_str(char_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80", char_buf_len);*/
		editable_number(load_area_id, load_area_digit, cbi, 2, 2, 16, 0xC0);
		append_str(char_buf, "\n\n(Type: ", char_buf_len);
		
		/*if(load_area_digit) {
			load_area_id = (load_area_id & 0xF) | ((load_area_id - (hacks_menu_idx << 4)) & 0xF0);
		} else {
			load_area_id = (load_area_id & 0xF0) | ((load_area_id - hacks_menu_idx) & 0x0F);
		}
		if(load_area_id < 0) load_area_id = 0;
		if(load_area_id > 0xC0) load_area_id = 0xC0;
		hacks_menu_idx = 0;*/

		switch(map_type) {
		case 0:
			append_str(char_buf, "\x01\x03\x09\x02\x03\x80\x40\x40\x80" "transition", char_buf_len);
			break;
		case 1:
			append_str(char_buf, "\x01\x03\x09\x02\x03\x40\x80\x40\x80" "exterior", char_buf_len);
			break;
		case 2:
			append_str(char_buf, "\x01\x03\x09\x02\x03\x40\x40\x80\x80" "interior", char_buf_len);
			break;
		}
		append_str(char_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80" ")", char_buf_len);
	} else if(state == MENU_GIVE_ITEM_ID) {
		if(cbi & 0x2000) {
			playmenusound(0x1);
			hacks_menu_idx += 10;
		} else if(cbi & 0x8000) {
			playmenusound(0x1);
			hacks_menu_idx -= 10;
		}
		
		if(hacks_menu_idx < 0) hacks_menu_idx = 0xb4;
		if(hacks_menu_idx > 0xb4) hacks_menu_idx = 0;
		if(hacks_menu_idx < give_item_page) give_item_page = hacks_menu_idx;
		if(hacks_menu_idx > give_item_page+9) give_item_page = hacks_menu_idx-9;

		if(cbi & 0x10) {
			playmenusound(0x6);
			state = MENU_MAIN;
			give_item_id = hacks_menu_idx;
			hacks_menu_idx = 1;
			return (void*)0;
		} else if(cbi & 0x40) {
			playmenusound(0x5);
			state = MENU_GIVE_ITEM_AMT;
			give_item_id = hacks_menu_idx;
			hacks_menu_idx = 0;
			return (void*)0;
		}
		for(int i = 0; i < 10; i++) {
			int item_id = i + give_item_page;
			char id_str[16];
			sprintf(id_str, "%d ", item_id);

			if(item_id == hacks_menu_idx) append_str(char_buf, "\x01\x03\x09\x02\x03\xc8\x73\x32\x80", char_buf_len);
			append_str(char_buf, id_str, char_buf_len);
			char *item_name = *((char**)(0x5517A0 + (item_id * 0x34)));
			if(item_name) {
				append_str(char_buf, item_name, char_buf_len);
			}
			if(item_id == hacks_menu_idx) append_str(char_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80\n", char_buf_len);
			else append_str(char_buf, "\n", char_buf_len);
		}
	} else if(state == MENU_GIVE_ITEM_AMT) {
		if(cbi & 0x10) {
			playmenusound(0x6);
			state = MENU_GIVE_ITEM_ID;
			hacks_menu_idx = give_item_id;
			return (void*)0;
		} else if(cbi & 0x40) {
			GiveItemToHero(give_item_id, give_item_amount, true);
			return HandleResumeGameTrampoline(a0, a1, a2, a3, t0);
		}
		char id_str[16];
		sprintf(id_str, "%d - ", give_item_id);

		append_str(char_buf, id_str, char_buf_len);
		char *item_name = *((char**)(0x5517A0 + (give_item_id * 0x34)));
		if(item_name) {
			append_str(char_buf, item_name, char_buf_len);
		}
		append_str(char_buf, "\n\nAmount: ", char_buf_len);
		editable_number(give_item_amount, give_item_amount_digit, cbi, 1, 4, 10, 9999);
	} else if(state == MENU_EDIT_NP) {
		if(cbi & 0x50) {
			playmenusound(0x6);
			state = MENU_MAIN;
			hacks_menu_idx = 2;
			return (void*)0;
		}
		append_str(char_buf, "$", char_buf_len);
		editable_number(*((int*)(*((int*)0x35c7ec) + 0x14)), neopoints_digit, cbi, 1, 7, 10, 9999999);
	} else if(state == MENU_EDIT_FLAGS) {
		if(cbi & 0x10) {
			playmenusound(0x6);
			state = MENU_MAIN;
			hacks_menu_idx = 3;
			return (void*)0;
		} else if(cbi & 0x40) {
			SetGameState(flag_id, !QueryGameState(flag_id));
			playmenusound(0x1);
		}
		append_str(char_buf, "Flag 0x", char_buf_len);
		editable_number(flag_id, flag_digit, cbi, 3, 3, 16, 0x2E6);
		if(QueryGameState(flag_id)) {
			append_str(char_buf, "\n\n  true", char_buf_len);
		} else {
			append_str(char_buf, "\n\n  false", char_buf_len);
		}
	} else if(state == MENU_OPTIONS) {
		if(hacks_menu_idx >= NUM_OPTIONS) hacks_menu_idx = 0;
		if(hacks_menu_idx < 0) hacks_menu_idx = NUM_OPTIONS-1;
		
		if(cbi & 0x10) {
			playmenusound(0x6);
			state = MENU_MAIN;
			hacks_menu_idx = 0;
			return (void*)0;
		} else if(cbi & 0x40) {
			*options_menu_flags[hacks_menu_idx] = !(*options_menu_flags[hacks_menu_idx]);
		}

		for(int i = 0; i < NUM_OPTIONS; i++) {
			if(i == hacks_menu_idx) append_str(char_buf, "\x01\x03\x09\x02\x03\xc8\x73\x32\x80", char_buf_len);
			append_str(char_buf, options_menu_items[i], char_buf_len);
			append_str(char_buf, *options_menu_flags[i] ? " - On\n" : " - Off\n", char_buf_len);
			if(i == hacks_menu_idx) append_str(char_buf, "\x01\x03\x09\x02\x03\x80\x80\x80\x80", char_buf_len);
		}
		append_str(char_buf, "\n\n", char_buf_len);
		append_str(char_buf, options_menu_description[hacks_menu_idx], char_buf_len);

	} else {
		state = MENU_OFF;
	}
	return (void*)0;
	//return HandleResumeGameTrampoline(a0, a1, a2, a3, t0);
}

extern "C" bool IsDebugMode() {
	return debug_mode_on;
}

extern "C" void SetWorldStart(int a0, int a1) {
	*((int*)0x2d7560) = a0;
	*((int*)0x2d7564) = a1;
}

extern "C" void* TitleScreenHook(int a0, int a1, int a2, int a3, int t0) {
	if(a0 == 0 && a1 >= 5 && (controller_buttons_instant & 0x40)) {
		playmenusound(0x5);
		return (void*)0xb3b6a4;
	} else {
		return HandleTitleScreen(a0, a1, a2, a3, t0);
	}
}

bool update_zone_map() {
	int image_buffer_id = *((int*)0xB5E610);
	if(image_buffer_id < 0) return false;
	int image_buffer_ptr = *(int*)(image_buffer_id == 0 ? 0xbe4f04 : 0xc26504);
	if(image_buffer_ptr < 0x100000) return false; // not done loading yet (scree why is this code running then?)
	if(!old_map_matrix_ptr) {
		old_map_matrix_ptr = (float*)(0x382f90 + (*((int*)0x2dce4c) * 0x50));
		for(int i = 0; i < 20; i++) {
			old_map_matrix[i] = old_map_matrix_ptr[i];
			old_map_matrix_ptr[i] = 0;
		}
	}

	old_map_matrix_ptr[0] = map_scale_x;
	old_map_matrix_ptr[10] = map_scale_z;
	old_map_matrix_ptr[12] = 256 - (map_origin_x * map_scale_x);
	old_map_matrix_ptr[14] = 224 - (map_origin_z * map_scale_z);

	int main_assets = *((int*)0x35C834);
	zone_map_last_active = main_assets;
	zone_map_last_exterior = *((int*)0x33F57C) ? *((int*)0x33F570) : 0;
	zone_map_last_transition = *((int*)0x339C2C) ? *((int*)0x339C20) : 0;
	zone_map_last_interior = *((int*)0x344ECC) ? *((int*)0x344EC0) : 0;
	int alt_assets = 0x33F570;
	int main_add = 8;
	int alt_add = 132;
	bool alt_color = (main_assets == 0x344EC0);
	if(main_assets == alt_assets) {
		alt_assets = 0x339C20;
		main_add = 132;
		alt_add = 8;
	}
	
	char *image_buffer = (char*)image_buffer_ptr;
	for(int i = 0; i < 256; i++) {
		int dblock = i / 32;
		int block = (i / 16) % 2;
		int chunk = (i / 8) % 2;
		int subindex = i % 8;
		
		int index = (dblock*32)+(((chunk*2)%8+block)*8)+subindex;
		char *offset = image_buffer + 512*448 + (i & 0xF)*4 + (i & 0xF0)*64;
		if(index < 8) {
			offset[0] = (index & 1) ? 0xf0 : 0;
			offset[1] = (index & 2) ? 0xf0 : 0;
			offset[2] = (index & 4) ? 0xf0 : 0;
			offset[3] = (index > 0) ? 0x80 : 0;
		} else if (index < 132) {
			int scl = index - 8 + 132;
			offset[0] = alt_color ? 0x60 : scl;
			offset[1] = 0x60;
			offset[2] = alt_color ? scl : 0x60;
			offset[3] = 0x60;
		} else {
			int scl = index - 132 + 132;
			offset[0] = 0x60;
			offset[1] = scl;
			offset[2] = 0x60;
			offset[3] = 0x60;
		}
	}
	void *zone_map = *((void**)(main_assets+0x57C0));
	short *load_map = *((short**)(main_assets+0x5904));
	if(!zone_map) {
		for(int i = 0; i < 512*448; i++) {
			image_buffer[i] = 0;
		}
		return true;
	}
	if(load_map) {
		short map_id_buffer[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		for(int i = 0; i < load_map[0]; i++) {
			short mid = load_map[i+3];
			for(int j = 0; j < 16; j++) {
				if(map_id_buffer[j] == mid) break;
				else if(map_id_buffer[j] == 0) {
					map_id_buffer[j] = mid;
					break;
				}
			}
		}
		for(int y = 0; y < 448; y++) {
			for(int x = 0; x < 512; x++) {
				float fx = (x - 256) / map_scale_x + map_origin_x;
				float fy = (y - 224) / map_scale_z + map_origin_z;
				int zx, zy;
				unsigned char color_to_assign = 0;
				if(GetZoneMapCoordinates(zone_map, &zx, &zy, fx, fy)) {
					void *tile = GetZoneMapEntry(zone_map, zx, zy);
					if(tile) {
						unsigned char load_index = *((unsigned char*)((int)tile + 0x18));
						if(load_index < load_map[0]) {
							short map_id = load_map[3+load_index];
							for(int j = 0; j < 16; j++) {
								if(map_id_buffer[j] == map_id) {
									color_to_assign = j;
									break;
								}
							}
						}
						
					}
				}
				image_buffer[swizzle(x, y, 512)] = color_to_assign;
			}
		}
	} else {
		// clear it
		for(int i = 0; i < 512*448; i++) {
			image_buffer[i] = 0;
		}
	}
	for(int y = 0; y < 448; y++) {
		if(y == 0 || y == 447) {
			for(int x = 0; x < 512; x++)
				image_buffer[swizzle(x, y, 512)] |= 0x80;
			continue;
		}
		for(int x = 0; x < 511; x++) {
			int swizzled = swizzle(x, y, 512);
			int swizzled_next = swizzle(x+1, y, 512);
			if((image_buffer[swizzled] & 0x7F) != image_buffer[swizzled_next] & 0x7F) {
				image_buffer[swizzled] |= 0x80;
				image_buffer[swizzled_next] |= 0x80;
			}
		}
	}
	for(int y = 1; y < 447; y++) {
		for(int x = 1; x < 511; x++) {
			int swizzled = swizzle(x, y, 512);
			int swizzled_next = swizzle(x, y+1, 512);
			if((image_buffer[swizzled] & 0x7F) != image_buffer[swizzled_next] & 0x7F) {
				image_buffer[swizzled] |= 0x80;
				image_buffer[swizzled_next] |= 0x80;
			}
		}
		image_buffer[swizzle(0, y, 512)] |= 0x80;
		image_buffer[swizzle(511, y, 512)] |= 0x80;
	}
	float min_height = 1234567.0f;
	float max_height = -7654321.0f;
	for(int y = 0; y < 448; y += 4) for(int x = 0; x < 512; x += 4) {
		float fx = (x - 256) / map_scale_x + map_origin_x;
		float fy = (y - 224) / map_scale_z + map_origin_z;
		int heck = 0;
		float fheight = get_floor_height(0, &heck, (void*)main_assets, fx, fy, -12345.0f);
		if(heck) {
			if(fheight < min_height) min_height = fheight;
			if(fheight > max_height) max_height = fheight;
			continue;
		}
		heck = 0;
		fheight = get_floor_height(0, &heck, (void*)alt_assets, fx, fy, -12345.0f);
		if(heck) {
			if(fheight < min_height) min_height = fheight;
			if(fheight > max_height) max_height = fheight;
		}
	}
	float height_range = max_height - min_height;
	for(int y = 0; y < 448; y++) {
		for(int x = 0; x < 512; x++) {
			int swizzled = swizzle(x, y, 512);
			int at = image_buffer[swizzled];
			if(at & 0x80) {
				at = at & 0x7F;
				while(at >= 7) {
					at -= 6;
				}
				image_buffer[swizzled] = at;
			} else {
				float fx = (x - 256) / map_scale_x + map_origin_x;
				float fy = (y - 224) / map_scale_z + map_origin_z;
				int heck = 0;
				float fheight = get_floor_height(0, &heck, (void*)main_assets, fx, fy, -12345.0f);
				if(heck) {
					int adjusted = (int)((fheight - min_height) / height_range * 123.0f);
					if(adjusted < 0) adjusted = 0;
					if(adjusted >= 124) adjusted = 123;

					image_buffer[swizzled] = main_add + adjusted;
				} else {
					fheight = get_floor_height(0, &heck, (void*)alt_assets, fx, fy, -12345.0f);
					if(heck) {
						int adjusted = (int)((fheight - min_height) / height_range * 123.0f);
						if(adjusted < 0) adjusted = 0;
						if(adjusted >= 124) adjusted = 123;
						image_buffer[swizzled] = alt_add + adjusted;
					} else {
						image_buffer[swizzled] = 0;
					}
				}
			}
		}
	}
	
	return true;
}

int yeet_timer = 0;

extern "C" void do_mod() {
	if(loading_area_now) {
		loading_area_now = false;
		int map_type = (map_type_table[load_area_id >> 2] >> ((load_area_id & 0x3) << 1)) & 0x3;
		switch(map_type) {
		case 1:
			load_area(0x33F570, get_area_file(load_area_id), 0xFFFF, -1, 0, 0, 1, fade_color, 0, 1);
			break;
		case 2:
			StartEnterInterior(load_area_id, 0xFFFF, 0xFFFF, fade_color);
			break;
		case 0:
			load_area(0x339C20, get_area_file(load_area_id), 0xFFFF, -1, 0, 0, 1, fade_color, 0, 1);
			break;
		}
	}
	if(*((int*)0x39ABD8) != 0xB3B5A0) state = MENU_OFF;
	if(*((int*)0x39ABD8) == (*((int*)(*((int*)0x39A37C) + 0x60)) + (0x14 * (0x1F + 0x27)))) {
		int cbi = controller_buttons_digital_instant;
		if((cbi & 0x80) && map_scale_x > 0.1f) {
			map_scale_x /= 1.3f;
			map_scale_z /= 1.3f;
			need_zone_map_update = true;
		} else if((cbi & 0x20) && map_scale_x < 10.0f) {
			map_scale_x *= 1.3f;
			map_scale_z *= 1.3f;
			need_zone_map_update = true;
		} else if((cbi & 0x1000)) {
			map_origin_z -= 100 / map_scale_z;
			need_zone_map_update = true;
		} else if((cbi & 0x4000)) {
			map_origin_z += 100 / map_scale_z;
			need_zone_map_update = true;
		} else if((cbi & 0x2000)) {
			map_origin_x += 100 / map_scale_x;
			need_zone_map_update = true;
		} else if((cbi & 0x8000)) {
			map_origin_x -= 100 / map_scale_x;
			need_zone_map_update = true;
		}
		if(zone_map_last_active != *((int*)0x35C834)) need_zone_map_update = true;
		if((zone_map_last_exterior != *((int*)0x33F570)) && *((int*)0x33F57C)) need_zone_map_update = true;
		if((zone_map_last_transition != *((int*)0x339C20)) && *((int*)0x339C2C)) need_zone_map_update = true;
		if((zone_map_last_interior != *((int*)0x344EC0)) && *((int*)0x344ECC)) need_zone_map_update = true;
		if(need_zone_map_update) {
			if(update_zone_map())
				need_zone_map_update = false;
		}
	} else {
		if(old_map_matrix_ptr) {
			for(int i = 0; i < 20; i++) {
				old_map_matrix_ptr[i] = old_map_matrix[i];
			}
			old_map_matrix_ptr = (float*)0;
		}
	}
	resume_game_ptr_2 = "Hack Menu";
	resume_game_ptr_1 = state == MENU_OFF ? resume_game_ptr_2 : char_buf;
	if(state != MENU_OFF && selected_select_item != 3) {
		if(selected_select_item < 3) hacks_menu_idx--;
		if(selected_select_item > 3) hacks_menu_idx++;
		selected_select_item = 3;
	}
	if(!(*((int*)0x35c7d4))) return;
	int player_state = *((int*)(*((int*)0x35c7d4) + 0x144));
	switch(player_state) {
	case 0x7:
	case 0xA:
	case 0x2B:
	case 0x2C:
	case 0x2D:
	case 0x2E:
		if(time_since_last_jump < 120 && player_state != last_player_state) {
			num_jumps_in_a_row++;
		}
		time_since_last_jump = 0;
	}
	if(player_state == 0x25 && player_state != last_player_state) {
		current_ledge_fly = *((int*)0x35C834);
	} else if(player_state != 0x25) {
		current_ledge_fly = 0;
	}
	time_since_last_jump++;
	if(time_since_last_jump >= 120) num_jumps_in_a_row = 1;
	last_player_state = player_state;

	if(num_jumps_in_a_row >= 40) {
		num_jumps_in_a_row = 0;
		switch(consequence_number) {
		case 0:
			DisplayDialogText("UwU... what's this?\x01\x02\x04\x04\x02What do you think you're doing?\x01\x02\x04\x04\x02You just jumped \x01\x03\x09\x02\x03\xa0\xa0\x40\x80""40 times\x01\x03\x09\x02\x03\x80\x80\x80\x80 in a row.\x01\x02\x04\x04\x02That's... not really a good use of time, is it?\x01\x02\x04\x04\x02If you keep doing that... let's just say \x01\x03\x09\x02\x03\xa0\x40\x40\x80things are going to happen\x01\x03\x09\x02\x03\x80\x80\x80\x80.\x01\x02\x04\x04\x02Love,\n    monster860");
			break;
		case 1:
			DisplayDialogText("What did I tell you?\x01\x02\x04\x04\x02Stop jumping around.\x01\x02\x04\x04\x02If you keep doing that, \x01\x03\x09\x02\x03\xa0\x40\x40\x80""bad things\x01\x03\x09\x02\x03\x80\x80\x80\x80 happen.\x01\x02\x04\x04\x02Love,\n    monster860");
			break;
		case 2:
			DisplayDialogText("Don't say I didn't warn you...               Y<<<<<<<<<<E<<<<<<<<<<<E<<<<<<<<<<<T<<<<<<<<<<.");
			yeet_timer = 1;
			break;
		case 3:
			DisplayDialogText("Okay, you win. Here, have some sick music.\x01\x02\x04\x04\x02Love,\n    monster860");
			int table_ptr;
			table_ptr = *((int*)0x2DFB88)+4;
			for(int i = 0; i <= 0xC0; i++) {
				*((int*)(table_ptr + 0x28*i)) = 0x2C;
			}
			break;
		default:
			DisplayDialogText("SCREEEEEEEEEEEEEEEEEEEEEE");
			break;
		}
		consequence_number++;
	}
	if(yeet_timer > 0) {
		yeet_timer++;
		if(yeet_timer > 300/* && *((int*)0x39ABD8) != 0xB3B6F4*/) {
			yeet_timer = 0;
			//*((int*)(*((int*)0x35c7d4) + 0x144)) = 0x10;
			KillBothHeroes();
		} else if(yeet_timer >= 96) {
			*((int*)(*((int*)0x35c7d4) + 0x144)) = 0x7;
			int p = *((int*)(*((int*)0x35c7d4) + 0x16C));
			*((float*)(p + 0x60)) = 50;
			if(yeet_timer < 150) *((float*)(p + 0x64)) = 50;
			*((float*)(p + 0x68)) = 50;
		}
	}

	if(*((int*)0x39ABD8) == 0xB3B62C && coords_display) {
		int player_pointer;
		player_pointer = *((int*)(*((int*)0x35c7d4) + 0x16C));
		float x = *((float*)(player_pointer + 0x50));
		float y = *((float*)(player_pointer + 0x54));
		float z = *((float*)(player_pointer + 0x58));
		float grv = *((float*)(player_pointer + 0x188));
		float yvel = *((float*)(player_pointer + 0x64));
		char x_buf[16], y_buf[16], z_buf[16], s_buf[16], grv_buf[16], yvel_buf[16];
		FloatToChar(x, 16, x_buf);
		FloatToChar(y, 16, y_buf);
		FloatToChar(z, 16, z_buf);
		float dx = x - player_last_x;
		float dz = z - player_last_z;
		FloatToChar(sqrtf((dx*dx)+(dz*dz))*30, 16, s_buf);
		FloatToChar(grv, 16, grv_buf);
		FloatToChar(yvel, 16, yvel_buf);
		sprintf(char_buf, "\x01\x03\x09\x02\x03\xa0\x40\x40\x80%s\n"
		"\x01\x03\x09\x02\x03\x40\xa0\x40\x80%s\n"
		"\x01\x03\x09\x02\x03\x60\x70\xa0\x80%s\n"
		"\x01\x03\x09\x02\x03\x60\xa0\xa0\x80Spd: %s\n"
		"\x01\x03\x09\x02\x03\x60\x40\xa0\x80Grv: %s\n"
		"\x01\x03\x09\x02\x03\xa0\xa0\x40\x80Yvel: %s", x_buf, y_buf, z_buf, s_buf, grv_buf, yvel_buf);
		DisplayScreenMessage(char_buf, -3.0f, 3.0f, 20.0f);
		player_last_x = x;
		player_last_z = z;
	}
	if(*((int*)0x39ABD8) == 0xB3B62C && alignment_display) {
		int num_enemies = *((int*)0x35c8f8);
		int *enemies = *((int**)0x35c8fc);
		for(int i = 0; i < num_enemies; i++) {
			int enemy = enemies[i];
			int vtable = *((int*)(enemy + 0x164));
			int (*alignment_fun)(int) = *(int (**)(int))(vtable + 0x114);
			int alignment = alignment_fun(enemy + *((int*)(vtable + 0x110)));
			if(alignment > 0 && alignment <= 7) {
				union {
					struct {
						float x, y, z, w;
					};
					u128 packed;
				} location;
				int entity_pointer = *((int*)(enemy + 0x16C));
				location.x = *((float*)(entity_pointer + 0x50));
				location.y = *((float*)(entity_pointer + 0x54));
				location.z = *((float*)(entity_pointer + 0x58));
				location.w = 1.0;
				DisplayWorldString(*((int*)0x35c884), location.packed, alignment_strings[alignment], false);
			}
		}
		//printf("\n");
	}
	 /*

	float pointer_as_float = *((float*)0x37b928);
	int pointer_as_int = *((int*)0x37b928);
	if(pointer_as_float != 0) {
		char fbuf[16];
		FloatToChar(pointer_as_float, 16, fbuf);
		sprintf(char_buf, "%s\n%x", fbuf, pointer_as_int);
		DisplayScreenMessage(char_buf, -2.0f, 2.0f, 20.0f);
	}

	// */

	//FloatToChar(txt_x, 15, float_buf1);
	//FloatToChar(txt_y, 15, float_buf2);
	//FloatToChar(txt_z, 15, float_buf3);
	//sprintf(char_buf, "at: %s, %s, %s", float_buf1, float_buf2, float_buf3);
	//DisplayScreenMessage("asdf", txt_x, txt_y, txt_z);
}
