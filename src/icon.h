#ifndef ICON_H
#define ICON_H

#define OO true
#define __ false

#define ICON_WIDTH 9
#define ICON_HEIGHT 9

/*  BLANK ICON

{{ __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ }};
*/


const bool close_icon[ICON_HEIGHT][ICON_WIDTH] PROGMEM =
{{ __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, OO, OO, OO, OO, OO, __, __ },
 { __, __, OO, OO, OO, OO, OO, __, __ },
 { __, __, __, OO, OO, OO, __, __, __ },
 { __, __, __, OO, OO, OO, __, __, __ },
 { __, __, __, __, OO, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ }};

const bool enter_icon[ICON_HEIGHT][ICON_WIDTH] PROGMEM =
{{ __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, OO, __ },
 { __, __, __, __, __, __, __, OO, __ },
 { __, __, __, __, __, __, __, OO, __ },
 { __, __, OO, __, __, __, __, OO, __ },
 { __, OO, OO, OO, OO, OO, OO, OO, __ },
 { __, __, OO, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ }};

const bool delete_icon[ICON_HEIGHT][ICON_WIDTH] PROGMEM =
{{ __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, OO, __, __, __, __, __ },
 { __, __, OO, OO, __, __, __, __, __ },
 { __, OO, OO, OO, OO, OO, OO, OO, __ },
 { __, __, OO, OO, __, __, __, __, __ },
 { __, __, __, OO, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ }};

const bool change_icon[ICON_HEIGHT][ICON_WIDTH] PROGMEM =
{{ __, __, __, __, __, __, __, __, __ },
 { __, __, __, OO, OO, OO, __, __, __ },
 { __, __, OO, __, __, __, OO, __, __ },
 { __, OO, OO, OO, __, __, OO, OO, __ },
 { __, OO, __, __, __, __, __, OO, __ },
 { __, OO, __, OO, __, OO, __, OO, __ },
 { __, __, OO, OO, __, __, OO, __, __ },
 { __, __, __, OO, OO, OO, __, __, __ },
 { __, __, __, __, __, __, __, __, __ }};

const bool wifi_signal_weak[ICON_HEIGHT][ICON_WIDTH] PROGMEM =
{{ __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, OO, __, __, __, __ },
 { __, __, __, OO, OO, OO, __, __, __ },
 { __, __, __, __, OO, __, __, __, __ }};

const bool wifi_signal_normal[ICON_HEIGHT][ICON_WIDTH] PROGMEM =
{{ __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, __, __, __, __, __, __ },
 { __, __, __, OO, OO, OO, __, __, __ },
 { __, __, OO, __, __, __, OO, __, __ },
 { __, OO, __, __, OO, __, __, OO, __ },
 { __, OO, __, OO, OO, OO, __, OO, __ },
 { __, __, __, __, OO, __, __, __, __ }};

const bool wifi_signal_strong[ICON_HEIGHT][ICON_WIDTH+2] PROGMEM =
{{__, __, __, __, __, __, __, __, __, __, __ },
 {__, __, __, __, __, __, __, __, __, __, __ },
 {__, __, __, OO, OO, OO, OO, OO, __, __, __ },
 {__, __, OO, __, __, __, __, __, OO, __, __ },
 {__, OO, __, __, OO, OO, OO, __, __, OO, __ },
 {OO, __, __, OO, __, __, __, OO, __, __, OO },
 {OO, __, OO, __, __, OO, __, __, OO, __, OO },
 {__, __, OO, __, OO, OO, OO, __, OO, __, __ },
 {__, __, __, __, __, OO, __, __, __, __, __ }};

const bool wifi_disconnet[ICON_HEIGHT][ICON_WIDTH] PROGMEM =
{{ __, __, __, __, __, __, __, __, __ },
 { __, OO, __, __, __, __, __, OO, __ },
 { __, __, OO, __, __, __, OO, __, __ },
 { __, __, __, OO, __, OO, __, __, __ },
 { __, __, __, __, OO, __, __, __, __ },
 { __, __, __, OO, __, OO, __, __, __ },
 { __, __, OO, __, __, __, OO, __, __ },
 { __, OO, __, __, __, __, __, OO, __ },
 { __, __, __, __, __, __, __, __, __ }};



#undef OO
#undef __

#endif