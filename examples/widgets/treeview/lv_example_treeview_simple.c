#include "../../lv_examples.h"
#if LV_USE_TREEVIEW && LV_BUILD_EXAMPLES

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target_obj(e);
    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked: %s", lv_treeview_node_get_text(obj));
    }
}

/**
 * @title Simple treeview
 * @brief A 280x300 treeview with a root, two folders and sample items using symbols for expand/collapse.
 *
 * `lv_treeview_create` builds a centered treeview. `lv_treeview_add_node` adds
 * a root, folders and items. By default all nodes start expanded. A single
 * `LV_EVENT_CLICKED` handler logs the clicked node's text via
 * `lv_treeview_node_get_text`.
 */
void lv_example_treeview_simple(void)
{
    lv_obj_t * tree = lv_treeview_create(lv_screen_active());
    lv_obj_set_size(tree, 280, 300);
    lv_obj_center(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    lv_obj_add_event_cb(root, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * folder1 = lv_treeview_add_node(root, "Folder 1");
    lv_obj_add_event_cb(folder1, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * item1_1 = lv_treeview_add_node(folder1, "Item 1-1");
    lv_obj_add_event_cb(item1_1, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * item1_2 = lv_treeview_add_node(folder1, "Item 1-2");
    lv_obj_add_event_cb(item1_2, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * folder2 = lv_treeview_add_node(root, "Folder 2");
    lv_obj_add_event_cb(folder2, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * item2_1 = lv_treeview_add_node(folder2, "Item 2-1");
    lv_obj_add_event_cb(item2_1, event_handler, LV_EVENT_CLICKED, NULL);

    lv_treeview_set_default_expanded(tree, false);

    lv_obj_t * folder3 = lv_treeview_add_node(root, "Folder 3 (collapsed)");
    lv_obj_add_event_cb(folder3, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * item3_1 = lv_treeview_add_node(folder3, "Item 3-1");
    lv_obj_add_event_cb(item3_1, event_handler, LV_EVENT_CLICKED, NULL);

    lv_treeview_set_default_expanded(tree, true);
}

#endif
