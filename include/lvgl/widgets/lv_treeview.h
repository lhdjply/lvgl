/**
 * @file lv_treeview.h
 *
 */

#ifndef LV_TREEVIEW_H
#define LV_TREEVIEW_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../core/lv_obj.h"

#if LV_USE_TREEVIEW

#if LV_USE_LABEL == 0
#error "lv_treeview: lv_label is required. Enable it in lv_conf.h (LV_USE_LABEL 1)"
#endif

#include "lv_label.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_treeview_class;
LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_treeview_node_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a treeview object
 * @param parent      pointer to an object, it will be the parent of the new treeview
 * @return            pointer to the created treeview
 */
lv_obj_t * lv_treeview_create(lv_obj_t * parent);

/**
 * Add a node to the treeview. If parent_node is the treeview itself, a root node is created.
 * @param parent_node pointer to the parent (treeview or node)
 * @param text        text of the new node
 * @return            pointer to the created node
 */
lv_obj_t * lv_treeview_add_node(lv_obj_t * parent_node, const char * text);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the text of a treeview node
 * @param node        pointer to a node
 * @param text        new text
 */
void lv_treeview_node_set_text(lv_obj_t * node, const char * text);

/**
 * Expand a treeview node to show its children
 * @param node        pointer to a node
 */
void lv_treeview_node_expand(lv_obj_t * node);

/**
 * Collapse a treeview node to hide its children
 * @param node        pointer to a node
 */
void lv_treeview_node_collapse(lv_obj_t * node);

/**
 * Toggle expand/collapse state of a treeview node
 * @param node        pointer to a node
 */
void lv_treeview_node_toggle(lv_obj_t * node);

/**
 * Set the default expanded state for newly added nodes
 * @param tree        pointer to a treeview
 * @param expanded    default expanded state
 */
void lv_treeview_set_default_expanded(lv_obj_t * tree, bool expanded);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the text of a treeview node
 * @param node        pointer to a node
 * @return            text of the node
 */
const char * lv_treeview_node_get_text(lv_obj_t * node);

/**
 * Check if a treeview node is expanded
 * @param node        pointer to a node
 * @return            true if expanded, false otherwise
 */
bool lv_treeview_node_is_expanded(lv_obj_t * node);

/**
 * Get the parent node of a treeview node
 * @param node        pointer to a node
 * @return            pointer to the parent node, or NULL for root
 */
lv_obj_t * lv_treeview_node_get_parent(lv_obj_t * node);

/**
 * Get the number of children of a treeview node
 * @param node        pointer to a node
 * @return            number of children
 */
uint32_t lv_treeview_node_get_child_count(lv_obj_t * node);

/**
 * Get a child of a treeview node by index
 * @param node        pointer to a node
 * @param idx         index of the child
 * @return            pointer to the child node, or NULL if not found
 */
lv_obj_t * lv_treeview_node_get_child(lv_obj_t * node, uint32_t idx);

/**
 * Get the default expanded state of a treeview
 * @param tree        pointer to a treeview
 * @return            default expanded state
 */
bool lv_treeview_get_default_expanded(lv_obj_t * tree);

/*=====================
 * Other functions
 *====================*/

/**
 * Remove a node from the treeview (and all its children)
 * @param node        pointer to a node
 */
void lv_treeview_node_remove(lv_obj_t * node);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_TREEVIEW*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_TREEVIEW_H*/
