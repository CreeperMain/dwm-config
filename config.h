/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 14;        /* vertical padding for statusbar */
static const int vertpad            = 12;       /* vertical padding of bar */
static const int sidepad            = 15;       /* horizontal padding of bar */
static const char *fonts[]          = {
	"mononoki-Regular.otf:style:medium:size=12" ,
	"JetBrainsMonoNerdFontMono-Regular.ttf:pixelsize=27:style=bold" 
	};
#include "tokyonight.h"
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { white, black2, black1 },
	[SchemeSel]  = { white, black1,  white  },
	[SchemeHid]  = { tblack,  black2, red  },
	[SchemeStatus]  = { white, black2,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { white, black1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { tblack, black2,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { white, black2,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { white, black2,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "", "","󰟒", "󰆍", "󰯉", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Audacity",     NULL,       NULL,       0,            1,           -1 },
	{ "Virt-manager",     NULL,       NULL,       0,            1,           -1 },
	{ "Viewnior",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char dmenufont[] = "mononoki-Regular.otf:style:medium:size=12";
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("alacritty") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("steam") },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("librewolf") },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("vscodium") },
	{ MODKEY,                       XK_s,      spawn,          SHCMD("flameshot gui") },
	{ MODKEY,                       XK_x,      spawn,          SHCMD("sleep 1 && xset dpms force off") },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("virt-viewer --connect qemu:///system") },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("firejail --noprofile --net=none obsidian") },
	{ MODKEY,         			    XK_a,      spawn,          SHCMD("firejail --noprofile --net=none audacity") },
//	{ MODKEY|ControlMask,           XK_e,      spawn,          SHCMD("setxkbmap us") }, //najdi nachin da rabotit so kirlichno e
	{ MODKEY|ControlMask,           XK_0,      spawn,          SHCMD("setxkbmap us") },
	{ MODKEY|ControlMask,           XK_m,      spawn,          SHCMD("setxkbmap mk") },
	{ MODKEY|ControlMask,           XK_s,      spawn,          SHCMD("setxkbmap rs") },
	{ MODKEY|ControlMask,           XK_r,      spawn,          SHCMD("setxkbmap ru phonetic") },
	{ MODKEY|ControlMask,           XK_d,      spawn,          SHCMD("setxkbmap de") },
	{ MODKEY|ControlMask,           XK_g,      spawn,          SHCMD("setxkbmap gr") },
	{ MODKEY|ControlMask,           XK_h,      spawn,          SHCMD("setxkbmap hr") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_l,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_h,      focusstackvis,  {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_l,      focusstackhid,  {.i = +1 } }, // to rotate through all windows in a workspace including hidden ones
	{ MODKEY|Mod1Mask,              XK_h,      focusstackhid,  {.i = -1 } },
    { MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },//nigggg
	{ MODKEY|ShiftMask,             XK_j,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_k,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_r,      setcfact,       {.f =  0.00} },
	{ MODKEY|ControlMask,           XK_j,      inplacerotate,  {.i = +1} }, // like vim
	{ MODKEY|ControlMask,           XK_k,      inplacerotate,  {.i = -1} }, // gore dolu like vim
	{ MODKEY|ControlMask,           XK_h,      inplacerotate,  {.i = +2} }, // rotates clockwise 
	{ MODKEY|ControlMask,           XK_l,      inplacerotate,  {.i = -2} }, // rotates counter clockwise
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_b,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|Mod4Mask,              XK_b,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|Mod4Mask,              XK_g,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY|ControlMask,           XK_g,      setlayout,      {.v = &layouts[10]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY|Mod4Mask,              XK_m,      setlayout,      {.v = &layouts[12]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,        	XK_f,      togglefullscr,  {0} }, //chagne all layouts to use control
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_s,      show,           {0} },
	{ MODKEY|Mod1Mask,              XK_h,      hide,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};
// winkey + <key> -- exceute command
// winkey + shift + <key> -- launch program
// winkey + control + <key> -- choose a keyboard layout

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

