

#if BIDI_PATCH
int
drw_text_overlay(Drw *drw, int x, int y, unsigned int w, unsigned int h,
                 unsigned int lpad, const char *text, int invert, Bool markup)
#else
int
drw_text_overlay(Drw *drw, int x, int y, unsigned int w, unsigned int h,
                 unsigned int lpad, const char *text, int invert, Bool markup)
#endif // BIDI_PATCH
{
#if BAR_PANGO_PATCH
	char buf[1024];
	int i, ty, th;
	unsigned int ew, eh;
	XftDraw *d = NULL;
	size_t len;
	int render = x || y || w || h;

	if (!drw || !text || !drw->fonts || (render && !drw->scheme))
		return 0;

	if (!render) {
		w = ~w;
	} else {
		#if BAR_ALPHA_PATCH
		d = XftDrawCreate(drw->dpy, drw->drawable, drw->visual, drw->cmap);
		#else
		d = XftDrawCreate(drw->dpy, drw->drawable,
		                  DefaultVisual(drw->dpy, drw->screen),
		                  DefaultColormap(drw->dpy, drw->screen));
		#endif // BAR_ALPHA_PATCH
		x += lpad;
		w -= lpad;
	}

	len = strlen(text);

	if (len) {
		drw_font_getexts(drw->fonts, text, len, &ew, &eh, markup);
		th = eh;

		// shorten text if necessary
		for (len = MIN(len, sizeof(buf) - 1); len && ew > w; len--) {
			drw_font_getexts(drw->fonts, text, len, &ew, &eh, markup);
			if (eh > th)
				th = eh;
		}

		if (len) {
			memcpy(buf, text, len);
			buf[len] = '\0';
			if (len < strlen(text))
				for (i = len; i && i > len - 3; buf[--i] = '.');

			if (render) {
				ty = y + (h - th) / 2;
				if (markup)
					pango_layout_set_markup(drw->fonts->layout, buf, len);
				else
					pango_layout_set_text(drw->fonts->layout, buf, len);

				pango_xft_render_layout(d, &drw->scheme[invert ? ColBg : ColFg],
				                        drw->fonts->layout,
				                        x * PANGO_SCALE, ty * PANGO_SCALE);

				if (markup)
					pango_layout_set_attributes(drw->fonts->layout, NULL);
			}
			x += ew;
			w -= ew;
		}
	}
	if (d)
		XftDrawDestroy(d);

	return x + (render ? w : 0);
#else // fallback when Pango patch is not present

	int ty;
	XftDraw *d = NULL;
	Fnt *usedfont;
	unsigned int ew;

	if (!drw || !text || !drw->fonts || (x || y || w || h) && !drw->scheme)
		return 0;

	usedfont = drw->fonts;
	#if BAR_ALPHA_PATCH
	d = XftDrawCreate(drw->dpy, drw->drawable, drw->visual, drw->cmap);
	#else
	d = XftDrawCreate(drw->dpy, drw->drawable,
	                  DefaultVisual(drw->dpy, drw->screen),
	                  DefaultColormap(drw->dpy, drw->screen));
	#endif // BAR_ALPHA_PATCH

	drw_font_getexts(usedfont, text, strlen(text), &ew, NULL);
	ty = y + (h - usedfont->h) / 2 + usedfont->xfont->ascent;

	XftDrawStringUtf8(d, &drw->scheme[invert ? ColBg : ColFg],
	                  usedfont->xfont, x + lpad, ty,
	                  (XftChar8 *)text, strlen(text));

	if (d)
		XftDrawDestroy(d);

	return x + lpad + ew;
#endif // BAR_PANGO_PATCH
}


#if BIDI_PATCH
int
drw_text_overlay(Drw *drw, int x, int y, unsigned int w, unsigned int h,
                 unsigned int lpad, const char *text, int invert, Bool markup,
                 Fnt *font_to_use)
#else
int
drw_text_overlay(Drw *drw, int x, int y, unsigned int w, unsigned int h,
                 unsigned int lpad, const char *text, int invert, Bool markup,
                 Fnt *font_to_use)
