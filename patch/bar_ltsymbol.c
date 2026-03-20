int
width_ltsymbol(Bar *bar, BarArg *a)
{
	#if BAR_PANGO_PATCH // renzo
	return TEXTWM(bar->mon->ltsymbol);
	#else
	return TEXTW(bar->mon->ltsymbol);
	#endif // BAR_PANGO_PATCH
}

int
draw_ltsymbol(Bar *bar, BarArg *a)
{
<<<<<<< HEAD
	#if BAR_LTSYMBOL_SCHEME_PATCH
	drw_setscheme(drw, scheme[SchemeLtSymbol]);
	#endif // BAR_LTSYMBOL_SCHEME_PATCH
=======
	#if BAR_PANGO_PATCH // renzo
	return drw_text(drw, a->x, a->y, a->w, a->h, lrpad / 2, bar->mon->ltsymbol, 0, True);
	#else
>>>>>>> 098ffab (Huge refactor: customized dwm-flexipatch extensively)
	return drw_text(drw, a->x, a->y, a->w, a->h, lrpad / 2, bar->mon->ltsymbol, 0, False);
	#endif // BAR_PANGO_PATCH
}

int
click_ltsymbol(Bar *bar, Arg *arg, BarArg *a)
{
	return ClkLtSymbol;
}
