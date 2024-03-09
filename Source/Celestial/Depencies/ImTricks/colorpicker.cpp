#define _CRT_SECURE_NO_WARNINGS
#include "gui.h"
#include "colorpicker.h"

using namespace ImGui;

inline void add_rect_filled_multi_color_rounded( const ImVec2& p_min, const ImVec2& p_max, ImU32 bg_color, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left, float rounding, ImDrawFlags rounding_corners )
{
    rounding = ImMin(rounding, ImFabs(p_max.x - p_min.x) * (((rounding_corners & ImDrawCornerFlags_Top) == ImDrawCornerFlags_Top) || ((rounding_corners & ImDrawCornerFlags_Bot) == ImDrawCornerFlags_Bot) ? 0.5f : 1.0f) - 1.0f);
    rounding = ImMin(rounding, ImFabs(p_max.y - p_min.y) * (((rounding_corners & ImDrawCornerFlags_Left) == ImDrawCornerFlags_Left) || ((rounding_corners & ImDrawCornerFlags_Right) == ImDrawCornerFlags_Right) ? 0.5f : 1.0f) - 1.0f);

    if (rounding <= 0.0f || rounding_corners == 0)
        return;
    else
    {
        const float rounding_tl = (rounding_corners & ImDrawCornerFlags_TopLeft) ? rounding : 0.0f;
        const float rounding_tr = (rounding_corners & ImDrawCornerFlags_TopRight) ? rounding : 0.0f;
        const float rounding_br = (rounding_corners & ImDrawCornerFlags_BotRight) ? rounding : 0.0f;
        const float rounding_bl = (rounding_corners & ImDrawCornerFlags_BotLeft) ? rounding : 0.0f;

        const ImVec2 uv = ImGui::GetWindowDrawList( )->_Data->TexUvWhitePixel;
        ImGui::GetWindowDrawList( )->PrimReserve(6, 4);
        ImGui::GetWindowDrawList( )->PrimWriteIdx((ImDrawIdx)(ImGui::GetWindowDrawList( )->_VtxCurrentIdx)); ImGui::GetWindowDrawList( )->PrimWriteIdx((ImDrawIdx)(ImGui::GetWindowDrawList( )->_VtxCurrentIdx + 1)); ImGui::GetWindowDrawList( )->PrimWriteIdx((ImDrawIdx)(ImGui::GetWindowDrawList( )->_VtxCurrentIdx + 2));
        ImGui::GetWindowDrawList( )->PrimWriteIdx((ImDrawIdx)(ImGui::GetWindowDrawList( )->_VtxCurrentIdx)); ImGui::GetWindowDrawList( )->PrimWriteIdx((ImDrawIdx)(ImGui::GetWindowDrawList( )->_VtxCurrentIdx + 2)); ImGui::GetWindowDrawList( )->PrimWriteIdx((ImDrawIdx)(ImGui::GetWindowDrawList( )->_VtxCurrentIdx + 3));
        ImGui::GetWindowDrawList( )->PrimWriteVtx(p_min, uv, col_upr_left);
        ImGui::GetWindowDrawList( )->PrimWriteVtx(ImVec2(p_max.x, p_min.y), uv, col_upr_right);
        ImGui::GetWindowDrawList( )->PrimWriteVtx(p_max, uv, col_bot_right);
        ImGui::GetWindowDrawList( )->PrimWriteVtx(ImVec2(p_min.x, p_max.y), uv, col_bot_left);

        ImGui::GetWindowDrawList( )->PathLineTo(p_min);
        ImGui::GetWindowDrawList( )->PathArcTo(ImVec2(p_min.x + rounding_tl, p_min.y + rounding_tl), rounding_tl, 4.820f, 3.100f);
        ImGui::GetWindowDrawList( )->PathFillConvex(bg_color);

        ImGui::GetWindowDrawList( )->PathLineTo(ImVec2(p_max.x, p_min.y));
        ImGui::GetWindowDrawList( )->PathArcTo(ImVec2(p_max.x - rounding_tr, p_min.y + rounding_tr), rounding_tr, 6.3400f, 4.620f);
        ImGui::GetWindowDrawList( )->PathFillConvex(bg_color);

        ImGui::GetWindowDrawList( )->PathLineTo(ImVec2(p_max.x, p_max.y));
        ImGui::GetWindowDrawList( )->PathArcTo(ImVec2(p_max.x - rounding_br, p_max.y - rounding_br), rounding_br, 7.960f, 6.240f);
        ImGui::GetWindowDrawList( )->PathFillConvex(bg_color);

        ImGui::GetWindowDrawList( )->PathLineTo(ImVec2(p_min.x, p_max.y));
        ImGui::GetWindowDrawList( )->PathArcTo(ImVec2(p_min.x + rounding_bl, p_max.y - rounding_bl), rounding_bl, 9.5f, 7.770f);
        ImGui::GetWindowDrawList( )->PathFillConvex(bg_color);

    }
}

