static void tagtoleft(const Arg *arg);
static void tagtoright(const Arg *arg);
static void viewtoleft(const Arg *arg);
static void viewtoright(const Arg *arg);
static void tagandviewtoleft(const Arg *arg);
static void tagandviewtoright(const Arg *arg);
#if FOCUSADJACENTTAG_PATCH && FOCUSADJACENTTAG_CIRCULAR_RENBEN_PATCH && FOCUSADJACENTTAG_ACTIVE_CIRCULAR_RENBEN_PATCH
static void viewtoleft_active(const Arg *arg);
static void viewtoright_active(const Arg *arg);
#endif