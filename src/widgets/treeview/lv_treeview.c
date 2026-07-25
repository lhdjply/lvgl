/**
 * @file lv_treeview.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lv_treeview_private.h"

#if LV_USE_TREEVIEW

#include "../../core/lv_obj_class_private.h"

/*********************
 *      DEFINES
 *********************/

#define MY_CLASS      (&lv_treeview_class)
#define MY_CLASS_NODE (&lv_treeview_node_class)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void node_event_cb(const lv_obj_class_t * class_p, lv_event_t * e);
static void node_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void update_node_text(lv_obj_t * node);
static void update_node_visibility(lv_obj_t * node);

/**********************
 *  STATIC VARIABLES
 **********************/

const lv_obj_class_t lv_treeview_class = {
    .width_def = (LV_DPI_DEF * 3) / 2,
    .height_def = LV_DPI_DEF * 2,
    .instance_size = sizeof(lv_treeview_t),
    .base_class = &lv_obj_class,
    .name = "lv_treeview",
};

const lv_obj_class_t lv_treeview_node_class = {
    .event_cb = node_event_cb,
    .destructor_cb = node_destructor,
    .width_def = LV_PCT(100),
    .height_def = 40,
    .instance_size = sizeof(lv_treeview_node_t),
    .base_class = &lv_obj_class,
    .name = "lv_treeview_node",
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_treeview_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);

    lv_treeview_set_default_expanded(obj, true);

    return obj;
}

lv_obj_t * lv_treeview_add_node(lv_obj_t * parent_node, const char * text)
{
    LV_LOG_INFO("begin");
    lv_treeview_t * t = NULL;
    lv_treeview_node_t * parent = NULL;

    if(lv_obj_check_type(parent_node, MY_CLASS)) {
        t = (lv_treeview_t *)parent_node;
    }
    else {
        parent = (lv_treeview_node_t *)parent_node;
        lv_obj_t * tree_obj = parent_node;
        while(tree_obj && !lv_obj_check_type(tree_obj, MY_CLASS)) {
            tree_obj = lv_obj_get_parent(tree_obj);
        }
        if(!tree_obj) return NULL;
        t = (lv_treeview_t *)tree_obj;
    }

    lv_obj_t * node = lv_obj_class_create_obj(MY_CLASS_NODE, (lv_obj_t *)t);
    lv_obj_class_init_obj(node);

    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    n->parent = parent;
    n->children_container = NULL;
    n->expanded = false;
    n->has_children = false;

    lv_obj_set_flex_flow(node, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(node, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    if(parent) {
        parent->has_children = true;
        update_node_text((lv_obj_t *)parent);
        n->depth = parent->depth + 1;
    }
    else {
        n->depth = 0;
        t->root_node = node;
    }

    lv_obj_set_style_pad_left(node, n->depth * 24, 0);

    n->text = lv_strdup(text);

    n->label = lv_label_create(node);
    lv_label_set_text(n->label, "");

    update_node_text(node);
    update_node_visibility(node);

    if(t->default_expanded) {
        lv_treeview_node_expand(node);
    }

    return node;
}

void lv_treeview_node_set_text(lv_obj_t * node, const char * text)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    if(n->text) lv_free(n->text);
    n->text = lv_strdup(text);
    update_node_text(node);
}

void lv_treeview_node_expand(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    n->expanded = true;
    update_node_text(node);

    lv_obj_t * tree = node;
    while(tree && !lv_obj_check_type(tree, MY_CLASS)) {
        tree = lv_obj_get_parent(tree);
    }

    if(tree) {
        uint32_t child_count = lv_obj_get_child_count(tree);
        for(uint32_t i = 0; i < child_count; i++) {
            lv_obj_t * child = lv_obj_get_child(tree, i);
            if(lv_obj_check_type(child, MY_CLASS_NODE)) {
                update_node_visibility(child);
            }
        }
        lv_obj_update_layout(tree);
        lv_obj_invalidate(tree);
    }
}

void lv_treeview_node_collapse(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    n->expanded = false;
    update_node_text(node);

    lv_obj_t * tree = node;
    while(tree && !lv_obj_check_type(tree, MY_CLASS)) {
        tree = lv_obj_get_parent(tree);
    }

    if(tree) {
        uint32_t child_count = lv_obj_get_child_count(tree);
        for(uint32_t i = 0; i < child_count; i++) {
            lv_obj_t * child = lv_obj_get_child(tree, i);
            if(lv_obj_check_type(child, MY_CLASS_NODE)) {
                update_node_visibility(child);
            }
        }
        lv_obj_update_layout(tree);
        lv_obj_invalidate(tree);
    }
}

void lv_treeview_node_toggle(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    if(!n->has_children) return;

    if(n->expanded) {
        lv_treeview_node_collapse(node);
    }
    else {
        lv_treeview_node_expand(node);
    }
}

void lv_treeview_set_default_expanded(lv_obj_t * tree, bool expanded)
{
    lv_treeview_t * t = (lv_treeview_t *)tree;
    t->default_expanded = expanded;
}

const char * lv_treeview_node_get_text(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    return n->text;
}

bool lv_treeview_node_is_expanded(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    return n->expanded;
}

lv_obj_t * lv_treeview_node_get_parent(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    if(n->parent) {
        return (lv_obj_t *)n->parent;
    }
    return NULL;
}

uint32_t lv_treeview_node_get_child_count(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    if(!n->has_children) return 0;

    lv_obj_t * tree = node;
    while(tree && !lv_obj_check_type(tree, MY_CLASS)) {
        tree = lv_obj_get_parent(tree);
    }
    if(!tree) return 0;

    uint32_t count = 0;
    uint32_t child_count = lv_obj_get_child_count(tree);
    for(uint32_t i = 0; i < child_count; i++) {
        lv_obj_t * child = lv_obj_get_child(tree, i);
        if(lv_obj_check_type(child, MY_CLASS_NODE)) {
            lv_treeview_node_t * c = (lv_treeview_node_t *)child;
            if(c->parent == n) {
                count++;
            }
        }
    }
    return count;
}

lv_obj_t * lv_treeview_node_get_child(lv_obj_t * node, uint32_t idx)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    if(!n->has_children) return NULL;

    lv_obj_t * tree = node;
    while(tree && !lv_obj_check_type(tree, MY_CLASS)) {
        tree = lv_obj_get_parent(tree);
    }
    if(!tree) return NULL;

    uint32_t count = 0;
    uint32_t child_count = lv_obj_get_child_count(tree);
    for(uint32_t i = 0; i < child_count; i++) {
        lv_obj_t * child = lv_obj_get_child(tree, i);
        if(lv_obj_check_type(child, MY_CLASS_NODE)) {
            lv_treeview_node_t * c = (lv_treeview_node_t *)child;
            if(c->parent == n) {
                if(count == idx) return child;
                count++;
            }
        }
    }
    return NULL;
}

