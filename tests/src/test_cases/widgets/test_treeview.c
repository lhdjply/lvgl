#if LV_BUILD_TEST
#include "../lvgl.h"
#include "../../lvgl_private.h"

#include "unity/unity.h"

static lv_obj_t * active_screen = NULL;
static lv_obj_t * tree = NULL;

void setUp(void)
{
    active_screen = lv_screen_active();
}

void tearDown(void)
{
    lv_obj_clean(active_screen);
}

/* Test creating a treeview and adding nodes */
void test_treeview_create_and_add_nodes(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_STRING("Root", lv_treeview_node_get_text(root));

    lv_obj_t * child = lv_treeview_add_node(root, "Child");
    TEST_ASSERT_NOT_NULL(child);
    TEST_ASSERT_EQUAL_STRING("Child", lv_treeview_node_get_text(child));

    lv_obj_t * grandchild = lv_treeview_add_node(child, "Grandchild");
    TEST_ASSERT_NOT_NULL(grandchild);
    TEST_ASSERT_EQUAL_STRING("Grandchild", lv_treeview_node_get_text(grandchild));
}

/* Test node parent relationship */
void test_treeview_node_parent(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    lv_obj_t * child = lv_treeview_add_node(root, "Child");

    /* Root has no parent */
    TEST_ASSERT_NULL(lv_treeview_node_get_parent(root));

    /* Child's parent is root */
    lv_obj_t * parent = lv_treeview_node_get_parent(child);
    TEST_ASSERT_NOT_NULL(parent);
    TEST_ASSERT_EQUAL_STRING("Root", lv_treeview_node_get_text(parent));
}

/* Test child count */
void test_treeview_node_child_count(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");

    TEST_ASSERT_EQUAL(0, lv_treeview_node_get_child_count(root));

    lv_treeview_add_node(root, "Child 1");
    TEST_ASSERT_EQUAL(1, lv_treeview_node_get_child_count(root));

    lv_treeview_add_node(root, "Child 2");
    lv_treeview_add_node(root, "Child 3");
    TEST_ASSERT_EQUAL(3, lv_treeview_node_get_child_count(root));
}

/* Test getting child by index */
void test_treeview_node_get_child(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    lv_obj_t * c1 = lv_treeview_add_node(root, "Child 1");
    lv_obj_t * c2 = lv_treeview_add_node(root, "Child 2");
    lv_obj_t * c3 = lv_treeview_add_node(root, "Child 3");

    TEST_ASSERT_EQUAL_PTR(c1, lv_treeview_node_get_child(root, 0));
    TEST_ASSERT_EQUAL_PTR(c2, lv_treeview_node_get_child(root, 1));
    TEST_ASSERT_EQUAL_PTR(c3, lv_treeview_node_get_child(root, 2));
    TEST_ASSERT_NULL(lv_treeview_node_get_child(root, 99));
}

/* Test expand / collapse state */
void test_treeview_expand_collapse(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    lv_obj_t * child = lv_treeview_add_node(root, "Child");

    /* Default is expanded */
    TEST_ASSERT_TRUE(lv_treeview_node_is_expanded(root));
    TEST_ASSERT_TRUE(lv_treeview_node_is_expanded(child));

    /* Collapse root */
    lv_treeview_node_collapse(root);
    TEST_ASSERT_FALSE(lv_treeview_node_is_expanded(root));

    /* Expand root */
    lv_treeview_node_expand(root);
    TEST_ASSERT_TRUE(lv_treeview_node_is_expanded(root));

    /* Toggle */
    lv_treeview_node_toggle(root);
    TEST_ASSERT_FALSE(lv_treeview_node_is_expanded(root));
    lv_treeview_node_toggle(root);
    TEST_ASSERT_TRUE(lv_treeview_node_is_expanded(root));
}

/* Test default expanded state */
void test_treeview_default_expanded(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    /* Default is true */
    TEST_ASSERT_TRUE(lv_treeview_get_default_expanded(tree));

    /* Set to false */
    lv_treeview_set_default_expanded(tree, false);
    TEST_ASSERT_FALSE(lv_treeview_get_default_expanded(tree));

    /* New nodes should be collapsed */
    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    TEST_ASSERT_FALSE(lv_treeview_node_is_expanded(root));

    /* Set back to true */
    lv_treeview_set_default_expanded(tree, true);
    lv_obj_t * child = lv_treeview_add_node(root, "Child");
    TEST_ASSERT_TRUE(lv_treeview_node_is_expanded(child));
}