inline void color_edit_restore_hs( const float* col, float* H, float* S, float* V )
{
    ImGuiContext& g = *GImGui;
    if (g.ColorEditLastColor != ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0)))
        return;

    if (*S == 0.0f || (*H == 0.0f && g.ColorEditLastHue == 1))
        *H = g.ColorEditLastHue;

    if (*V == 0.0f)
        *S = g.ColorEditLastSat;
}

inline float hue_bar( float col[4], float H, bool *value_changed ) {
    auto style = ImGui::GetStyle( );
    auto window = ImGui::GetCurrentWindow( );
    auto io = ImGui::GetIO( );
    float w = window->Size.x - ( window->DC.CursorPos.x - window->Pos.x ) - style.WindowPadding.x;
    ImVec2 pos = window->DC.CursorPos;
    ImRect rect( pos, pos + ImVec2( w, 8 ) );

    const int style_alpha8 = IM_F32_TO_INT8_SAT( style.Alpha );
    const ImU32 col_hues[6 + 1] = { IM_COL32( 255, 0, 0, style_alpha8 ), IM_COL32( 255, 255, 0, style_alpha8 ), IM_COL32( 0, 255, 0, style_alpha8 ), IM_COL32( 0, 255, 255, style_alpha8 ), IM_COL32( 0, 0, 255, style_alpha8 ), IM_COL32( 255, 0, 255, style_alpha8 ), IM_COL32( 255, 0, 0, style_alpha8 ) };    const ImU32 col_midgrey = IM_COL32( 128, 128, 128, style_alpha8 );

    for (int i = 0; i < 6; ++i)
        window->DrawList->addrectFilledMultiColor( ImVec2( rect.Min.x + i * ( w / 6 ), rect.Min.y ), ImVec2( rect.Min.x + ( i + 1 ) * ( w / 6 ), rect.Max.y ), col_hues[i], col_hues[i + 1], col_hues[i + 1], col_hues[i] );

    add_rect_filled_multi_color_rounded( rect.Min, rect.Max, ImGui::GetColorU32( ImGuiCol_WindowBg ), ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, rect.GetHeight( ) / 2, ImDrawFlags_RoundCornersAll );

    ImVec4 hue_color_f( 1, 1, 1, style.Alpha ); ImGui::ColorConvertHSVtoRGB( H, 1, 1, hue_color_f.x, hue_color_f.y, hue_color_f.z );
    ImU32 hue_color32 = ImGui::ColorConvertFloat4ToU32( hue_color_f );
    window->DrawList->AddCircleFilled( { rect.Min.x + rect.GetHeight( ) / 2 + ( w - rect.GetHeight( ) ) * H, rect.GetCenter( ).y }, rect.GetHeight( ) / 2 + 3, hue_color32 );
    window->DrawList->AddCircle( { rect.Min.x + rect.GetHeight( ) / 2 + ( w - rect.GetHeight( ) ) * H, rect.GetCenter( ).y }, rect.GetHeight( ) / 2 + 3, ImColor( 255, 255, 255, int( style.Alpha * 255 ) ) );

    ImGui::InvisibleButton( "hue", rect.GetSize( ) );
    if ( ImGui::IsItemActive( ) ) {
        H = ImSaturate( ( io.MousePos.x - pos.x ) / ( rect.GetWidth( ) + 1 ) );
        *value_changed = true;
    }

    return H;
}

