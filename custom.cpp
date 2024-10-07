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

CUSTOM_COMMAND_SIG(modal_delete_word_right)
{
    delete_alpha_numeric_boundary(app);
    switch_mode_normal(app);
}

CUSTOM_COMMAND_SIG(modal_delete_word_left)
{
    backspace_alpha_numeric_boundary(app);
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
    Bind(exit_4coder, KeyCode_F4, KeyCode_Alt);
    
    // Normal
    SelectMap(mapid_normal);
    ParentMap(mapid_shared);
    Bind(switch_mode_insert, KeyCode_Tab);
    Bind(switch_mode_delete, KeyCode_D);
    
    // Insert
    SelectMap(mapid_insert);
    ParentMap(mapid_shared);
    BindTextInput(write_text_and_auto_indent);
    Bind(backspace_char, KeyCode_Backspace);
    
    // Delete
    SelectMap(mapid_delete);
    Bind(switch_mode_normal, KeyCode_Escape);
    Bind(modal_delete_word_left, KeyCode_Left);
    Bind(modal_delete_word_right, KeyCode_Right);
    
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
