#if BAR_PANGO_PATCH //renzo
const char *
#else
char *
#endif // BAR_PANGO_PATCH
tagicon(Monitor *m, int tag)
{
#if BAR_ALTTAGSDECORATION_PATCH
	Client *c;
#endif // BAR_ALTTAGSDECORATION_PATCH
	int tagindex = tag + NUMTAGS * m->num;
	if (tagindex >= LENGTH(tagicons[DEFAULT_TAGS]))
		tagindex = tagindex % LENGTH(tagicons[DEFAULT_TAGS]);
#if BAR_ALTTAGSDECORATION_PATCH
	for (c = m->clients; c && (!(c->tags & 1 << tag) || HIDDEN(c)); c = c->next);
	if (c)
		return tagicons[ALT_TAGS_DECORATION][tagindex];
#endif // BAR_ALTTAGSDECORATION_PATCH

#if BAR_TAG_MULTI_ICONS_RENBEN_PATCH
	return tagicons[m->tagicons_current][tagindex];
// BAR_TAG_MULTI_ICONS_RENBEN_PATCH 1
#elif BAR_ALTERNATIVE_TAGS_PATCH
	if (m->alttag)
	return tagicons[ALTERNATIVE_TAGS][tagindex];
// BAR_ALTERNATIVE_TAGS_PATCH
#else
	return tagicons[DEFAULT_TAGS][tagindex];
#endif
}