bool lv_treeview_get_default_expanded(lv_obj_t * tree)
{
    lv_treeview_t * t = (lv_treeview_t *)tree;
    return t->default_expanded;
}

void lv_treeview_node_remove(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;

    if(n->parent) {
        lv_treeview_node_t * parent = n->parent;
        uint32_t child_count = lv_treeview_node_get_child_count((lv_obj_t *)parent);
        if(child_count <= 1) {
            parent->has_children = false;
            update_node_text((lv_obj_t *)parent);
        }
    }
    lv_obj_delete(node);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void node_event_cb(const lv_obj_class_t * class_p, lv_event_t * e)
{
    LV_UNUSED(class_p);
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        lv_treeview_node_toggle(obj);
    }
}

static void node_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    lv_treeview_node_t * n = (lv_treeview_node_t *)obj;
    if(n->text) {
        lv_free(n->text);
        n->text = NULL;
    }
}

static void update_node_text(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;
    if(n->has_children) {
        if(n->expanded) {
            lv_label_set_text_fmt(n->label, LV_SYMBOL_DOWN " %s", n->text);
        }
        else {
            lv_label_set_text_fmt(n->label, LV_SYMBOL_RIGHT " %s", n->text);
        }
    }
    else {
        lv_label_set_text_fmt(n->label, "  %s", n->text);
    }
}

static void update_node_visibility(lv_obj_t * node)
{
    lv_treeview_node_t * n = (lv_treeview_node_t *)node;

    lv_treeview_node_t * parent = n->parent;
    bool visible = true;
    while(parent) {
        if(!parent->expanded) {
            visible = false;
            break;
        }
        parent = parent->parent;
    }

    lv_obj_set_hidden(node, !visible);
}

#endif /*LV_USE_TREEVIEW*/
