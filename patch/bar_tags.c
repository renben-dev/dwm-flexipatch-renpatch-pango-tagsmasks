int
width_tags(Bar *bar, BarArg *a)
{
	int w, i;
	#if BAR_HIDEVACANTTAGS_PATCH
	Client *c;
	unsigned int occ = 0;
	for (c = bar->mon->clients; c; c = c->next)
		//occ |= c->tags == 255 ? 0 : c->tags;
		occ |= c->tags == TAGMASK ? 0 : c->tags; //renzo correction to git
	#endif // BAR_HIDEVACANTTAGS_PATCH

	for (w = 0, i = 0; i < NUMTAGS; i++) {
		#if BAR_HIDEVACANTTAGS_PATCH
		if (!(occ & 1 << i || bar->mon->tagset[bar->mon->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH

		#if BAR_PANGO_PATCH // renzo
		w += TEXTWM(tagicon(bar->mon, i));
		#else
		w += TEXTW(tagicon(bar->mon, i));
		#endif // BAR_PANGO_PATCH

	}
	return w;
}

int
draw_tags(Bar *bar, BarArg *a)
{
	int invert;
	int w, x = a->x;
	unsigned int i, occ = 0, urg = 0;
	#if BAR_PANGO_PATCH //renzo
	const char *
	#else
	char *
	#endif // BAR_PANGO_PATCH
	icon;
	Client *c;
	Monitor *m = bar->mon;

	// renz start : adding pango to tags draw
	int markup = 0;
	#if BAR_PANGO_PATCH 
	markup =1;
	#endif // BAR_PANGO_PATCH
	// renzo end

	for (c = m->clients; c; c = c->next) {
		#if BAR_HIDEVACANTTAGS_PATCH
		//occ |= c->tags == 255 ? 0 : c->tags;
		occ |= c->tags == TAGMASK ? 0 : c->tags; //renzo correction to git
		#else
		occ |= c->tags;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		if (c->isurgent)
			urg |= c->tags;
	}
	for (i = 0; i < NUMTAGS; i++) {
		#if BAR_HIDEVACANTTAGS_PATCH
		/* do not draw vacant tags */
		if (!(occ & 1 << i || m->tagset[m->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH

		icon = tagicon(bar->mon, i);
		invert = 0;
		
		// renzo start
		#if BAR_PANGO_PATCH
		w = TEXTWM(icon);
		#else
		w = TEXTW(icon);
		#endif // BAR_PANGO_PATCH
		// renzo end

		#if BAR_PER_TAG_COLOR_RENBEN_PATCH
		if(colorful_tags){
			drw_setscheme(drw, scheme[
				m->tagset[m->seltags] & 1 << i ?
					(underline_sel_tags ?
						SchemeTagsNorm00 + i
						: SchemeTagsSel
					)
					: (urg & 1 << i ?
						//SchemeUrg // renzo: invert on urg variant in line below
						SchemeTagsNorm00 + i
						: ((occ & (1 << i)) == 0 ?
							SchemeTagsNormUnoccupied
							: SchemeTagsNorm00 + i
						)
					)
			]);
			// renzo: invert on urg variant in line below
			if(urg & 1 << i){
				invert =1;
			}
		}
		else{
		#endif //BAR_PER_TAG_COLOR_RENBEN_PATCH
			drw_setscheme(drw, scheme[
				m->tagset[m->seltags] & 1 << i ? 
					SchemeTagsSel
					:(
					urg & (1 << i) ? 
						SchemeUrg
						:
						SchemeTagsNorm
					)
			]);
		#if BAR_PER_TAG_COLOR_RENBEN_PATCH
		}	
		#endif //BAR_PER_TAG_COLOR_RENBEN_PATCH
		#if BAR_TAG_NUM_CLIENTS_INDICATOR_RENBEN_PATCH
		int dx= 0;
		if(tag_num_clients_type == INDICATOR_NUMBER_OF_CLIENTS_TOP_LEFT || tag_num_clients_type == INDICATOR_NUMBER_OF_CLIENTS_BOTTOM_LEFT){
			x += drawindicator_num_clients(m, NULL, occ, x, a->y, a->h, lrpad / 2, 0, i, invert, tag_num_clients_type);
			drw_text(drw, x, a->y, w - lrpad/2, a->h, 0, icon, invert, markup);
		}
		else if(tag_num_clients_type == INDICATOR_NUMBER_OF_CLIENTS_TOP_RIGHT || tag_num_clients_type == INDICATOR_NUMBER_OF_CLIENTS_BOTTOM_RIGHT){
			drw_text(drw, x, a->y, w - lrpad/2, a->h, lrpad/2, icon, invert, markup);
			dx = drawindicator_num_clients(m, NULL, occ, x, a->y, a->h, 0, lrpad / 2, i, invert, tag_num_clients_type);
		}
		#else
		drw_text(drw, x, a->y, w, a->h, lrpad / 2, icon, invert, markup);
		#endif // BAR_TAG_NUM_CLIENTS_INDICATOR_RENBEN_PATCH
		drawindicator(m, NULL, occ, x, a->y, w, a->h, i, -1, invert, tagindicatortype);
		
		#if BAR_PER_TAG_COLOR_RENBEN_PATCH
			if(underline_sel_tags){
				if (m->tagset[m->seltags] & 1 << i)
					drw_rect(drw, x + ulinepad, bh - ulinestroke - ulinevoffset, w - (ulinepad * 2), ulinestroke, 1, invert);
			}
		#elif BAR_UNDERLINETAGS_PATCH
		if (ulineall || m->tagset[m->seltags] & 1 << i)
			drw_rect(drw, x + ulinepad, bh - ulinestroke - ulinevoffset, w - (ulinepad * 2), ulinestroke, 1, 0);
		#endif // BAR_UNDERLINETAGS_PATCH //BAR_PER_TAG_COLOR_RENBEN_PATCH
		x += w;
	}

	return 1;
}

int
click_tags(Bar *bar, Arg *arg, BarArg *a)
{
	int i = 0, x = 0;
	#if BAR_HIDEVACANTTAGS_PATCH
	Client *c;
	unsigned int occ = 0;
	for (c = bar->mon->clients; c; c = c->next)
		//occ |= c->tags == 255 ? 0 : c->tags;
		occ |= c->tags == TAGMASK ? 0 : c->tags; //renzo correction to git
	#endif // BAR_HIDEVACANTTAGS_PATCH

	do {
		#if BAR_HIDEVACANTTAGS_PATCH
		if (!(occ & 1 << i || bar->mon->tagset[bar->mon->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH

		#if BAR_PANGO_PATCH //renzo
		x += TEXTWM(tagicon(bar->mon, i));
		#else
		x += TEXTW(tagicon(bar->mon, i));
		#endif //BAR_PANGO_PATCH
	} while (a->x >= x && ++i < NUMTAGS);
	if (i < NUMTAGS) {
		arg->ui = 1 << i;
	}
	#if BAR_TAGPREVIEW_PATCH
	if (selmon->previewshow != 0) {
		hidetagpreview(selmon);
	}
	#endif // BAR_TAGPREVIEW_PATCH
	return ClkTagBar;
}

int
hover_tags(Bar *bar, BarArg *a, XMotionEvent *ev)
{
	#if BAR_TAGPREVIEW_PATCH
	int i = 0, x = lrpad / 2;
	int px, py;
	Monitor *m = bar->mon;
	#if VANITYGAPS_PATCH
	int ov = gappov;
	int oh = gappoh;
	#else
	int ov = 0;
	int oh = 0;
	#endif // VANITYGAPS_PATCH

	#if BAR_HIDEVACANTTAGS_PATCH
	Client *c;
	unsigned int occ = 0;
	for (c = bar->mon->clients; c; c = c->next)
		//occ |= c->tags == 255 ? 0 : c->tags;
		occ |= c->tags == TAGMASK ? 0 : c->tags; //renzo correction to git
	#endif // BAR_HIDEVACANTTAGS_PATCH

	do {
		#if BAR_HIDEVACANTTAGS_PATCH
		if (!(occ & 1 << i || bar->mon->tagset[bar->mon->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		
		#if BAR_PANGO_PATCH // 	renzo
		x += TEXTWM(tagicon(bar->mon, i));
		#else
		x += TEXTW(tagicon(bar->mon, i));
		#endif // BAR_PANGO_PATCH
		
	} while (a->x >= x && ++i < NUMTAGS);

	if (i < NUMTAGS) {
		if ((i + 1) != selmon->previewshow && !(selmon->tagset[selmon->seltags] & 1 << i)) {
			if (bar->by > m->my + m->mh / 2) // bottom bar
				py = bar->by - m->mh / scalepreview - oh;
			else // top bar
				py = bar->by + bar->bh + oh;
			px = bar->bx + ev->x - m->mw / scalepreview / 2;
			if (px + m->mw / scalepreview > m->mx + m->mw)
				px = m->wx + m->ww - m->mw / scalepreview - ov;
			else if (px < bar->bx)
				px = m->wx + ov;
			selmon->previewshow = i + 1;
			showtagpreview(i, px, py);
		} else if (selmon->tagset[selmon->seltags] & 1 << i) {
			hidetagpreview(selmon);
		}
	} else if (selmon->previewshow != 0) {
		hidetagpreview(selmon);
	}
	#endif // BAR_TAGPREVIEW_PATCH

	return 1;
}
