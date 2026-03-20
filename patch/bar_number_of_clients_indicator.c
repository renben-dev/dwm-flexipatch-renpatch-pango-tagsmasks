static const char *__superscripts__[] = {
    "⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹", "⁺"
};
static const char *__subscripts__[] = {
    "₀", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", "₉", "₊"
};

int
drawindicator_num_clients(Monitor *m, Client *c, unsigned int occ, int x, int y, int h, unsigned int lpad, unsigned int rpad, unsigned int tag, int invert, int type)
{  
	int i, w;
    int num_clients = 0;
    char *symbol;
	if (!(occ & 1 << tag) || type == INDICATOR_NUMBER_OF_CLIENTS_NONE)
		return 0;
    
    for (c = m->clients; c && num_clients <= 10; c = c->next) {
        if (c->tags & (1 << tag)) {
            num_clients++;
        }
    }

    if(!num_clients)
        return 0;

    if (type == INDICATOR_NUMBER_OF_CLIENTS_TOP_RIGHT || type == INDICATOR_NUMBER_OF_CLIENTS_TOP_LEFT)
        symbol = __subscripts__[num_clients];
    else
        symbol = __subscripts__[num_clients];
    
    w = TEXTW(symbol) - lrpad + lpad + rpad;    
	drw_text(drw, x, y, w, h, lpad, symbol, invert, False);
    
    return w;
}