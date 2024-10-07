#if !defined(FCODER_DEFAULT_BINDINGS_CPP)
#define FCODER_DEFAULT_BINDINGS_CPP

#include "4coder_default_include.cpp"
#include "generated/managed_id_metadata.cpp"

String_ID mapid_shared;
String_ID mapid_normal;
String_ID mapid_insert;
String_ID mapid_delete;

void set_current_mapid(Application_Links* app, Command_Map_ID mapid)
{
    View_ID view = get_active_view(app, 0);
    Buffer_ID buffer = view_get_buffer(app, view, 0);
    Managed_Scope scope = buffer_get_managed_scope(app, buffer);
    Command_Map_ID* map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID);
    *map_id_ptr = mapid;
}

CUSTOM_COMMAND_SIG(switch_mode_normal)
{
    set_current_mapid(app, mapid_normal);
    
    active_color_table.arrays[defcolor_cursor].vals[0] = 0xffff5533;
    active_color_table.arrays[defcolor_at_cursor].vals[0] = 0xff00aacc;
    active_color_table.arrays[defcolor_margin_active].vals[0] = 0xffff5533;
}

CUSTOM_COMMAND_SIG(switch_mode_insert)
{
    set_current_mapid(app, mapid_insert);
    
    active_color_table.arrays[defcolor_cursor].vals[0] = 0xff80ff80;
    active_color_table.arrays[defcolor_at_cursor].vals[0] = 0xff293134;
    active_color_table.arrays[defcolor_margin_active].vals[0] = 0xff80ff80;
}

CUSTOM_COMMAND_SIG(switch_mode_delete)
{
    set_current_mapid(app, mapid_delete);
    
    active_color_table.arrays[defcolor_cursor].vals[0] = 0xffffff00;
    active_color_table.arrays[defcolor_at_cursor].vals[0] = 0xff0000ff;
}

CUSTOM_COMMAND_SIG(move_white_left)
{
    move_left_whitespace_boundary(app);
}

CUSTOM_COMMAND_SIG(move_white_right)
{
    move_right_whitespace_boundary(app);
}

CUSTOM_COMMAND_SIG(move_token_left)
{
    move_left_whitespace_or_token_boundary(app);
}

CUSTOM_COMMAND_SIG(move_token_right)
{
    move_right_whitespace_or_token_boundary(app);
}

CUSTOM_COMMAND_SIG(move_bol)
{
    seek_beginning_of_line(app);
}

CUSTOM_COMMAND_SIG(move_eol)
{
    seek_end_of_line(app);
}

CUSTOM_COMMAND_SIG(move_up_blank)
{
    move_up_to_blank_line(app);
}

CUSTOM_COMMAND_SIG(move_down_blank)
{
    move_down_to_blank_line(app);
}

CUSTOM_COMMAND_SIG(move_up_half)
{
    View_ID v = get_active_view(app, Access_ReadVisible);
    f32 h = get_page_jump(app, v);
    move_vertical_pixels(app, -h / 2);
}

CUSTOM_COMMAND_SIG(move_down_half)
{
    View_ID v = get_active_view(app, Access_ReadVisible);
    f32 h = get_page_jump(app, v);
    move_vertical_pixels(app, h / 2);
}

CUSTOM_COMMAND_SIG(centre_view_mid)
{
    center_view(app);
}

CUSTOM_COMMAND_SIG(centre_view_top)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Rect_f32 region = view_get_buffer_region(app, view);
    i64 pos = view_get_cursor_pos(app, view);
    Buffer_Cursor cursor = view_compute_cursor(app, view, seek_pos(pos));
    f32 view_height = rect_height(region);
    Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
    scroll.target.line_number = cursor.line;
    scroll.target.pixel_shift.y = -view_height * 0.1f;
    view_set_buffer_scroll(app, view, scroll, SetBufferScroll_SnapCursorIntoView);
    no_mark_snap_to_cursor(app, view);
}

