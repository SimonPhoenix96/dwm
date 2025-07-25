/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "chromium"

/* appearance */
/* BorderMode=false */
static unsigned int borderpx = 0; /* border pixel of windows */
static unsigned int snap = 1;	  /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 8;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1;        /* 0 means no systray */
static unsigned int gappih = 20;  /* horiz inner gap between windows */
static unsigned int gappiv = 14;  /* vert inner gap between windows */
static unsigned int gappoh = 20;  /* horiz outer gap between windows and screen edge */
static unsigned int gappov = 14;  /* vert outer gap between windows and screen edge */
static int swallowfloating = 0;	  /* 1 means swallow floating windows by default */
static int smartgaps = 0;		  /* 1 means no outer gap when there is only one window */
static int showbar = 1;			  /* 0 means no bar */
static int topbar = 1;			  /* 0 means bottom bar */
// static char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
// static char *fonts[]          = { "xos4 Terminus:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true",
//"monospace:size=10"  };
static char *fonts[] = {"Terminus:size=10", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true", "monospace:size=10"};
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static const unsigned int baralpha = 140;
static const unsigned int borderalpha = 140;
static char selfgcolor[] = "#ffffff";
static char selbordercolor[] = "#a00000";
static char selbgcolor[] = "#6ba887";
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
	[SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

typedef struct
{
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL};
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL};
const char *spcmd3[] = {TERMINAL, "-n", "sphtop", "-g", "120x30", "-e", "htop", NULL};
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm", spcmd1},
	{"spcalc", spcmd2},
	{"sphtop", spcmd3},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    instance      title       	 tags mask    isfloating
	   isterminal  noswallow  monitor */
	{"KeePassXC", "keepassxc", "PW.kdbx - KeePassXC", 1 << 1, 0, 0, 0, -1},
	{"KeePassXC", "keepassxc", "Auto-Type - KeePassXC", 0, 0, 0, 0, -1},
	{"Steam", "Steam", "Steam", 1 << 4, 0, 0, 0, -1},
	{"Chromium", "chromium", "Navidrome - Chromium", 1 << 2, 0, 0, 0, -1},
	{"st-256color", "st-256color", "newsboat", 1 << 2, 0, 0, 0, -1},
	{"st-256color", "st-256color", "cmus", 1 << 2, 0, 0, 0, -1},
	{"st-256color", "st-256color", "somafm", 1 << 2, 0, 0, 0, -1},
	{"Chromium", "chromium", "SomaFM", 1 << 2, 0, 0, 0, -1},
	{"Chromium", "chromium", "dnbradio.com", 1 << 2, 0, 0, 0, -1},
	{"Chromium", "chromium", "WhatsApp - Chromium", 1 << 3, 0, 0, 0, -1},
	{"Chromium", "chromium",
	 "HBR1 - Dream Factory - Muses Radio Player - Chromium", 1 << 2, 0, 0, 0,
	 -1},
	{"Telegram", "telegram", NULL, 1 << 3, 0, 0, 0, -1},
	{"st-256color", "st-256color", "cointop", 1 << 6, 0, 0, 0, -1},
	{"Thunderbird", "Mail", NULL, 1 << 7, 0, 0, 0, -1},
	{NULL, "spterm", NULL, SPTAG(0), 1, 1, 0, -1},
	{NULL, "spcalc", NULL, SPTAG(1), 1, 1, 0, -1},
	{NULL, "sphtop", NULL, SPTAG(2), 1, 1, 0, -1},

};

