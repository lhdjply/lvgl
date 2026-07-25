/**
 * @file lv_treeview_private.h
 *
 */

#ifndef LV_TREEVIEW_PRIVATE_H
#define LV_TREEVIEW_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../core/lv_obj_private.h"
#include "../../lvgl_public.h"

#if LV_USE_TREEVIEW

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

struct _lv_treeview_t {
    lv_obj_t obj;
    lv_obj_t * root_node;
    uint8_t default_expanded : 1;
};

struct _lv_treeview_node_t {
    lv_obj_t obj;
    lv_obj_t * label;
    lv_obj_t * children_container;
    lv_treeview_node_t * parent;
    char * text;
    uint8_t expanded : 1;
    uint8_t has_children : 1;
    uint8_t depth;
};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_TREEVIEW */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_TREEVIEW_PRIVATE_H*/