CUSTOM_COMMAND_SIG(centre_view_bot)
{
    View_ID view = get_active_view(app, Access_ReadVisible);
    Rect_f32 region = view_get_buffer_region(app, view);
    i64 pos = view_get_cursor_pos(app, view);
    Buffer_Cursor cursor = view_compute_cursor(app, view, seek_pos(pos));
    f32 view_height = rect_height(region);
    Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
    scroll.target.line_number = cursor.line;
    scroll.target.pixel_shift.y = -view_height * 0.9f;
    view_set_buffer_scroll(app, view, scroll, SetBufferScroll_SnapCursorIntoView);
    no_mark_snap_to_cursor(app, view);
}

CUSTOM_COMMAND_SIG(delete_white_left)
{
    set_mark(app);
    move_white_left(app);
    delete_range(app);
}

CUSTOM_COMMAND_SIG(delete_white_right)
{
    set_mark(app);
    move_white_right(app);
    delete_range(app);
}

CUSTOM_COMMAND_SIG(delete_token_left)
{
    set_mark(app);
    move_token_left(app);
    delete_range(app);
}

CUSTOM_COMMAND_SIG(delete_token_right)
{
    set_mark(app);
    move_token_right(app);
    delete_range(app);
}

CUSTOM_COMMAND_SIG(delete_bol)
{
    set_mark(app);
    move_bol(app);
    delete_range(app);
}

CUSTOM_COMMAND_SIG(delete_eol)
{
    set_mark(app);
    move_eol(app);
    delete_range(app);
}

CUSTOM_COMMAND_SIG(modal_delete_white_left)
{
    delete_white_left(app);
    switch_mode_normal(app);
}

CUSTOM_COMMAND_SIG(modal_delete_white_right)
{
    delete_white_right(app);
    switch_mode_normal(app);
}

CUSTOM_COMMAND_SIG(modal_delete_token_left)
{
    delete_token_left(app);
    switch_mode_normal(app);
}

CUSTOM_COMMAND_SIG(modal_delete_token_right)
{
    delete_token_right(app);
    switch_mode_normal(app);
}

CUSTOM_COMMAND_SIG(modal_delete_bol)
{
    delete_bol(app);
    switch_mode_normal(app);
}

CUSTOM_COMMAND_SIG(modal_delete_eol)
{
    delete_eol(app);
    switch_mode_normal(app);
}

CUSTOM_COMMAND_SIG(modal_delete_line)
{
    delete_line(app);
    switch_mode_normal(app);
}

