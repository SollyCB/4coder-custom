#if !defined(FCODER_DEFAULT_BINDINGS_CPP)
#define FCODER_DEFAULT_BINDINGS_CPP

#include "4coder_default_include.cpp"
#include "generated/managed_id_metadata.cpp"

String_ID mapid_shared;
String_ID mapid_normal;
String_ID mapid_insert;
String_ID mapid_delete;

CUSTOM_COMMAND_SIG(proj_root) { project_go_to_root_directory(app); }
CUSTOM_COMMAND_SIG(buf_new) { interactive_new(app); }
CUSTOM_COMMAND_SIG(buf_open) { interactive_open_or_new(app); }
CUSTOM_COMMAND_SIG(buf_open_other) { open_in_other(app); }
CUSTOM_COMMAND_SIG(buf_switch) { interactive_switch_buffer(app); }
CUSTOM_COMMAND_SIG(buf_kill) { interactive_kill_buffer(app); }
CUSTOM_COMMAND_SIG(save_all) { save_all_dirty_buffers(app); }
CUSTOM_COMMAND_SIG(jump_first) { goto_first_jump(app); }
CUSTOM_COMMAND_SIG(jump_next) { goto_next_jump(app); }
CUSTOM_COMMAND_SIG(jump_prev) { goto_prev_jump(app); }
CUSTOM_COMMAND_SIG(jump_def) { jump_to_definition_at_cursor(app); }
CUSTOM_COMMAND_SIG(jump_bof) { goto_beginning_of_file(app); }
CUSTOM_COMMAND_SIG(jump_eof) { goto_end_of_file(app); }
CUSTOM_COMMAND_SIG(jump_line) { goto_line(app); }
CUSTOM_COMMAND_SIG(jump_other) { if_read_only_goto_position(app); }
CUSTOM_COMMAND_SIG(jump_same) { if_read_only_goto_position_same_panel(app); }
CUSTOM_COMMAND_SIG(macro_begin) { keyboard_macro_start_recording(app); }
CUSTOM_COMMAND_SIG(macro_end) { keyboard_macro_finish_recording(app); }
CUSTOM_COMMAND_SIG(macro_replay) { keyboard_macro_replay(app); }
CUSTOM_COMMAND_SIG(sh) { execute_any_cli(app); }
CUSTOM_COMMAND_SIG(build) { build_in_build_panel(app); }
CUSTOM_COMMAND_SIG(build_open) { change_to_build_panel(app); }
CUSTOM_COMMAND_SIG(build_close) { close_build_panel(app); }
CUSTOM_COMMAND_SIG(panel_switch) { change_active_panel(app); }
CUSTOM_COMMAND_SIG(panel_swap) { swap_panels(app); }
CUSTOM_COMMAND_SIG(panel_dup) { view_buffer_other_panel(app); }
CUSTOM_COMMAND_SIG(fkey_cmd) { project_fkey_command(app); }
CUSTOM_COMMAND_SIG(list_def) { list_all_locations_of_type_definition(app); }
CUSTOM_COMMAND_SIG(list_def_ident) { list_all_locations_of_type_definition_of_identifier(app); }
CUSTOM_COMMAND_SIG(list_ident_all) { list_all_locations_of_identifier(app); }
CUSTOM_COMMAND_SIG(list_all) { list_all_locations(app); }
CUSTOM_COMMAND_SIG(list_all_substr) { list_all_substring_locations_case_insensitive(app); }
CUSTOM_COMMAND_SIG(list_all_sel) { list_all_locations_of_selection(app); }
CUSTOM_COMMAND_SIG(scope) { select_surrounding_scope(app); }
CUSTOM_COMMAND_SIG(scope_next) { select_next_scope_absolute(app); }
CUSTOM_COMMAND_SIG(scope_prev) { select_prev_scope_absolute(app); }
CUSTOM_COMMAND_SIG(complete) { word_complete(app); }
CUSTOM_COMMAND_SIG(complete_drop_down) { word_complete_drop_down(app); }
CUSTOM_COMMAND_SIG(comment_toggle) { comment_line_toggle(app); }
CUSTOM_COMMAND_SIG(line_dup) { duplicate_line(app); }
CUSTOM_COMMAND_SIG(line_up) { move_line_up(app); }
CUSTOM_COMMAND_SIG(line_down) { move_line_down(app); }
CUSTOM_COMMAND_SIG(swap_mark) { cursor_mark_swap(app); }

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

CUSTOM_COMMAND_SIG(move_alpha_num_left)
{
    move_left_alpha_numeric_boundary(app);
}

