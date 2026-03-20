void
tagtoleft(const Arg *arg)
{
	unsigned int MASK = (1 << NUMTAGS) - 1;
#if FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
	if (selmon->sel != NULL
		&& __builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1) {
		unsigned int current_tag = selmon->tagset[selmon->seltags] & MASK;
		unsigned int next_tag = current_tag >> 1;

		if (next_tag == 0)
    		next_tag = (1 << (NUMTAGS - 1));

		// retain other tags, just replace current view tag with next
		selmon->sel->tags &= ~current_tag;  //remove current tag
		selmon->sel->tags |= next_tag;	// add new tag

		arrange(selmon);
		focus(NULL);
	}
#else
	if (selmon->sel != NULL
	&& __builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1
	&& selmon->tagset[selmon->seltags] > 1) {
		selmon->sel->tags >>= 1;
		arrange(selmon);
		focus(NULL);
	}
#endif //FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
}

void
tagtoright(const Arg *arg)
{
	unsigned int MASK = (1 << NUMTAGS) - 1;
#if FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
	if (selmon->sel != NULL
    && __builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1) {
		unsigned int current_tag = selmon->tagset[selmon->seltags] & MASK;
		unsigned int next_tag = current_tag << 1;

		if (next_tag > (1 << (NUMTAGS - 1)))
			next_tag = 1;

		// retain other tags, just replace current view tag with next
		selmon->sel->tags &= ~current_tag;  //remove current tag
		selmon->sel->tags |= next_tag;	// add new tag

		arrange(selmon);
		focus(NULL);
	}
#else
	if (selmon->sel != NULL
	&& __builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1
	&& selmon->tagset[selmon->seltags] & (MASK >> 1)) {
		selmon->sel->tags <<= 1;
		arrange(selmon);
		focus(NULL);
	}
#endif //FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
}

void
viewtoleft(const Arg *arg)
{
	unsigned int MASK = (1 << NUMTAGS) - 1;
#if FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
	if (__builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1) {
		if (selmon->tagset[selmon->seltags] & 1){
			view(&((Arg) { .ui = (1 << (NUMTAGS - 1)) }));	
		}
		else {
			view(&((Arg) { .ui = selmon->tagset[selmon->seltags] >> 1 }));
		}
  	}
#else
	if (__builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1
	&& selmon->tagset[selmon->seltags] > 1) {
		view(&((Arg) { .ui = selmon->tagset[selmon->seltags] >> 1 }));
	}
#endif //FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
}

void
viewtoright(const Arg *arg)
{
	unsigned int MASK = (1 << NUMTAGS) - 1;
#if FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
	if (__builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1) {
		if (selmon->tagset[selmon->seltags] & (1 << (NUMTAGS -1))){
			view(&((Arg) { .ui = 1 }));	
		}
		else {
			view(&((Arg) { .ui = selmon->tagset[selmon->seltags] << 1 }));
		}
  	}
	
#else
	if (__builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1
	&& selmon->tagset[selmon->seltags] & (MASK >> 1)) {
		view(&((Arg) { .ui = selmon->tagset[selmon->seltags] << 1 }));
	}
#endif //FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
}

void
tagandviewtoleft(const Arg *arg)
{
	unsigned int MASK = (1 << NUMTAGS) - 1;
#if FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
	if (selmon->sel != NULL
		&& __builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1) {
		unsigned int current_tag = selmon->tagset[selmon->seltags] & MASK;
		unsigned int next_tag = current_tag >> 1;

		if (next_tag == 0)
    		next_tag = (1 << (NUMTAGS - 1));

		// retain other tags, just replace current view tag with next
		selmon->sel->tags &= ~current_tag;  //remove current tag
		selmon->sel->tags |= next_tag;	// add new tag

		view(&((Arg) { .ui = next_tag }));
	}
#else
	if (selmon->sel != NULL
	&& __builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1
	&& selmon->tagset[selmon->seltags] > 1) {
		selmon->sel->tags >>= 1;
		view(&((Arg) { .ui = selmon->tagset[selmon->seltags] >> 1 }));
	}
#endif //FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
}

void
tagandviewtoright(const Arg *arg)
{
	unsigned int MASK = (1 << NUMTAGS) - 1;
#if FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
	if (selmon->sel != NULL
    && __builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1) {
		unsigned int current_tag = selmon->tagset[selmon->seltags] & MASK;
		unsigned int next_tag = current_tag << 1;

		if (next_tag > (1 << (NUMTAGS - 1)))
			next_tag = 1;

		// retain other tags, just replace current view tag with next
		selmon->sel->tags &= ~current_tag;  //remove current tag
		selmon->sel->tags |= next_tag;	// add new tag

		view(&((Arg) { .ui = next_tag }));
	}
#else
	if (selmon->sel != NULL
	&& __builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1
	&& selmon->tagset[selmon->seltags] & (MASK >> 1)) {
		selmon->sel->tags <<= 1;
		view(&((Arg) { .ui = selmon->tagset[selmon->seltags] << 1 }));
	}
#endif //FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH
}

#if FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH && FOCUSADJACENTTAG_ACTIVE_CIRCULAR_RENBEN_PATCH
int is_tag_occupied(Monitor *m, unsigned int tagmask) {
    Client *c;
    for (c = m->clients; c; c = c->next) {
        if (c->tags & tagmask)
            return 1;
    }
    return 0;
}

void
viewtoleft_active(const Arg *arg)
{
    unsigned int MASK = (1 << NUMTAGS) - 1;
    
    // Move to the left tag, wrapping around
	if (__builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1) {
		unsigned int cur_tag = selmon->tagset[selmon->seltags] & MASK;
    	unsigned int next_tag = (cur_tag >> 1) | ((cur_tag & 1) << (NUMTAGS - 1)); // rotate right by 1 bit

		while (next_tag != cur_tag){
			// Check if tag is occupied (clients on that tag)
			if (next_tag != 0 && is_tag_occupied(selmon, next_tag)) {
				view(&((Arg){ .ui = next_tag }));
				break;
			}
			next_tag = (next_tag >> 1) | ((next_tag & 1) << (NUMTAGS - 1)); // rotate right by 1 bit
		}
	}
}

void
viewtoright_active(const Arg *arg)
{
    unsigned int MASK = (1 << NUMTAGS) - 1;
    
    // Move to the right tag, wrapping around
	if (__builtin_popcount(selmon->tagset[selmon->seltags] & MASK) == 1) {
		unsigned int cur_tag = selmon->tagset[selmon->seltags] & MASK;
    	unsigned int next_tag = (((cur_tag << 1) & MASK) | (cur_tag >> (NUMTAGS - 1))); // rotate left by 1 bit

		while (next_tag != cur_tag){
			// Check if tag is occupied (clients on that tag)
			if (next_tag != 0 && is_tag_occupied(selmon, next_tag)) {
				view(&((Arg){ .ui = next_tag }));
				break;
			}
			next_tag = (((next_tag << 1) & MASK) | (next_tag >> (NUMTAGS - 1))); // rotate left by 1 bit
		}
	}
}
#endif // FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH and FOCUSADJACENTTAG_ACTIVE_CIRCULAR_RENBEN_PATCH