void
custom_layer_init(Application_Links *app){
    Thread_Context *tctx = get_thread_context(app);
    
    default_framework_init(app);
    
    set_all_default_hooks(app);
    mapping_init(tctx, &framework_mapping);
    
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
    
    mapid_shared = vars_save_string_lit( "mapid_shared" );
    mapid_normal = vars_save_string_lit( "mapid_normal" );
    mapid_insert = vars_save_string_lit( "mapid_insert" );
    mapid_delete = vars_save_string_lit( "mapid_delete" );
    
    MappingScope();
    SelectMapping(&framework_mapping);
    
    SelectMap(global_map_id);
    SelectMap(mapid_shared);
    BindCore(default_startup, CoreCode_Startup);
    BindCore(default_try_exit, CoreCode_TryExit);
    
    BindCore(default_startup, CoreCode_Startup);
    BindCore(default_try_exit, CoreCode_TryExit);
    BindCore(clipboard_record_clip, CoreCode_NewClipboardContents);
    BindMouseWheel(mouse_wheel_scroll);
    BindMouseWheel(mouse_wheel_change_face_size, KeyCode_Control);
    
    BindMouse(click_set_cursor_and_mark, MouseCode_Left);
    BindMouseRelease(click_set_cursor, MouseCode_Left);
    BindCore(click_set_cursor_and_mark, CoreCode_ClickActivateView);
    BindMouseMove(click_set_cursor_if_lbutton);
    
    Bind(switch_mode_normal, KeyCode_Escape);
    Bind(move_left, KeyCode_Left);
    Bind(move_right, KeyCode_Right);
    Bind(move_up, KeyCode_Up);
    Bind(move_down, KeyCode_Down);
    
    Bind(cut, KeyCode_X, KeyCode_Control);
    Bind(copy, KeyCode_C, KeyCode_Control);
    Bind(paste, KeyCode_V, KeyCode_Control);
    Bind(delete_range, KeyCode_D, KeyCode_Control);
    Bind(save, KeyCode_S, KeyCode_Control);
    
    Bind(exit_4coder, KeyCode_F4, KeyCode_Alt);
    
    // Normal
    SelectMap(mapid_normal);
    ParentMap(mapid_shared);
    Bind(switch_mode_insert, KeyCode_I);
    Bind(switch_mode_delete, KeyCode_D);
    
    Bind(move_left, KeyCode_H);
    Bind(move_right, KeyCode_L);
    Bind(move_up, KeyCode_K);
    Bind(move_down, KeyCode_J);
    
    Bind(move_token_left, KeyCode_H, KeyCode_Shift);
    Bind(move_token_right, KeyCode_L, KeyCode_Shift);
    Bind(move_up_blank, KeyCode_K, KeyCode_Shift);
    Bind(move_down_blank, KeyCode_J, KeyCode_Shift);
    
    Bind(move_white_left, KeyCode_H, KeyCode_Control);
    Bind(move_white_right, KeyCode_L, KeyCode_Control);
    Bind(move_up_half, KeyCode_K, KeyCode_Control);
    Bind(move_down_half, KeyCode_J, KeyCode_Control);
    
    Bind(move_white_left, KeyCode_H, KeyCode_Control, KeyCode_Shift);
    Bind(move_white_right, KeyCode_L, KeyCode_Control, KeyCode_Shift);
    Bind(move_up_half, KeyCode_K, KeyCode_Control, KeyCode_Shift);
    Bind(move_down_half, KeyCode_J, KeyCode_Control, KeyCode_Shift);
    
    Bind(centre_view_mid, KeyCode_Equal);
    Bind(centre_view_top, KeyCode_Minus);
    Bind(centre_view_bot, KeyCode_Minus, KeyCode_Shift);
    Bind(delete_line, KeyCode_D, KeyCode_Shift);
    
    // Insert
    SelectMap(mapid_insert);
    ParentMap(mapid_shared);
    BindTextInput(write_text_and_auto_indent);
    Bind(backspace_char, KeyCode_Backspace);
    Bind(delete_token_left, KeyCode_Backspace, KeyCode_Shift);
    Bind(delete_white_left, KeyCode_Backspace, KeyCode_Control);
    Bind(delete_token_right, KeyCode_Delete, KeyCode_Shift);
    Bind(delete_white_right, KeyCode_Delete, KeyCode_Control);
    
    // Delete
    SelectMap(mapid_delete);
    Bind(switch_mode_normal, KeyCode_Escape);
    Bind(modal_delete_line, KeyCode_D);
    Bind(modal_delete_bol, KeyCode_Left, KeyCode_Control);
    Bind(modal_delete_eol, KeyCode_Right, KeyCode_Control);
    Bind(modal_delete_white_left, KeyCode_Left, KeyCode_Shift);
    Bind(modal_delete_white_right, KeyCode_Right, KeyCode_Shift);
    Bind(modal_delete_token_left, KeyCode_Left);
    Bind(modal_delete_token_right, KeyCode_Right);
    
    SelectMap(file_map_id);
    ParentMap(mapid_normal);
    
    SelectMap(code_map_id);
    ParentMap(mapid_normal);
}

#if 0
#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

void custom_layer_init(Application_Links *app) {
    Thread_Context *tctx = get_thread_context(app);
    
    default_framework_init(app);
    
    set_all_default_hooks(app);
    mapping_init(tctx, &framework_mapping);
    
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
    
    setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
	
    setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
}
#endif

#endif
