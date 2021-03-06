#pragma once


namespace user
{


   class CLASS_DECL_AURA style_base :
      virtual public object
   {
      public:


         virtual void initialize_style_menu() = 0;
         virtual void initialize_style_button() = 0;
         virtual void initialize_style_menu_button() = 0;
         virtual void initialize_style_menu_popup() = 0;
         virtual void initialize_style_system_menu_button() = 0;
         virtual void initialize_style_system_menu_close() = 0;
         virtual void initialize_style_system_menu_popup() = 0;
         virtual void initialize_style() = 0;



         //virtual style * style_get(e_style estyle) = 0;
         ///virtual sp(style) & operator[](e_style estyle) = 0;


         virtual ::user::interaction * create_menu_button(::aura::application * papp) = 0;
         virtual bool prepare_menu(::user::menu_item * pitem) = 0;
         virtual bool prepare_menu_button(::user::menu_item * pitem) = 0;


         virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics,::user::frame * pframe) = 0;
         virtual void DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics) = 0;
         virtual bool simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics) = 0;
         virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui) = 0;
         virtual bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics,tab * ptab) = 0;
         virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText) = 0;
         virtual bool _001OnTabLayout(::user::tab * ptab) = 0;
         virtual void _001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck) = 0;
         virtual bool _001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar) = 0;
         virtual bool _001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar) = 0;
         virtual bool _001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar) = 0;


         virtual bool get_color(COLORREF & cr,e_color ecolor, ::user::interaction * pui);
         virtual bool get_font(::draw2d::font_sp & sp, e_font efont, ::user::interaction * pui);
         virtual bool get_translucency(e_translucency & etranslucency, e_element eelement, ::user::interaction * pui);
         virtual bool get_flag(bool & bSet, ::user::e_flag eflag, ::user::interaction * pui);
         virtual bool get_rect(RECT & rect, ::user::e_rect erect, ::user::interaction * pui);
         virtual bool get_int(int & i, ::user::e_int eint, ::user::interaction * pui);
         virtual bool get_double(double & d, ::user::e_double edouble, ::user::interaction * pui);

         virtual e_schema get_user_style() = 0;


   };


} // namespace user




