/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */


static const unsigned int gappih    = 6;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 6;       /* vert inner gap between windows */
static const unsigned int gappoh    = 6;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 6;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */


static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
//static const char *fonts[]          = { "monospace:size=10" };
static const char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeStatus]  = { col_gray3, "#333333",  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, "#333333",  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, "#333333",  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x30", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "100x30", "-e", "ranger", NULL };
const char *spcmd3[] = {"netease-cloud-music", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
};

static const char *const autostart[] = {
	"sh", "-c","~/.dwm/autostart.sh",NULL, /* terminate */
	"sh", "-c","~/.dwm/bar.sh",NULL, /* terminate */
	"sh", "-c","~/.dwm/clock.sh",NULL, /* terminate */
	//"st", "-e","yay","-Syu",NULL, /* terminate */
	//"sh", "-c","while true;do ~/.dwm/bar.sh;sleep 1;done;",NULL /* bar */

};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                 instance                  title       tags mask     isfloating   isterminal  noswallow  monitor */
	{ "Gimp",	             NULL,		            	NULL,		0,				0,		 0,           0,      	 -1 },
	{ "Firefox",             NULL,		            	NULL,		1 << 8,			0,		 0,           0,      	 -1 },
	{ "st-256color",         "spterm",	            	NULL,		SPTAG(0),		1,		 1,           0,      	 -1 },
	{ NULL,		             "spfm",	            	NULL,		SPTAG(1),		1,		 0,           0,      	 -1 },
	{ "netease-cloud-music", NULL,	                    NULL,		SPTAG(2),		1,	     0,		      0,         -1 },
	{ "st-256color",        "st-256color",              NULL,		0,		        0,	     1,		      0,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run","-l","10","-c",NULL};
static const char *termcmd[]  = { "st", NULL };


#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } }, //dmenu_菜单
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } }, //终端

	{ MODKEY,                       XK_b,      togglebar,      {0} },     //隐藏显示状态栏

	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },

  /*{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },*/
	
    //调整主界面大小
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.02} }, 
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },


	{ MODKEY,                       XK_a,      togglegaps,     {0} },        //打开关闭边距
	{ MODKEY|ShiftMask,             XK_a,      defaultgaps,    {0} },        //重置到默认边距
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +1 } }, //加大边距
	{ MODKEY,                       XK_x,      incrgaps,       {.i = -1 } }, //减小边距

/*	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
*/

    { MODKEY|ShiftMask,             XK_minus,  spawn,	       SHCMD("pamixer --allow-boost -d 10;kill -44 $(pidof dwmblocks)") }, //音量减小
    { MODKEY|ShiftMask,             XK_equal,  spawn,	       SHCMD("pamixer --allow-boost -i 10;kill -44 $(pidof dwmblocks)") }, //音量加大
    { MODKEY|ShiftMask,             XK_0,      spawn,	       SHCMD("pamixer -t;pkill -RTMIN+12 dwmblocks") }, //静音

	{ MODKEY,	        	XK_r,		spawn,		SHCMD("st -e htop") }, // htop

	{ MODKEY,                       XK_space, zoom,           {0} }, //切换为Master
	{ MODKEY,                       XK_Tab,    view,          {0} }, //与之前Tag来回切换

	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} }, //关闭应用
    /*
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
    */


	{ MODKEY,		            	XK_w,		spawn,	   	    SHCMD("chromium --enable-features=WebUIDarkMode --force-dark-mode") }, //chromium 浏览器 暗黑模式

	//{ MODKEY,                       XK_space,  setlayout,      {0} },

	{ MODKEY,                       XK_l,      spawn,SHCMD("i3lock -c 000000") }, //锁屏
	{ MODKEY,                       XK_f,      togglefullscr,     {0} }, //全屏
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },  //悬浮切换
	{ MODKEY,                       XK_s,      togglesticky,   {0} },  //固定磁铁

  /*{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
*/

    //便签 应用
	{ MODKEY|ShiftMask,            	XK_Return, togglescratch,  {.ui = 0 } },  //ST 终端
	{ MODKEY|ShiftMask,            	XK_u,	   togglescratch,  {.ui = 1 } },  //Ranger 文件管理
	{ MODKEY|ShiftMask,            	XK_m,	   togglescratch,  {.ui = 2 } },


	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

    { MODKEY|ShiftMask,             XK_r,      self_restart,   {0} }, //重启dwm
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} }, //退出dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} }, // 移动窗口
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} }, //
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} }, //调整窗口大小
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
