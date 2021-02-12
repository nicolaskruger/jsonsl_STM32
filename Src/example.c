/*
 * example.c
 *
 *  Created on: Feb 12, 2021
 *      Author: nicolas-kruger
 */
#include "example.h"
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

static int MaxOutputLevel = 20;
static int MaxDescentLevel = 20;
static bool DumpIncremental = false;
static bool DumpProgress = true;
static bool DumpCompletion = true;
static bool DumpStringContents = true;
static bool DumpHashKeys = true;
static bool DumpAll = true;
static bool Silent = true;


static void pad_level(int level) {
    for (; level > 1; level--) {
        putchar(' ');
    }
}
void nest_callback_initial(jsonsl_t jsn,
                        jsonsl_action_t action,
                        struct jsonsl_state_st *state,
                        const char *at)
{

}
int error_callback(jsonsl_t jsn,
                    jsonsl_error_t err,
                    struct jsonsl_state_st *state,
                    char *at)
{
    fprintf(stderr, "Got error at pos %lu: %s\n\r",
            jsn->pos, jsonsl_strerror(err));
    printf("Remaining text: %s\n\r", at);
    abort();
    return 0;
}
void dump_element(struct element_st *root, int level)
{
	char *typestr = "UNKNOWN";
	    if (!root) {
	        return;
	    }
	    if (MaxOutputLevel < level) {
	        return;
	    }
	#define X(t) \
	    if (root->type == TYPE_##t) \
	        typestr = #t;
	    _XTYPE_ALL
	#undef X
    pad_level(level);
    printf("<%s", typestr);

    switch(root->type) {
    case TYPE_STRING:
        dump_string((struct string_st*)root, level+1);
        break;
    case TYPE_LIST:
//        dump_list((struct list_st*)root, level+1);
        break;
    case TYPE_HASH:
//        dump_hash((struct hash_st*)root, level+1);
        break;
    default:
        fprintf(stderr, "Unknown type!\n");
        abort();
        break;
    }
    pad_level(level);
    printf("</%s>\n", typestr);
}

void dump_string(struct string_st *str, int level)
{
    printf(" len=\"%lu\">", strlen(str->data));
    if (DumpStringContents) {
        printf("%s", str->data);
    }
    printf("\n");
}

//void dump_list(struct list_st *list, int level)
//{
//    GList *node;
//    printf(">\n");
//    for (node = list->data; node; node = node->next) {
//        dump_element((struct element_st*)node->data, level);
//    }
//}

//void dump_hash_iterfunc(gpointer key, gpointer value, void *data)
//{
//    int level = *(int*)data;
//    level++;
//    printf("\n");
//    pad_level(level);
//    printf("<KEY len=\"%lu\"", strlen((char*)key+1));
//    if (DumpHashKeys) {
//        printf(" key=\"%s\"", (char*)key+1);
//    }
//    printf("/>\n");
//    dump_element((struct element_st*)value, level+1);
//}

//void dump_hash(struct hash_st *hash, int level)
//{
//    printf(">\n");
//    g_hash_table_foreach(hash->data, dump_hash_iterfunc, &level);
//}
void parser_json(const char* json){
	int fd, status;
	jsonsl_t jsn;
	struct objgraph_st graph;
	char *buf, *bufp;
	size_t nread;
	size_t json_len = strlen(json);

	jsn = jsonsl_new(10);
	jsonsl_enable_all_callbacks(jsn);

	jsn->action_callback = nest_callback_initial;
	jsn->action_callback_PUSH = NULL;
	jsn->action_callback_POP = NULL;
	jsn->error_callback = error_callback;
	jsn->data = &graph;
	jsn->max_callback_level = MaxDescentLevel;

	memset(&graph, 0, sizeof(graph));

	jsonsl_feed(jsn, json, json_len);
	if(DumpCompletion){

	}


}
