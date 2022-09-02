/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
#define ICONSIZE 28   /* icon size */
#define ICONSPACING 6 /* space between icon and title */

static const Bool viewontag         = False;     /* Switch view on tag switch */
//内边距
static const int horizpadbar        = 10;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;       /* vertical padding for statusbar */

//与屏幕间距 
static const int vertpad            = 10;       /* vertical padding of bar */  
static const int sidepad            = 10;       /* horizontal padding of bar */

//static const char *fonts[]          = { "monospace:size=10", "NotoColorEmoji:pixelsize=24:antialias=true"  };
static const char *fonts[]          ={"Monaco:pixelsize=24:antialias=true", "NotoColorEmoji:pixelsize=24:antialias=true"};
static const char dmenufont[]       = "Monaco:pixelsize=30:antialias=true";

static const char col_gray1[]       = "#303030";  //#状态条底色
static const char col_gray2[]       = "#404040";  //#当static const unsigned int borderpx不为0时，非活动窗口外边框颜色
static const char col_gray3[]       = "#bbbbbb";  //#当前非活动的title字体颜色
static const char col_gray4[]       = "#eeeeee";  //#当前活动的title字体颜色
static const char col_cyan[]        = "#505050";  //#title底色
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#bbbbbb", "#404040", "#404040" },
	[SchemeSel]  = { "#eeeeee", "#606060", "#808080"  },
};



typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"lx-music-desktop", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"splx-music-desktop",   spcmd3},
};



static const char *const autostart[] = {
//	"sh", "-c","~/.dwm/autostart.sh",NULL, /* terminate */
	"dwmblocks",NULL,
	"redshift",NULL,
	"fcitx5",NULL,
	"picom","-b","--experimental-backends",NULL,
    "sh","-c","sudo echo 3 | sudo tee /proc/sys/net/ipv4/tcp_fastopen ",NULL,
    "trojan-go","-config","/etc/trojan/config.json",NULL,
    "sh","-c","feh --bg-center ~/wallpaper/01.jpg",NULL,
    "xmodmap ~/.xmodmaprc",NULL,
    "wmname","LG3D",NULL,
    "batsignal","-b",NULL,
    "twmnd",NULL,
   "sh", "-c","~/.dwm/clock.sh",NULL, /* terminate */
   "sh", "-c","~/.dwm/battery-status.sh",NULL, /* terminate */
 //   "sh","-c","~/.dwm/bin/terminal",NULL
};

