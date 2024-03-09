#include "gui.h"

inline void add_rect_filled_multi_color_rounded( const ImVec2& p_min, const ImVec2& p_max, ImU32 bg_color, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left, float rounding, ImDrawFlags rounding_corners );
inline void color_edit_restore_hs( const float* col, float* H, float* S, float* V );
inline float hue_bar( float col[4], float H, bool *value_changed );
inline void alpha_bar( float col[4], float* a, bool *value_changed );
inline void square( float col[4], float h, float* s, float* v, bool* value_changed );
inline bool color_btn( const char* str_id, ImColor col, bool selected );
bool color_picker( const char* str_id, float col[4] );

using namespace ImGui;
