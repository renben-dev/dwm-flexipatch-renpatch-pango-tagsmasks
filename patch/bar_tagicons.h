enum {
	DEFAULT_TAGS,
	ALTERNATIVE_TAGS,
	ALT_TAGS_DECORATION,
};

static 
#if BAR_PANGO_PATCH //renzo
const char *
#else
char *
#endif //BAR_PANGO_PATCH
tagicon(Monitor *m, int tag);