inline void alpha_bar( float col[4], float* a, bool *value_changed ) {
    auto style = ImGui::GetStyle( );
    auto window = ImGui::GetCurrentWindow( );
    auto io = ImGui::GetIO( );
    float w = window->Size.x - ( window->DC.CursorPos.x - window->Pos.x ) - style.WindowPadding.x;
    ImVec2 pos = window->DC.CursorPos;
    ImRect rect( pos, pos + ImVec2( w, 8 ) );

    ImGui::RenderColorRectWithAlphaCheckerboard( window->DrawList, rect.Min, rect.Max, 0, w / 60, ImVec2( 0.0f, 0.0f ) );
    window->DrawList->addrectFilledMultiColor( rect.Min, rect.Max, ImColor{ col[0], col[1], col[2], 0.f }, ImColor{ col[0], col[1], col[2], GImGui->Style.Alpha }, ImColor{ col[0], col[1], col[2], GImGui->Style.Alpha }, ImColor{ col[0], col[1], col[2], 0.f } );
    add_rect_filled_multi_color_rounded( rect.Min, rect.Max, ImGui::GetColorU32( ImGuiCol_WindowBg ), ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, rect.GetHeight( ) / 2, ImDrawFlags_RoundCornersAll );

    auto circle_col = ImTricks::Animations::FastColorLerp( ImColor( 1.f, 1.f, 1.f, style.Alpha ), ImColor( col[0], col[1], col[2], 1.f ), *a );
    window->DrawList->AddCircleFilled( { rect.Min.x + rect.GetHeight( ) / 2 + ( w - rect.GetHeight( ) ) * *a, rect.GetCenter( ).y }, rect.GetHeight( ) / 2 + 3, circle_col );
    window->DrawList->AddCircle( { rect.Min.x + rect.GetHeight( ) / 2 + ( w - rect.GetHeight( ) ) * *a, rect.GetCenter( ).y }, rect.GetHeight( ) / 2 + 3, ImColor( 255, 255, 255, int( style.Alpha * 255 ) ) );

    ImGui::InvisibleButton( "alpha", rect.GetSize( ) );
    if ( ImGui::IsItemActive( ) ) {
        *a = ImSaturate( ( io.MousePos.x - pos.x ) / ( rect.GetWidth( ) - 1 ) );
        *value_changed = true;
    }
}

inline void square( float col[4], float h, float* s, float* v, bool* value_changed ) {
    auto style = ImGui::GetStyle( );
    auto window = ImGui::GetCurrentWindow( );
    auto io = ImGui::GetIO( );
    auto g = *GImGui;
    ImVec2 pos = window->DC.CursorPos;
    ImRect rect( pos, pos + ImVec2( window->Size.x - style.WindowPadding.x * 2, ( window->Size.x - style.WindowPadding.x * 2 ) * 0.5f ) );

    ImVec4 hue_color_f( 1, 1, 1, style.Alpha ); ImGui::ColorConvertHSVtoRGB( h, 1, 1, hue_color_f.x, hue_color_f.y, hue_color_f.z );
    ImU32 hue_color32 = ImGui::ColorConvertFloat4ToU32( hue_color_f );

    const int style_alpha8 = IM_F32_TO_INT8_SAT( style.Alpha );
    const ImU32 col_black = IM_COL32( 0, 0 ,0, style_alpha8 );
    const ImU32 col_white = IM_COL32( 255, 255, 255, style_alpha8 );

    window->DrawList->addrectFilledMultiColor( rect.Min, rect.Max, col_white, hue_color32, hue_color32, col_white);
    window->DrawList->addrectFilledMultiColor( rect.Min, rect.Max, 0, 0, col_black, col_black);
    add_rect_filled_multi_color_rounded( rect.Min, rect.Max, ImGui::GetColorU32( ImGuiCol_WindowBg ), ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, ImColor{ 0.f, 0.f, 0.f, 0.f }, style.FrameRounding, ImDrawFlags_RoundCornersAll );

    ImVec2 cursor_pos;
    cursor_pos.x = ImClamp(IM_ROUND(rect.Min.x + ImSaturate(*s)     * rect.GetWidth( )), rect.Min.x + 2, rect.Max.x - 2);
    cursor_pos.y = ImClamp(IM_ROUND(rect.Min.y + ImSaturate(1 - *v) * rect.GetHeight( )), rect.Min.y + 2, rect.Max.y - 2);

    auto circle_col = ImColor( col[0], col[1], col[2], 1.f );
    window->DrawList->AddCircleFilled( cursor_pos, 5, circle_col );
    window->DrawList->AddCircle( cursor_pos, 5, ImColor( 255, 255, 255, int( style.Alpha * 255 ) ) );

    ImGui::InvisibleButton( "sv", rect.GetSize( ) );
    if ( ImGui::IsItemActive( ) )
    {
        *s = ImSaturate( ( io.MousePos.x - rect.Min.x ) / ( rect.GetWidth( ) - 1 ) ) <= 0 ? 0.01f : ImSaturate( ( io.MousePos.x - rect.Min.x ) / ( rect.GetWidth( ) - 1 ) );
        *v = ( 1.0f - ImSaturate( ( io.MousePos.y - rect.Min.y ) / ( rect.GetHeight( ) - 1 ) ) ) <= 0 ? 0.01f : 1.0f - ImSaturate( ( io.MousePos.y - rect.Min.y ) / ( rect.GetHeight( ) - 1 ) );

        *value_changed = true;
    }
}

