typedef struct {
    size_t length;
    size_t used;
    char * data;
} strbuf_t;

int al_init(strbuf_t *, size_t);
void al_destroy(strbuf_t *);
int al_append(strbuf_t *, char);
int al_remove(strbuf_t *, char *);
