#pragma once

#pragma once


namespace user
{
   enum e_object
   {

      object_list,
      object_tree

   };


   enum e_theme
   {

      theme_lite,
      theme_blue,
      theme_dark

   };


   enum e_schema
   {

      schema_default,
      schema_menu,
      schema_button,
      schema_menu_button,
      schema_menu_close,
      schema_menu_popup,
      schema_system_menu_button,
      schema_system_menu_close,
      schema_system_menu_popup,

   };



   enum e_appearance
   {

      appearance_none,
      appearance_current,
      appearance_iconic,
      appearance_normal,
      appearance_left,
      appearance_top,
      appearance_right,
      appearance_bottom,
      appearance_top_left,
      appearance_top_right,
      appearance_bottom_left,
      appearance_bottom_right,
      appearance_zoomed,
      appearance_full_screen,
      appearance_minimal,
      appearance_notify_icon,
      appearance_up,
      appearance_down,
      appearance_fixed_size,


   };


   enum e_translucency
   {

      translucency_undefined,
      translucency_none,
      translucency_present,
      translucency_total

   };

   enum e_control_type
   {
      control_type_none,
      control_type_static,
      control_type_check_box,
      control_type_edit,
      control_type_simple_list,
      control_type_button,
      control_type_combo_box,
      control_type_edit_plain_text,
      control_type_list,
      control_type_mesh,
      control_type_tree,
      control_type_split,
      control_type_tab,
      control_type_toolbar,
      control_type_statusbar,
      control_type_menu
   };




   enum e_element
   {

      element_none,
      element_frame_window,
      element_tab,
      element_close_tab_button,
      element_status_image,
      element_text,
      element_icon,
      element_border,
      element_client,
      element_area,
      element_drop_down,
      element_item,
      element_search_edit,
      element_search_ok,
      element_scrollbar_rect,
      element_scrollbar_rectA,
      element_scrollbar_rectB,
      element_scrollbar_pageA,
      element_scrollbar_pageB,


      element_split = 10000,

   };

   using translucency_map = ::map < e_element,e_element,e_translucency,e_translucency >;


   enum e_event
   {
      event_initialize_control,
      event_button_down,
      event_button_clicked,
      event_m_button_down,
      event_m_button_up,
      event_list_clicked,
      event_mouse_enter,
      event_mouse_leave,
      event_set_check,
      event_timer,
      event_enter_key,
      event_escape,
      event_tab_key,
      event_key_down,
      event_after_change_text,
      event_after_change_cur_sel,
      event_after_change_cur_hover,
      event_timebar_change,
      event_menu_hover,
      event_context_menu_close,
      event_set_focus,
      event_kill_focus,
      event_on_create_view,
      event_on_create_tab,
      event_form_initialize,
      event_create,
      event_layout,
      event_calc_item_height,
      event_change_view_style
   };

   enum e_color
   {

      color_none,
      color_text,
      color_text_highlight,
      color_text_selected,
      color_text_selected_highlight,
      color_text_focused,
      color_background,
      color_background_highlight,
      color_background_selected,
      color_background_selected_highlight,
      color_border_normal,
      color_border_hover,
      color_border_press,
      color_border_disabled,
      color_background_normal,
      color_background_hover,
      color_background_press,
      color_background_disabled,
      color_text_normal,
      color_text_hover,
      color_text_press,
      color_text_disabled,
      color_button_background_normal,
      color_button_background_hover,
      color_button_background_press,
      color_button_background_disabled,
      color_button_text_normal,
      color_button_text_hover,
      color_button_text_press,
      color_button_text_disabled,
      color_face,
      color_face_lite,
      color_list_header,
      color_list_header_background,
      color_list_header_separator,
      color_list_item_background,
      color_list_background,
      color_edit_text,
      color_edit_background,
      color_edit_text_selected,
      color_edit_background_selected,
      color_tree_background,
      color_view_background,
      color_scrollbar_background,
      color_toolbar_background,
      color_toolbar_separator,
      color_split_layout_background,
      color_tab_client_background,
      color_tab_layout_background,
      color_action_hover_border_color,
   };

   using color_map = map < e_color,e_color,COLORREF,COLORREF >;

   enum e_font
   {

      font_default,
      font_button,
      font_plain_edit,
      font_tree,
      font_list_item,
      font_list_hover,
      font_static,
      font_toolbar,

   };

   using font_map = map < e_font,e_font,::draw2d::font_sp >;

   enum e_flag
   {

      flag_none,
      flag_border,

   };

   using flag_map = map < e_flag,e_flag,bool,bool >;

   enum e_rect
   {

      rect_none,
      rect_menu_margin,

   };

   using rect_map = ::map < e_rect,e_rect,rect,rect >;

   enum e_int
   {

      int_none,
      int_border,
      int_element_padding,
      int_menu_button_padding,
      int_check_box_size

   };

   enum e_double
   {

      double_none,
      double_default_one_min,
      double_width_rate,
      double_height_rate,
      double_default_one_max,

   };

   using int_map = ::map < e_int,e_int,int,int >;

   using double_map = ::map < e_double,e_double,double,double >;

   enum e_timer
   {

      timer_command_probe = 11225,
      timer_menu

   };


   enum e_control_function
   {
      // Text got from control m_uiId member
      control_function_static,
      // Text got from control m_uiText member
      control_function_static2,
      control_function_data_selection,
      control_function_check_box,
      control_function_duplicate_on_check_box,
      control_function_disable_on_check_box,
      control_function_save_on_change,
      control_function_vms_data_edit,
      control_function_action,
      control_function_edit_multi_line,
   };


   enum e_control_data_type
   {
      control_data_type_string,
      control_data_type_natural,
   };


   enum e_control_ddx
   {

      control_ddx_none,
      control_ddx_flags,
      control_ddx_dbflags,

   };


} // namespace user