inline bool color_btn( const char* str_id, ImColor col, bool selected ) {
    auto window = ImGui::GetCurrentWindow( );
    auto pos = window->DC.CursorPos;
    auto id = window->GetID( str_id );

    ImVec2 size( 20, 20 );
    ImRect rect( pos, pos + size );

    ImGui::ItemSize( rect );
    ImGui::ItemAdd( rect, id );

    bool pressed = ImGui::ButtonBehavior( rect, id, NULL, NULL );

    auto anim = ImTricks::Animations::FastFloatLerp( str_id, 0, selected, 0.f, 1.f, ui::anim_speed );

    window->DrawList->AddCircleFilled( rect.GetCenter( ), rect.GetWidth( ) / 2 - 4 * anim, col );
    window->DrawList->AddCircle( rect.GetCenter( ), rect.GetWidth( ) / 2 - 1, col, 0, 2 * anim);

    return pressed;
}

bool color_picker( const char* str_id, float col[4] ) {
    auto style = ImGui::GetStyle( );
    auto window = ImGui::GetCurrentWindow( );
    auto pos = window->DC.CursorPos;
    ImGuiContext& gi = *GImGui;

    float h = 1.f, s = 1.f, v = 1.f;
    float r = col[0], g = col[1], b = col[2], a = col[3];
    int i[4] = { IM_F32_TO_INT8_UNBOUND(col[0]), IM_F32_TO_INT8_UNBOUND(col[1]), IM_F32_TO_INT8_UNBOUND(col[2]), IM_F32_TO_INT8_UNBOUND(col[3]) };

    bool value_changed = false;

    ImGui::ColorConvertRGBtoHSV( r, g, b, h, s, v );
    color_edit_restore_hs( col, &h, &s, &v );

    static std::unordered_map< const char*, int > selected_colors;
    auto it = selected_colors.find( str_id );

    if ( it == selected_colors.end( ) ) {
        selected_colors.insert( { str_id, -1 } );
        it = selected_colors.find( str_id );
    }

    char buf[64];
    ImFormatString(buf, IM_ARRAYSIZE(buf), "%02X%02X%02X%02X", ImClamp(i[0], 0, 255), ImClamp(i[1], 0, 255), ImClamp(i[2], 0, 255), ImClamp(i[3], 0, 255));
    ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, { 26, 35 / 2 - GImGui->FontSize / 2 } );
    ImGui::PushStyleColor( ImGuiCol_FrameBg, ImVec4( 1.f, 1.f, 1.f, 0.03f * style.Alpha ) );
    if ( ImGui::InputTextEx( "##Input", "", buf, sizeof( buf ), { window->Size.x - style.WindowPadding.x * 2, 35 }, 0 ) ) {
        value_changed = true;
        char* p = buf;
        while (*p == '#' || ImCharIsBlankA(*p))
            p++;
        i[0] = i[1] = i[2] = 0;
        i[3] = 0xFF;
        int ri = sscanf(p, "%02X%02X%02X%02X", (unsigned int*)&i[0], (unsigned int*)&i[1], (unsigned int*)&i[2], (unsigned int*)&i[3]);
        r = i[0] / 255.f;
        g = i[1] / 255.f;
        b = i[2] / 255.f;
        ImGui::ColorConvertRGBtoHSV( r, g, b, h, s, v );
        IM_UNUSED(ri);
    }
    ImGui::PopStyleColor( );
    ImGui::PushStyleColor( ImGuiCol_Text, ImGui::GetColorU32( ImGuiCol_TextDisabled ) );
    ImGui::RenderText( { pos.x + ImGui::GetStyle( ).FramePadding.x / 2 - ImGui::CalcTextSize( "#" ).x / 2 + 1, window->DC.CursorPos.y - ImGui::GetFrameHeight( ) - style.ItemSpacing.y + ImGui::GetStyle( ).FramePadding.y }, "#" );
    ImGui::PopStyleColor( );
    ImGui::PopStyleVar( );

    square( col, h, &s, &v, &value_changed );

    h = hue_bar( col, h, &value_changed );
    alpha_bar( col, &a, &value_changed );

    ImGui::ColorConvertHSVtoRGB( h, s, v, r, g, b );

    if ( value_changed ) {
        gi.ColorEditLastHue = h;
        gi.ColorEditLastSat = s;
        gi.ColorEditLastColor = ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0));

        col[0] = r;
        col[1] = g;
        col[2] = b;
        col[3] = a;
    }

    return true;
}
