/*
 * example.h
 *
 *  Created on: Feb 12, 2021
 *      Author: nicolas-kruger
 */
#include "jsonsl.h"

#ifndef INC_EXAMPLE_H_
#define INC_EXAMPLE_H_

#define _XTYPE_ALL \
    X(LIST) \
    X(HASH) \
    X(BOOLEAN) \
    X(INTEGER) \
    X(STRING)

typedef enum {
#define X(t) \
    TYPE_ ##t ,
    _XTYPE_ALL
    TYPE_UNKNOWN
#undef X
} jtype_t;

#define ST_ELEMENT_BASE(ptype) \
    jtype_t type; \
    struct element_st *parent; \
    ptype *data;

struct element_st { ST_ELEMENT_BASE(void) };
struct string_st {
    ST_ELEMENT_BASE(const char)
};

struct objgraph_st {
    struct element_st *root;
};

void parser_json(const char* json);

#endif /* INC_EXAMPLE_H_ */
