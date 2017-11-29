typedef char T;
struct LList {
	T val;
	struct LList *next;
};

struct LList LList_init(char *);
size_t LList_len(struct LList *);
//struct LList *LList_insert(struct LList *);
struct LList *LList_append(struct LList *, T);
struct LList *LList_index(struct LList *, size_t);
#define LList_get_last(llist) (LList_index(llist, LList_len(llist)))

