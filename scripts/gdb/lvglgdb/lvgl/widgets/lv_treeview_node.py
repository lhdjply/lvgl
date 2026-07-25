"""
Auto-generated wrapper for lv_treeview_node_t.

Do not edit manually. Regenerate from the GDB script root with:
    python3 scripts/generate_all.py
"""

from lvglgdb.lvgl.core.lv_obj import LVObject
from ._helpers import ptr_or_none, safe_string


class LVTreeviewNode(LVObject):
    """LVGL treeview widget (lv_treeview_node_t)."""

    def __init__(self, obj):
        super().__init__(obj)
        self._wv = self.cast("lv_treeview_node_t", ptr=True) or self

    @property
    def label(self):
        return ptr_or_none(self._wv.safe_field("label"))

    @property
    def children_container(self):
        return ptr_or_none(self._wv.safe_field("children_container"))

    @property
    def parent(self):
        return ptr_or_none(self._wv.safe_field("parent"))

    @property
    def text(self):
        return safe_string(self._wv, "text")

    @property
    def expanded(self):
        return int(self._wv.safe_field("expanded", 0))

    @property
    def has_children(self):
        return int(self._wv.safe_field("has_children", 0))

    @property
    def depth(self):
        return int(self._wv.safe_field("depth", 0))

    def snapshot(self, include_children=False, include_styles=False):
        """Snapshot with widget-specific fields in widget_data."""
        s = super().snapshot(include_children=include_children, include_styles=include_styles)
        d = s.get('widget_data') or {}
        d["label"] = self.label
        d["children_container"] = self.children_container
        d["parent"] = self.parent
        d["text"] = self.text
        d["expanded"] = self.expanded
        d["has_children"] = self.has_children
        d["depth"] = self.depth
        s['widget_data'] = d
        return s