/* layout(s) */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static float mfact = 0.55;			 /* factor of master area size [0.05..0.95] */
static int nmaster = 1;				 /* number of clients in master area */
static int resizehints = 0;			 /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1				 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
// #include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{"[]=", tile},	 /* Default: Master on left, slaves on right */
	{"TTT", bstack}, /* Master on top, slaves on bottom */

	{"[@]", spiral},   /* Fibonacci spiral */
	{"[\\]", dwindle}, /* Decreasing in size right and leftward */

	{"[D]", deck},	  /* Master on left, slaves in monocle-like mode on right */
	{"[M]", monocle}, /* All windows on top of eachother */

	{"|M|", centeredmaster},		 /* Master in middle, slaves on sides */
	{">M>", centeredfloatingmaster}, /* Same but master floats */

	{"><>", NULL}, /* no layout function means floating behavior */
	{NULL, NULL},
	{"###", gaplessgrid},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                          \
	{MODKEY, KEY, view, {.ui = 1 << TAG}},                         \
		{MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
		{MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},          \
		{MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define STACKKEYS(MOD, ACTION)                      \
	{MOD, XK_j, ACTION##stack, {.i = INC(-1)}},     \
		{MOD, XK_k, ACTION##stack, {.i = INC(+1)}}, \
		{MOD, XK_v, ACTION##stack, {.i = 0}}, /* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
											  /* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
											  /* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
											  /* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                     \
	{                                  \
		.v = (const char *[])          \
		{                              \
			"/bin/sh", "-c", cmd, NULL \
		}                              \
	}

/* commands */
static const char *termcmd[] = {TERMINAL, NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	{"color0", STRING, &normbordercolor},
	{"color8", STRING, &selbordercolor},
	{"color0", STRING, &normbgcolor},
	{"color4", STRING, &normfgcolor},
	{"color0", STRING, &selfgcolor},
	{"color4", STRING, &selbgcolor},
	{"borderpx", INTEGER, &borderpx},
	{"snap", INTEGER, &snap},
	{"showbar", INTEGER, &showbar},
	{"topbar", INTEGER, &topbar},
	{"nmaster", INTEGER, &nmaster},
	{"resizehints", INTEGER, &resizehints},
	{"mfact", FLOAT, &mfact},
	{"gappih", INTEGER, &gappih},
	{"gappiv", INTEGER, &gappiv},
	{"gappoh", INTEGER, &gappoh},
	{"gappov", INTEGER, &gappov},
	{"swallowfloating", INTEGER, &swallowfloating},
	{"smartgaps", INTEGER, &smartgaps},
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
	/* modifier                     key            function                argument */
	STACKKEYS(MODKEY,                              focus)
	STACKKEYS(MODKEY|ShiftMask,                    push)
	/* { MODKEY|ShiftMask,		XK_Escape,     spawn,	               SHCMD("") }, */
	{ MODKEY,			XK_grave,      spawn,	               {.v = (const char*[]){ "dmenuunicode", NULL } } },
	/* { MODKEY|ShiftMask,		XK_grave,      togglescratch,	       SHCMD("") }, */
	TAGKEYS(			XK_1,          0)
	TAGKEYS(			XK_2,          1)
	TAGKEYS(			XK_3,          2)
	TAGKEYS(			XK_4,          3)
	TAGKEYS(			XK_5,          4)
	TAGKEYS(			XK_6,          5)
	TAGKEYS(			XK_7,          6)
	TAGKEYS(			XK_8,          7)
	TAGKEYS(			XK_9,          8)
	{ MODKEY,			XK_0,	       view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,	       tag,                    {.ui = ~0 } },
	{ MODKEY,			XK_minus,      spawn,                  SHCMD("$HOME/.local/bin/keyboard-layout-switcher.sh") },
	{ MODKEY|ShiftMask,		XK_minus,      spawn,                  SHCMD("") },
	{ MODKEY,			XK_equal,      spawn,                  SHCMD("rofi -show calc -modi calc -no-show-match -no-sort")},
	{ MODKEY|ShiftMask,		XK_equal,      spawn,                  SHCMD("rofi -show emoji -modi emoji")},
	{ MODKEY,			XK_BackSpace,  spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY|ShiftMask,		XK_BackSpace,  spawn,                  {.v = (const char*[]){ "sysact", NULL } } },

	{MODKEY, XK_Tab, view, {0}},
	/* { MODKEY|ShiftMask,		XK_Tab,		spawn,		SHCMD("") }, */
	{MODKEY, XK_q, killclient, {0}},
	/* quit dwm, used for restarting after recompiling dwm */
	{ MODKEY|ShiftMask,		XK_q,          spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY,			XK_w,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
	{MODKEY | ShiftMask, XK_w, spawn, SHCMD("librewolf")},
	{MODKEY, XK_e, spawn, SHCMD("emacs")},
	{MODKEY | ShiftMask, XK_e, spawn, SHCMD(TERMINAL " -e emacs -nw")},
	{ MODKEY,			XK_r, spawn, SHCMD("dolphin")},
	{MODKEY | ShiftMask, XK_r, spawn, SHCMD(TERMINAL " -e btop --force-utf")},
	{MODKEY, XK_t, setlayout, {.v = &layouts[0]}},			   /* tile */
	{MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[1]}}, /* bstack */
	{MODKEY, XK_y, setlayout, {.v = &layouts[2]}},			   /* spiral */
	{MODKEY | ShiftMask, XK_y, setlayout, {.v = &layouts[3]}}, /* dwindle */
	{MODKEY, XK_u, setlayout, {.v = &layouts[4]}},			   /* deck */
	{MODKEY | ShiftMask, XK_u, setlayout, {.v = &layouts[5]}}, /* monocle */
	{MODKEY, XK_i, setlayout, {.v = &layouts[6]}},			   /* centeredmaster */
	{MODKEY | ShiftMask, XK_i, setlayout, {.v = &layouts[7]}}, /* centeredfloatingmaster */
	{MODKEY, XK_o, incnmaster, {.i = +1}},
	{MODKEY | ShiftMask, XK_o, incnmaster, {.i = -1}},
	{MODKEY, XK_p, spawn, SHCMD("$HOME/.local/bin/keyboard-layout-switcher.sh")},
	{MODKEY | ShiftMask, XK_p, spawn, SHCMD("")},
	{MODKEY, XK_bracketleft, spawn, SHCMD("notify-send \"$(date)\" \"$(uptime)\"")},
	{MODKEY | ShiftMask, XK_bracketleft, spawn, SHCMD("notify-send \"Memory\" \"$(free -h)\"")},
	{MODKEY, XK_bracketright, spawn, SHCMD("notify-send \"Disk\" \"$(df -h /)\"")},
	{MODKEY | ShiftMask, XK_bracketright, spawn, SHCMD("notify-send \"Temperature\" \"$(sensors | grep Core)\"")},
	{MODKEY, XK_backslash, view, {0}},
	/* { MODKEY|ShiftMask,		XK_backslash,		spawn,		SHCMD("") }, */

	{MODKEY, XK_a, togglegaps, {0}},
	{MODKEY | ShiftMask, XK_a, defaultgaps, {0}},
	{MODKEY, XK_s, togglesticky, {0}},
	/* { MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("") }, */
	{MODKEY, XK_d, spawn, SHCMD("rofi -show combi -combi-modes \"window,run,emoji\" -modes combi")},
	{MODKEY | ShiftMask, XK_d, spawn, SHCMD("keepassxc")},
	{MODKEY, XK_f, togglefullscr, {0}},
	{MODKEY | ShiftMask, XK_f, setlayout, {.v = &layouts[8]}},
	//{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	//{ MODKEY|ShiftMask,		XK_g,		shifttag,	{ .i = -1 } },
	{MODKEY, XK_h, setmfact, {.f = -0.05}},
	/* J and K are automatically bound above in STACKEYS */
	{MODKEY, XK_l, setmfact, {.f = +0.05}},
	{MODKEY | ShiftMask, XK_h, setcfact, {.f = -0.35}},
	{MODKEY | ShiftMask, XK_l, setcfact, {.f = +0.35}},
	{MODKEY, XK_semicolon, shiftview, {.i = 1}},
	{MODKEY | ShiftMask, XK_semicolon, shifttag, {.i = 1}},
	{MODKEY, XK_apostrophe, togglescratch, {.ui = 1}},
	{ MODKEY|ShiftMask,		XK_apostrophe,  togglescratch,          {.ui = 2} },
	//{ MODKEY|ShiftMask,		XK_apostrophe,	togglesmartgaps,	{0} },
	{MODKEY, XK_Return, spawn, {.v = termcmd}},
	{MODKEY | ShiftMask, XK_Return, togglescratch, {.ui = 0}},

	{MODKEY, XK_z, incrgaps, {.i = +3}},
	/* { MODKEY|ShiftMask,		XK_z,		spawn,		SHCMD("") }, */
	{MODKEY, XK_x, incrgaps, {.i = -3}},
	/* { MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("") }, */
	{MODKEY, XK_c, spawn, SHCMD(TERMINAL " -e code")},
	{MODKEY | ShiftMask, XK_c, spawn, SHCMD(TERMINAL " -e cointop")},
	/* V is automatically bound above in STACKKEYS */
	{MODKEY, XK_b, togglebar, {0}},
	/* { MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("") }, */
	{MODKEY | ShiftMask, XK_n, spawn, SHCMD(TERMINAL "")},
	{ MODKEY|ShiftMask,		XK_n,          spawn,                  SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 dwmblocks") },
	{MODKEY, XK_m, spawn, SHCMD(TERMINAL "")},
	{MODKEY | ShiftMask, XK_m, spawn, SHCMD(TERMINAL " -e pulsemixer")},
	{MODKEY, XK_comma, spawn, SHCMD("")},
	{MODKEY | ShiftMask, XK_comma, spawn, SHCMD("")},
	{MODKEY, XK_period, spawn, SHCMD("")},
	{MODKEY | ShiftMask, XK_period, spawn, SHCMD(TERMINAL " -e somafm")},

	{MODKEY, XK_Left, focusmon, {.i = -1}},
	{MODKEY | ShiftMask, XK_Left, tagmon, {.i = -1}},
	{MODKEY, XK_Right, focusmon, {.i = +1}},
	{MODKEY | ShiftMask, XK_Right, tagmon, {.i = +1}},

	{MODKEY, XK_Page_Up, shiftview, {.i = +1}},
	{MODKEY | ShiftMask, XK_Page_Up, shifttag, {.i = +1}},
	{MODKEY, XK_Page_Down, shiftview, {.i = -1}},
	{MODKEY | ShiftMask, XK_Page_Down, shifttag, {.i = -1}},
	{MODKEY, XK_Insert, spawn, SHCMD("")},

	{ MODKEY,			XK_F1,         spawn,                  SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
	{ MODKEY,			XK_F2,         spawn,                  SHCMD("")},
	{ MODKEY,			XK_F3,         spawn,                  {.v = (const char*[]){ "displayselect", NULL } } },
	{ MODKEY,			XK_F4,         spawn,                  SHCMD("")},
	{ MODKEY,			XK_F5,         spawn,                   SHCMD("")},
	{ MODKEY,			XK_F6,         spawn,                  SHCMD("")},
	{ MODKEY,			XK_F7,         spawn,                  SHCMD("")},
	{ MODKEY,			XK_F8,         spawn,                  SHCMD("")},
	{ MODKEY,			XK_F9,         spawn,                  {.v = (const char*[]){ "mounter", NULL } } },
	{ MODKEY,			XK_F10,        spawn,                  {.v = (const char*[]){ "unmounter", NULL } } },
	{ MODKEY,			XK_F11,        spawn,                  SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,			XK_F12,        spawn,                  SHCMD("remaps") },
	{ MODKEY,			XK_space,      zoom,                   {0} },
	{ MODKEY|ShiftMask,		XK_space,      togglefloating,         {0} },

	{0, XK_Print, spawn, SHCMD("")},
	{MODKEY, XK_Home, spawn, SHCMD("flameshot gui -c -p ~/Pictures/Screenshots")},
	{ShiftMask, XK_Home, spawn, SHCMD("")},
	{MODKEY | ShiftMask, XK_Print, spawn, SHCMD("")},
	{MODKEY, XK_Delete, spawn, SHCMD("")},
	{MODKEY, XK_Scroll_Lock, spawn, SHCMD("")},

	{ 0, XF86XK_AudioMute,                         spawn,                  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,                  spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+ -l 1.0; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,                  spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%- -l 1.0; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,                         spawn,                  {.v = (const char*[]){ "playerctl", "previous", NULL } } },
	{ 0, XF86XK_AudioNext,                         spawn,                  {.v = (const char*[]){ "playerctl", "next", NULL } } },
	{ MODKEY|ShiftMask, XF86XK_AudioPrev,          spawn,                  {.v = (const char*[]){ "playerctl", "position", "10-", NULL } } },
	{ MODKEY|ShiftMask, XF86XK_AudioNext,          spawn,                  {.v = (const char*[]){ "playerctl", "position", "10+", NULL } } },
	{ 0, XF86XK_AudioPause,                        spawn,                  {.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0, XF86XK_AudioPlay,                         spawn,                  {.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0, XF86XK_AudioStop,                         spawn,                  {.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ MODKEY|ShiftMask, XF86XK_AudioPlay,          spawn,                  {.v = (const char*[]){ "playerctl", "shuffle", "toggle", NULL } } },
	{ 0, XF86XK_AudioRewind,                       spawn,                  {.v = (const char*[]){ "playerctl", "position", "10-", NULL } } },
	{ 0, XF86XK_AudioForward,                      spawn,                  {.v = (const char*[]){ "playerctl", "position", "10+", NULL } } },
	{ 0, XF86XK_AudioMedia,                        spawn,                  {.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0, XF86XK_AudioMicMute,                      spawn,                  SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	/* { 0, XF86XK_PowerOff,                       spawn,                  {.v = (const char*[]){ "sysact", NULL } } }, */
	{ 0, XF86XK_Calculator,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,                             spawn,                  {.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
	{ 0, XF86XK_WWW,                               spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
	{ 0, XF86XK_DOS,                               spawn,                  {.v = termcmd } },
	{ 0, XF86XK_ScreenSaver,                       spawn,                  SHCMD("slock & xset dpms force off; playerctl pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,                          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ 0, XF86XK_Mail,                              spawn,                  SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e",  "lfub",  "/", NULL } } },
	/* { 0, XF86XK_Battery,                        spawn,                  SHCMD("") }, */
	{ 0, XF86XK_Launch1,                           spawn,                  {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,                    spawn,                  SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,                       spawn,                  {.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	{ 0, XF86XK_TouchpadOn,                        spawn,                  {.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,                   spawn,                  {.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,                 spawn,                  {.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },

	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ClkWinTitle, 0, Button2, zoom, {0}},
	{ClkStatusText, 0, Button1, sigdwmblocks, {.i = 1}},
	{ClkStatusText, 0, Button2, sigdwmblocks, {.i = 2}},
	{ClkStatusText, 0, Button3, sigdwmblocks, {.i = 3}},
	{ClkStatusText, 0, Button4, sigdwmblocks, {.i = 4}},
	{ClkStatusText, 0, Button5, sigdwmblocks, {.i = 5}},
	{ClkStatusText, ShiftMask, Button1, sigdwmblocks, {.i = 6}},
#endif
	{ClkStatusText, ShiftMask, Button3, spawn, SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h")},
	{ClkClientWin, MODKEY, Button1, movemouse, {0}},
	{ClkClientWin, MODKEY, Button2, defaultgaps, {0}},
	{ClkClientWin, MODKEY, Button3, resizemouse, {0}},
	{ClkClientWin, MODKEY, Button4, incrgaps, {.i = +1}},
	{ClkClientWin, MODKEY, Button5, incrgaps, {.i = -1}},
	{ClkTagBar, 0, Button1, view, {0}},
	{ClkTagBar, 0, Button3, toggleview, {0}},
	{ClkTagBar, MODKEY, Button1, tag, {0}},
	{ClkTagBar, MODKEY, Button3, toggletag, {0}},
	{ClkTagBar, 0, Button4, shiftview, {.i = -1}},
	{ClkTagBar, 0, Button5, shiftview, {.i = 1}},
	{ClkRootWin, 0, Button2, togglebar, {0}},
};

