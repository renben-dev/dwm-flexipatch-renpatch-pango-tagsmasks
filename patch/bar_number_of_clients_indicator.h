enum {
    INDICATOR_NUMBER_OF_CLIENTS_NONE,
	INDICATOR_NUMBER_OF_CLIENTS_TOP_LEFT,
	INDICATOR_NUMBER_OF_CLIENTS_TOP_RIGHT,
	INDICATOR_NUMBER_OF_CLIENTS_BOTTOM_LEFT,
	INDICATOR_NUMBER_OF_CLIENTS_BOTTOM_RIGHT
};

int
drawindicator_num_clients(Monitor *m, Client *c, unsigned int occ, int x, int y, int h, unsigned int lpad, unsigned int rpad, unsigned int tag, int invert, int type);