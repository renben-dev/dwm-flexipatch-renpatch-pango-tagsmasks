void
set_next_tagicons()
{
	selmon->tagicons_current = (selmon->tagicons_current + 1) % tagicons_count;
	drawbar(selmon);
}
