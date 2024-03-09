#pragma once

#include <imgui.h>
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include <imgui_internal.h>
#include <imgui_tricks.hpp>
#include <functional>

using namespace ImGui;

#define font( n ) ImGui::GetIO( ).Fonts->Fonts[n]

inline const char* KEY_NAMES[] = {
    "NONE",
    "M1",
    "M2",
    "CN",
    "M3",
    "M4",
    "M5",
    "NONE",
    "BACK",
    "TAB",
    "NONE",
    "NONE",
    "BACK",
    "ENT",
    "NONE",
    "NONE",
    "SHIFT",
    "CTRL",
    "ALT",
    "PAUSE",
    "CAPS",
    "KAN",
    "NONE",
    "JUN",
    "FIN",
    "KAN",
    "NONE",
    "ESC",
    "CON",
    "NCO",
    "ACC",
    "MAD",
    "SPACE",
    "PGU",
    "PGD",
    "END",
    "HOME",
    "LEFT",
    "UP",
    "RIGH",
    "DOWN",
    "SEL",
    "PRINT",
    "EXE",
    "PRINT",
    "INS",
    "DEL",
    "HEL",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "???",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "WIN",
    "WIN",
    "APP",
    "NONE",
    "SLE",
    "NUM0",
    "NUM1",
    "NUM2",
    "NUM3",
    "NUM4",
    "NUM5",
    "NUM6",
    "NUM7",
    "NUM8",
    "NUM9",
    "*",
    "+",
    "|",
    "-",
    ".",
    "/",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NUMLOCK",
    "SCR",
    "=",
    "MAS",
    "TOY",
    "OYA",
    "OYA",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "NONE",
    "SHIFT",
    "SHIFT",
    "CTRL",
    "CTRL",
    "ALT",
    "ALT"
};

struct multi_select_item {
    const char* label;
    bool selected = false;

    multi_select_item( const char* _label ) : label{ _label } { };

    operator bool( ) const {
        return selected;
    }
};

struct c_tab {
    const char* m_label;
    const char* m_icon;

    std::vector< std::function< void( ) > > pages;
    std::vector < const char* > m_subtabs;
    int cur_subtab = 0;

    c_tab( const char* icon, const char* label, std::vector< const char* > subtabs ) {
        m_icon = icon;
        m_label = label;
        m_subtabs = subtabs;
    }
};

namespace ui {
    inline ImVec2 size{ 650, 440 };
    inline int next_tab;
    inline int next_subtab;
    
    inline float content_anim = 0.f;
    inline float anim_speed = 0.12f;
    inline float content_anim_dest = 1.f;
    inline int cur_page = 0;

    bool tab( int num );
    void rotate_start( );
    ImVec2 rotation_center( );
    void rotate_end( float rad, ImVec2 center );
    void handle_alpha_anim( );
    void render_page( );
    void add_page( int tab, std::function< void( ) > code );
    ImVec2 text_size( int font, const char* text );
    void styles( );
    void colors( );
    bool color_btn( const char* str_id, float col[4], ImVec2 size );

    void begin_child( const char* name, ImVec2 size = ImVec2{ 0, 0 } );
    void end_child( );
    void multi_select( const char* label, std::vector< multi_select_item >& items );

    inline std::vector< c_tab > tabs{ 
        { "C", "Celestial", { } },
    };
};