/* tagging */
static const char *tags[] = { "1.cmd", "2.web", "3.code", "4.note","5.read","6.video", "7.music", "8.wmware", "9.otheres" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	 /*class             instance        title       tags mask     isfloating   monitor */
	{ "Gimp",            NULL,           NULL,       0,            1,           -1 },
	{ "Firefox",         NULL,           NULL,       8,            0,           -1 },
	{ "Google-chrome",   NULL,           NULL,       2,            0,           -1 },
	{ NULL,	       	     "spterm",		 NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		         "spfm",		 NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		         "keepassxc",	 NULL,		SPTAG(2),		0,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *menucmd[]  = { "sh","-c","~/.dwm/bin/menu", NULL };
static const char *termcmd[]  = { "sh","-c","~/.dwm/bin/terminal", NULL };
static const char *lock[]  = { "sh","-c","~/.dwm/bin/lock", NULL };
static const char *changebg[]  = { "sh","-c","~/.dwm/change_bg.sh", NULL };
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     	key        function        argument */
	{ MODKEY|ShiftMask,             	XK_b,      spawn,          {.v = changebg } }, //dmenu菜单
	{ MODKEY,                       	XK_p,      spawn,          {.v = menucmd } },
	{ MODKEY,                       	XK_d,      spawn,          SHCMD("rofi -show")},
	{ MODKEY,                       	XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       	XK_b,      togglebar,      {0} },
	{ MODKEY,                       	XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       	XK_k,      focusstack,     {.i = -1 } },
//	{ MODKEY,                       	XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       	XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       	XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       	XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       	XK_space,  zoom,           {0} },
	{ MODKEY,                       	XK_Tab,    view,           {0} },
	{ MODKEY,                       	XK_q,      killclient,     {0} },
	{ MODKEY,                       	XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,                       	XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       	XK_m,      setlayout,      {.v = &layouts[2]} },
//	{ MODKEY,                       	XK_equal,  setlayout,      {0} },
	{ MODKEY,                       	XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             	XK_space,  togglefloating, {0} },


    { MODKEY|ShiftMask,            		XK_Return, togglescratch,  {.ui = 0 } },
	{ MODKEY,            				XK_e,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,            		XK_m,	   togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,             	XK_l,      spawn,          {.v = lock } },


	{ MODKEY,                   		XK_o,	   spawn,          SHCMD("sh ~/.dwm/mouse_enable.sh")},
	{ MODKEY|ShiftMask,             	XK_o,	   spawn,          SHCMD("sh ~/.dwm/mouse_disable.sh")},


//	{ MODKEY,                       	XK_0,      view,           {.ui = ~0 } },
//	{ MODKEY|ShiftMask,             	XK_0,      tag,            {.ui = ~0 } },
//	{ MODKEY,                       	XK_comma,  focusmon,       {.i = -1 } },
//	{ MODKEY,                       	XK_period, focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,             	XK_comma,  tagmon,         {.i = -1 } },
//	{ MODKEY|ShiftMask,             	XK_period, tagmon,         {.i = +1 } },
//
	{ Mod1Mask,                     	XK_minus,  setgaps,        {.i = -2 } },
	{ Mod1Mask,                     	XK_equal,  setgaps,        {.i = +2 } },
	{ Mod1Mask|ShiftMask,           	XK_equal,  setgaps,        {.i = 0  } },

        { 0,                            	XF86XK_AudioMute,           spawn,      SHCMD("pamixer -t;pkill -RTMIN+10 dwmblocks;") },
	{ 0,                            	XF86XK_AudioRaiseVolume,    spawn,      SHCMD("pamixer --allow-boost -i 5;pkill -RTMIN+10 dwmblocks") },
	{ 0,                            	XF86XK_AudioLowerVolume,    spawn,      SHCMD("pamixer --allow-boost -d 5;pkill -RTMIN+10 dwmblocks") },

	{ 0,                            	XF86XK_Calculator,          spawn,      SHCMD("st -e bc -l") },

   	{ 0,                            	XF86XK_MonBrightnessUp,	    spawn,	SHCMD("light -A 5; pkill -RTMIN+9 dwmblocks") },
	{ 0,                            	XF86XK_MonBrightnessDown,   spawn,	SHCMD("light -U 5; pkill -RTMIN+9 dwmblocks") },

	{ MODKEY,                   		XK_w,	   spawn,           SHCMD("/usr/bin/google-chrome-stable")},
	{ MODKEY,                   		XK_a,	   spawn,           SHCMD("~/.dwm/bin/flameshot")},

	//{ MODKEY|ShiftMask,  		       XK_r,      resizemouse,     {0} },
	{ MODKEY|ControlMask|ShiftMask,        XK_r,      quit,            {1} },
	{ MODKEY|ShiftMask|ControlMask,        XK_q,      quit,            {0} },





	TAGKEYS(                        	XK_1,                      0)
	TAGKEYS(                        	XK_2,                      1)
	TAGKEYS(                        	XK_3,                      2)
	TAGKEYS(                        	XK_4,                      3)
	TAGKEYS(                        	XK_5,                      4)
	TAGKEYS(                        	XK_6,                      5)
	TAGKEYS(                        	XK_7,                      6)
	TAGKEYS(                        	XK_8,                      7)
	TAGKEYS(                        	XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
      //{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