CUSTOM_COMMAND_SIG(move_alpha_num_right)
{
    move_right_alpha_numeric_boundary(app);
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

CUSTOM_COMMAND_SIG(new_line_above)
{
    move_bol(app);
    write_text(app, string_u8_litexpr("\n"));
    auto_indent_line_at_cursor(app);
    move_up(app);
    switch_mode_insert(app);
}

CUSTOM_COMMAND_SIG(new_line_below)
{
    move_eol(app);
    write_text(app, string_u8_litexpr("\n"));
    auto_indent_line_at_cursor(app);
    switch_mode_insert(app);
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

CUSTOM_COMMAND_SIG(delete_alpha_num_left)
{
    set_mark(app);
    move_alpha_num_left(app);
    delete_range(app);
}

CUSTOM_COMMAND_SIG(delete_alpha_num_right)
{
    set_mark(app);
    move_alpha_num_right(app);
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
    
    mapid_shared = vars_save_string_lit("mapid_shared");
    mapid_normal = vars_save_string_lit("mapid_normal");
    mapid_insert = vars_save_string_lit("mapid_insert");
    mapid_delete = vars_save_string_lit("mapid_delete");
    
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
    
    Bind(command_lister, KeyCode_X, KeyCode_Alt);
    Bind(switch_mode_normal, KeyCode_Escape);
    Bind(move_left, KeyCode_Left);
    Bind(move_right, KeyCode_Right);
    Bind(move_up, KeyCode_Up);
    Bind(move_down, KeyCode_Down);
    
    Bind(move_token_left, KeyCode_Left, KeyCode_Shift);
    Bind(move_token_right, KeyCode_Right, KeyCode_Shift);
    Bind(move_up_blank, KeyCode_Up, KeyCode_Shift);
    Bind(move_down_blank, KeyCode_Down, KeyCode_Shift);
    
    Bind(move_white_left, KeyCode_Left, KeyCode_Control);
    Bind(move_white_right, KeyCode_Right, KeyCode_Control);
    Bind(move_up_half, KeyCode_Up, KeyCode_Control);
    Bind(move_down_half, KeyCode_Down, KeyCode_Control);
    
    Bind(move_alpha_num_left, KeyCode_Left, KeyCode_Alt);
    Bind(move_alpha_num_right, KeyCode_Right, KeyCode_Alt);
    
    Bind(move_white_left, KeyCode_H, KeyCode_Control, KeyCode_Shift);
    Bind(move_white_right, KeyCode_L, KeyCode_Control, KeyCode_Shift);
    
    Bind(cut, KeyCode_X, KeyCode_Control);
    Bind(copy, KeyCode_C, KeyCode_Control);
    Bind(paste, KeyCode_V, KeyCode_Control);
    Bind(delete_range, KeyCode_D, KeyCode_Control);
    Bind(save, KeyCode_S, KeyCode_Control);
    Bind(save_all, KeyCode_S, KeyCode_Control, KeyCode_Shift);
    Bind(undo, KeyCode_Z, KeyCode_Control);
    Bind(redo, KeyCode_R, KeyCode_Control);
    Bind(paste_next, KeyCode_V, KeyCode_Control, KeyCode_Shift);
    
    Bind(backspace_char, KeyCode_Backspace);
    Bind(delete_char, KeyCode_Delete);
    Bind(delete_token_left, KeyCode_Backspace, KeyCode_Shift);
    Bind(delete_token_right, KeyCode_Delete, KeyCode_Shift);
    Bind(delete_white_left, KeyCode_Backspace, KeyCode_Control);
    Bind(delete_white_right, KeyCode_Delete, KeyCode_Control);
    Bind(delete_alpha_num_left, KeyCode_Backspace, KeyCode_Alt);
    Bind(delete_alpha_num_right, KeyCode_Delete, KeyCode_Alt);
    
    Bind(exit_4coder, KeyCode_F4, KeyCode_Alt);
    
    // Normal
    SelectMap(mapid_normal);
    ParentMap(mapid_shared);
    Bind(switch_mode_insert, KeyCode_I);
    Bind(switch_mode_delete, KeyCode_D);
    
    Bind(undo, KeyCode_U);
    Bind(redo, KeyCode_U, KeyCode_Shift);
    
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
    
    Bind(move_alpha_num_left, KeyCode_H, KeyCode_Alt);
    Bind(move_alpha_num_right, KeyCode_L, KeyCode_Alt);
    
    Bind(move_white_left, KeyCode_H, KeyCode_Control, KeyCode_Shift);
    Bind(move_white_right, KeyCode_L, KeyCode_Control, KeyCode_Shift);
    Bind(move_up_half, KeyCode_K, KeyCode_Control, KeyCode_Shift);
    Bind(move_down_half, KeyCode_J, KeyCode_Control, KeyCode_Shift);
    
    Bind(centre_view_mid, KeyCode_Equal);
    Bind(centre_view_top, KeyCode_Minus);
    Bind(centre_view_bot, KeyCode_Minus, KeyCode_Shift);
    
    Bind(line_up, KeyCode_K, KeyCode_Alt);
    Bind(line_down, KeyCode_J, KeyCode_Alt);
    Bind(line_dup, KeyCode_M);
    Bind(set_mark, KeyCode_Space);
    Bind(swap_mark, KeyCode_Space, KeyCode_Control);
    
    Bind(jump_next, KeyCode_N);
    Bind(jump_prev, KeyCode_N, KeyCode_Shift);
    Bind(jump_first, KeyCode_N, KeyCode_Control, KeyCode_Shift);
    Bind(jump_def, KeyCode_W);
    Bind(jump_other, KeyCode_Return);
    Bind(jump_same, KeyCode_Return, KeyCode_Shift);
    Bind(jump_bof, KeyCode_G);
    Bind(jump_eof, KeyCode_G, KeyCode_Shift);
    Bind(jump_line, KeyCode_G, KeyCode_Control);
    
    Bind(scope, KeyCode_Semicolon);
    Bind(scope_prev, KeyCode_LeftBracket);
    Bind(scope_next, KeyCode_RightBracket);
    Bind(place_in_scope, KeyCode_S);
    
    Bind(search, KeyCode_F);
    Bind(reverse_search, KeyCode_F, KeyCode_Shift);
    Bind(list_def, KeyCode_T);
    Bind(list_def_ident, KeyCode_T, KeyCode_Control);
    Bind(list_ident_all, KeyCode_T, KeyCode_Shift);
    Bind(list_all, KeyCode_F, KeyCode_Control);
    Bind(list_all_substr, KeyCode_F, KeyCode_Alt);
    Bind(list_all_sel, KeyCode_F, KeyCode_Control, KeyCode_Shift);
    
    Bind(new_line_below, KeyCode_O);
    Bind(new_line_above, KeyCode_O, KeyCode_Shift);
    
    Bind(buf_switch, KeyCode_B);
    Bind(buf_open, KeyCode_B, KeyCode_Control);
    Bind(buf_kill, KeyCode_B, KeyCode_Shift);
    Bind(buf_open_other, KeyCode_B, KeyCode_Alt);
    Bind(buf_new, KeyCode_B, KeyCode_Control, KeyCode_Shift);
    
    Bind(panel_switch, KeyCode_P);
    Bind(panel_swap, KeyCode_P, KeyCode_Shift);
    Bind(panel_dup, KeyCode_P, KeyCode_Alt);
    
    Bind(replace_in_range, KeyCode_R);
    Bind(replace_in_buffer, KeyCode_R, KeyCode_Shift);
    Bind(replace_in_all_buffers, KeyCode_R, KeyCode_Control, KeyCode_Shift);
    
    Bind(query_replace, KeyCode_Q);
    Bind(query_replace_identifier, KeyCode_Q, KeyCode_Shift);
    Bind(query_replace_selection, KeyCode_Q, KeyCode_Control);
    
    Bind(build, KeyCode_M, KeyCode_Alt);
    Bind(build_open, KeyCode_M);
    Bind(build_close, KeyCode_M, KeyCode_Shift);
    
    Bind(fkey_cmd, KeyCode_F1);
    Bind(fkey_cmd, KeyCode_F2);
    Bind(fkey_cmd, KeyCode_F3);
    Bind(fkey_cmd, KeyCode_F4);
    
    Bind(comment_toggle, KeyCode_Semicolon, KeyCode_Control);
    Bind(delete_line, KeyCode_D, KeyCode_Shift);
    
    // Insert
    SelectMap(mapid_insert);
    ParentMap(mapid_shared);
    BindTextInput(write_text_and_auto_indent);
    
    Bind(complete, KeyCode_Tab);
    Bind(complete_drop_down, KeyCode_Tab, KeyCode_Shift);
    
    Bind(open_long_braces, KeyCode_LeftBracket, KeyCode_Control);
    Bind(open_long_braces_semicolon, KeyCode_LeftBracket, KeyCode_Alt);
    Bind(open_long_braces_break, KeyCode_LeftBracket, KeyCode_Control, KeyCode_Shift);
    Bind(write_todo, KeyCode_T, KeyCode_Alt);
    Bind(write_note, KeyCode_N, KeyCode_Alt);
    
    // Delete
    SelectMap(mapid_delete);
    ParentMap(mapid_normal);
    Bind(switch_mode_normal, KeyCode_Escape);
    Bind(modal_delete_line, KeyCode_D);
    Bind(modal_delete_bol, KeyCode_H, KeyCode_Control);
    Bind(modal_delete_eol, KeyCode_L, KeyCode_Control);
    Bind(modal_delete_white_left, KeyCode_H, KeyCode_Shift);
    Bind(modal_delete_white_right, KeyCode_L, KeyCode_Shift);
    Bind(modal_delete_token_left, KeyCode_H);
    Bind(modal_delete_token_right, KeyCode_L);
    
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