/* Test node text set/get */
void test_treeview_node_set_text(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * node = lv_treeview_add_node(tree, "Original");
    TEST_ASSERT_EQUAL_STRING("Original", lv_treeview_node_get_text(node));

    lv_treeview_node_set_text(node, "Changed");
    TEST_ASSERT_EQUAL_STRING("Changed", lv_treeview_node_get_text(node));
}

/* Test node removal */
void test_treeview_node_remove(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    lv_obj_t * child = lv_treeview_add_node(root, "Child");

    TEST_ASSERT_EQUAL(1, lv_treeview_node_get_child_count(root));

    lv_treeview_node_remove(child);
    TEST_ASSERT_EQUAL(0, lv_treeview_node_get_child_count(root));
}

/* Test collapse hides children */
void test_treeview_collapse_hides_children(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    lv_obj_t * child = lv_treeview_add_node(root, "Child");

    /* Initially visible */
    TEST_ASSERT_FALSE(lv_obj_is_hidden(child));

    /* Collapse root should hide child */
    lv_treeview_node_collapse(root);
    TEST_ASSERT_TRUE(lv_obj_is_hidden(child));

    /* Expand root should show child */
    lv_treeview_node_expand(root);
    TEST_ASSERT_FALSE(lv_obj_is_hidden(child));
}

/* Test deep nesting visibility */
void test_treeview_deep_nesting_visibility(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    lv_obj_t * folder = lv_treeview_add_node(root, "Folder");
    lv_obj_t * item = lv_treeview_add_node(folder, "Item");

    /* All visible initially */
    TEST_ASSERT_FALSE(lv_obj_is_hidden(folder));
    TEST_ASSERT_FALSE(lv_obj_is_hidden(item));

    /* Collapse folder hides item but folder remains visible */
    lv_treeview_node_collapse(folder);
    TEST_ASSERT_FALSE(lv_obj_is_hidden(folder));
    TEST_ASSERT_TRUE(lv_obj_is_hidden(item));

    /* Collapse root hides both folder and item */
    lv_treeview_node_collapse(root);
    TEST_ASSERT_TRUE(lv_obj_is_hidden(folder));
    TEST_ASSERT_TRUE(lv_obj_is_hidden(item));

    /* Expand root shows folder, but item stays hidden (folder still collapsed) */
    lv_treeview_node_expand(root);
    TEST_ASSERT_FALSE(lv_obj_is_hidden(folder));
    TEST_ASSERT_TRUE(lv_obj_is_hidden(item));

    /* Expand folder shows item */
    lv_treeview_node_expand(folder);
    TEST_ASSERT_FALSE(lv_obj_is_hidden(item));
}

/* Test adding node to treeview directly creates root */
void test_treeview_add_node_as_root(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_NULL(lv_treeview_node_get_parent(root));
    TEST_ASSERT_EQUAL_STRING("Root", lv_treeview_node_get_text(root));
}

/* Test toggle does nothing on leaf nodes */
void test_treeview_toggle_leaf_node(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_t * leaf = lv_treeview_add_node(tree, "Leaf");
    bool initial_state = lv_treeview_node_is_expanded(leaf);

    /* Toggling a leaf node should not change its expanded state */
    lv_treeview_node_toggle(leaf);
    TEST_ASSERT_EQUAL(initial_state, lv_treeview_node_is_expanded(leaf));
}

/* Test add root node with default_expanded false */
void test_treeview_root_respects_default_expanded(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_treeview_set_default_expanded(tree, false);
    lv_obj_t * root = lv_treeview_add_node(tree, "Collapsed Root");
    TEST_ASSERT_FALSE(lv_treeview_node_is_expanded(root));

    lv_treeview_set_default_expanded(tree, true);
    lv_obj_t * root2 = lv_treeview_add_node(root, "Expanded Child"); /* root is the parent */
    TEST_ASSERT_TRUE(lv_treeview_node_is_expanded(root2));
}

/* Test screenshot */
void test_treeview_snapshot(void)
{
    tree = lv_treeview_create(active_screen);
    TEST_ASSERT_NOT_NULL(tree);

    lv_obj_set_size(tree, 200, 400);

    lv_obj_t * root = lv_treeview_add_node(tree, "Root");
    lv_obj_t * folder1 = lv_treeview_add_node(root, "Folder 1");
    lv_treeview_add_node(folder1, "Item 1-1");
    lv_treeview_add_node(folder1, "Item 1-2");
    lv_obj_t * folder2 = lv_treeview_add_node(root, "Folder 2");
    lv_treeview_add_node(folder2, "Item 2-1");

    lv_obj_center(tree);

    TEST_ASSERT_EQUAL_SCREENSHOT("widgets/treeview_1.png");
}

#endif
