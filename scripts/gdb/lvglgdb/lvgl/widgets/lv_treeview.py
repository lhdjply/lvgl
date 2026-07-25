"""
Auto-generated wrapper for lv_treeview_t.

Do not edit manually. Regenerate from the GDB script root with:
    python3 scripts/generate_all.py
"""

from lvglgdb.lvgl.core.lv_obj import LVObject
from ._helpers import ptr_or_none


class LVTreeview(LVObject):
    """LVGL treeview widget (lv_treeview_t)."""

    def __init__(self, obj):
        super().__init__(obj)
        self._wv = self.cast("lv_treeview_t", ptr=True) or self

    @property
    def root_node(self):
        return ptr_or_none(self._wv.safe_field("root_node"))

    @property
    def default_expanded(self):
        return int(self._wv.safe_field("default_expanded", 0))

    def snapshot(self, include_children=False, include_styles=False):
        """Snapshot with widget-specific fields in widget_data."""
        s = super().snapshot(include_children=include_children, include_styles=include_styles)
        d = s.get('widget_data') or {}
        d["root_node"] = self.root_node
        d["default_expanded"] = self.default_expanded
        s['widget_data'] = d
        return s