#endif // BIDI_PATCH
{
#if BAR_PANGO_PATCH
	char buf[1024];
	int i, ty, th;
	unsigned int ew, eh;
	XftDraw *d = NULL;
	size_t len;
	int render = x || y || w || h;
	Fnt *fnt = font_to_use ? font_to_use : drw->fonts;

	if (!drw || !text || !fnt || (render && !drw->scheme))
		return 0;

	if (!render) {
		w = ~w;
	} else {
		#if BAR_ALPHA_PATCH
		d = XftDrawCreate(drw->dpy, drw->drawable, drw->visual, drw->cmap);
		#else
		d = XftDrawCreate(drw->dpy, drw->drawable,
		                  DefaultVisual(drw->dpy, drw->screen),
		                  DefaultColormap(drw->dpy, drw->screen));
		#endif
		x += lpad;
		w -= lpad;
	}

	len = strlen(text);

	if (len) {
		drw_font_getexts(fnt, text, len, &ew, &eh, markup);
		th = eh;

		// shorten text if necessary
		for (len = MIN(len, sizeof(buf) - 1); len && ew > w; len--) {
			drw_font_getexts(fnt, text, len, &ew, &eh, markup);
			if (eh > th)
				th = eh;
		}

		if (len) {
			memcpy(buf, text, len);
			buf[len] = '\0';
			if (len < strlen(text))
				for (i = len; i && i > len - 3; buf[--i] = '.');

			if (render) {
				ty = y + (h - th) / 2;
				if (markup)
					pango_layout_set_markup(fnt->layout, buf, len);
				else
					pango_layout_set_text(fnt->layout, buf, len);

				pango_xft_render_layout(d, &drw->scheme[invert ? ColBg : ColFg],
				                        fnt->layout,
				                        x * PANGO_SCALE, ty * PANGO_SCALE);

				if (markup)
					pango_layout_set_attributes(fnt->layout, NULL);
			}
			x += ew;
			w -= ew;
		}
	}
	if (d)
		XftDrawDestroy(d);

	return x + (render ? w : 0);
#else // no BAR_PANGO_PATCH

	int ty;
	XftDraw *d = NULL;
	Fnt *fnt = font_to_use ? font_to_use : drw->fonts;
	unsigned int ew;

	if (!drw || !text || !fnt || (x || y || w || h) && !drw->scheme)
		return 0;

	#if BAR_ALPHA_PATCH
	d = XftDrawCreate(drw->dpy, drw->drawable, drw->visual, drw->cmap);
	#else
	d = XftDrawCreate(drw->dpy, drw->drawable,
	                  DefaultVisual(drw->dpy, drw->screen),
	                  DefaultColormap(drw->dpy, drw->screen));
	#endif

	drw_font_getexts(fnt, text, strlen(text), &ew, NULL);
	ty = y + (h - fnt->h) / 2 + fnt->xfont->ascent;

	XftDrawStringUtf8(d, &drw->scheme[invert ? ColBg : ColFg],
	                  fnt->xfont, x + lpad, ty,
	                  (XftChar8 *)text, strlen(text));

	if (d)
		XftDrawDestroy(d);

	return x + lpad + ew;
#endif
}



✅ Step-by-Step Implementation
🧩 1. config.h — Add an overlay font string
Add a single font string for your overlay font, similar to fonts[]:

c
Copy
Edit
static const char *overlayfont = "JetBrainsMono Nerd Font Mono:size=14:style=Bold";
✔️ You can pick any font and size here. This keeps it flexible and in line with how fonts[] works.

💡 2. Declare bar_overlay_font for external use
Still in config.h, just declare it as an extern pointer:

c
Copy
Edit
extern Fnt *bar_overlay_font;
🧱 3. In your drw.c (or dwm.c), define and initialize the font
At the top of your .c file:

c
Copy
Edit
Fnt *bar_overlay_font = NULL;
Then inside your setup() function or wherever you call drw_load_fonts(...), add this:

c
Copy
Edit
bar_overlay_font = drw_font_create(drw, overlayfont);
if (!bar_overlay_font) {
    die("Failed to load overlay font: %s\n", overlayfont);
}
✔️ This uses your configured font from config.h.

🧼 4. Clean up on exit (cleanup())
At shutdown, add this:

c
Copy
Edit
if (bar_overlay_font)
    drw_font_free(bar_overlay_font);
🧪 5. Use it in your drw_text_overlay() call
Pass bar_overlay_font as the font_to_use argument:

c
Copy
Edit
drw_text_overlay(drw, x, y, w, h, lpad, "Overlay text", 0, 0, bar_overlay_font);
