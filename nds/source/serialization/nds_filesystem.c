#include "debug/nds_debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "process/process.h"
#include "process/process_manager.h"
#include "serialization/serialization_request.h"
#include "timer.h"
#include <fat.h>
#include <stdio.h>
#include <stdlib.h>
#include <nds_defines.h>

PLATFORM_File_System_Context _NDS_file_system_context;

void m_NDS_process__serialization(
        Process *p_this_process,
        Game *p_game);

///
/// For the NDS, PLATFORM_file_system_context is
/// symbiotic with PLATFORM_audio_context. This is
/// because of how PLATFORM_audio_context needs to
/// stream audio from SLOT_1 while the PLATFORM_file_system_context
/// needs to write data to SLOT_1 in real time.
///
/// To accomplish this, write data is stored in a queue
/// and waits for a write window. Audio is streamed in
/// roughly every 2 seconds, so the write window
/// is every second and a half for a maximum of 50kb~.
///
/// TODO:   this write window is determined from testing
///         SLOT_1 cards on hand. Further work is needed
///         based on the write speed of other cards.
///

void PLATFORM_initialize_file_system_context(
        Game *p_game,
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context) {
#ifndef NDEBUG
    if (!p_PLATFORM_file_system_context) {
        debug_abort("NDS::PLATFORM_initialize_file_system_context, p_PLATFORM_file_system_context is null.");
        return;
    }
#endif
    for (Index__u16 index_of__serialization_request = 0;
            index_of__serialization_request
            < FILE_SYSTEM_CONTEXT__QUANTITY_OF__SERIALIZAITON_REQUESTS;
            index_of__serialization_request++) {
        initialize_serialization_request_as__uninitalized(
                &p_PLATFORM_file_system_context
                ->serialization_requests[index_of__serialization_request]);
    }

    if (!fatInitDefault()) {
        debug_abort("NDS::PLATFORM_initialize_file_system_context, failed to initialize fatInitDefault(...)");
        return;
    }

    Process *p_serialization_process =
        allocate_process_forcefully_in__process_manager(
                get_p_process_manager_from__game(p_game),
                p_game);
    register_process_as__critical_in__process_manager(
            get_p_process_manager_from__game(p_game), 
            p_game, 
            p_serialization_process);
    if (!p_serialization_process) {
        debug_abort("NDS::PLATFORM_initialize_file_system_context, failed to allocate p_serialization_process.");
        return;
    }
    p_serialization_process
        ->m_process_run__handler =
        m_NDS_process__serialization;

    p_PLATFORM_file_system_context
        ->p_serialization_process = p_serialization_process;
    p_serialization_process->p_process_data = 
        p_PLATFORM_file_system_context;

    p_PLATFORM_file_system_context
        ->f_audio_stream__callback = 0;
    p_PLATFORM_file_system_context
        ->index_of__next_serialization_request = 0;

    initialize_timer_u8(
            &p_PLATFORM_file_system_context
            ->timer__audio_stream_u8,
            FILE_SYSTEM_CONTEXT__AUDIO_STREAM__TIME_WINDOW);
}

Serialization_Request *PLATFORM_allocate_serialization_request(
        PLATFORM_File_System_Context *p_PLATOFRM_file_system_context) {
    if (p_PLATOFRM_file_system_context
            ->index_of__next_serialization_request
            >= FILE_SYSTEM_CONTEXT__QUANTITY_OF__SERIALIZAITON_REQUESTS) {
        debug_error("NDS::PLATFORM_allocate_serialization_request, failed to find available request slot.");
        return 0;
    }

    // TODO:    support retaining requests
    //          currently we only support fire and forget
    //          and this logic below reflects that.
    Serialization_Request *p_serialization_request =
        &p_PLATOFRM_file_system_context
        ->serialization_requests[
            p_PLATOFRM_file_system_context
                ->index_of__next_serialization_request++];

    initialize_serialization_request_as__uninitalized(
            p_serialization_request);
    set_serialization_request_as__active(
            p_serialization_request);
    return p_serialization_request;
}

enum PLATFORM_Open_File_Error PLATFORM_open_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        const char *p_path,
        const char *p_flags,
        Serialization_Request *p_serialization_request) {
    // TODO: validate path
    FILE *p_file = fopen(p_path, p_flags);

    if (!p_file) {
        initialize_serialization_request_as__uninitalized(
                p_serialization_request);
        return PLATFORM_Open_File_Error__File_Not_Found;
    }

    p_serialization_request
        ->p_file_handler = p_file;

    return PLATFORM_Open_File_Error__None;
}

void PLATFORM_close_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        Serialization_Request *p_serialization_request) {
    FILE *p_file = (FILE*)p_serialization_request->p_file_handler;

    initialize_serialization_request_as__uninitalized(
            p_serialization_request);

    if (!p_file)
        return;

    fclose(p_file);
}

enum PLATFORM_Write_File_Error PLATFORM_write_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        u8 *p_source,
        Quantity__u32 length_of__data,
        Quantity__u32 quantity_of__writes,
        void *p_file_handler) {
#ifndef NDEBUG
    if (!p_file_handler) {
        debug_abort("NDS::PLATFORM_write_file, p_file_handler is null.");
        return PLATFORM_Write_File_Error__Unknown;
    }
#endif

    FILE *p_file = p_file_handler;
    fwrite(
            p_source,
            length_of__data,
            quantity_of__writes,
            p_file);
}

enum PLATFORM_Read_File_Error PLATFORM_read_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        u8 *p_destination,
        Quantity__u32 *p_length_of__data_to_read,
        Quantity__u32 quantity_of__reads,
        void *p_file_handler) {
#ifndef NDEBUG
    if (!p_file_handler) {
        debug_abort("NDS::PLATFORM_read_file, p_file_handler is null.");
        return PLATFORM_Read_File_Error__Unknown;
    }
#endif

    FILE *p_file = p_file_handler;
    *p_length_of__data_to_read = 
        fread(
            p_destination,
            *p_length_of__data_to_read,
            quantity_of__reads,
            p_file);
}

void m_NDS_process__serialization(
        Process *p_this_process,
        Game *p_game) {
    return;
    PLATFORM_File_System_Context *p_PLATFORM_file_system_context =
        (PLATFORM_File_System_Context*)p_this_process->p_process_data;

#ifndef NDEBUG
    if (!p_PLATFORM_file_system_context) {
        debug_error("m_NDS_process__serialization, p_PLATOFRM_file_system_context is null.");
        fail_process(p_this_process);
        return;
    }
#endif

    /// Block Serialization for audio stream.
    if (p_PLATFORM_file_system_context
            ->f_audio_stream__callback) {
        Timer__u8 *p_timer = 
            &p_PLATFORM_file_system_context
            ->timer__audio_stream_u8;
        loop_timer_u8(p_timer);
        if (get_time_elapsed_from__timer_u8(p_timer)
                >= FILE_SYSTEM_CONTEXT__AUDIO_STREAM__TIME_CYCLE) {
            p_PLATFORM_file_system_context
                ->f_audio_stream__callback();
            return;
        }
        if (get_time_elapsed_from__timer_u8(p_timer)
                >= FILE_SYSTEM_CONTEXT__AUDIO_STREAM__TIME_WINDOW) {
            return;
        }
    }

    /// Handle serialization requests
    for (Index__u16 index_of__serialization_request = 0;
            index_of__serialization_request
            < FILE_SYSTEM_CONTEXT__QUANTITY_OF__SERIALIZAITON_REQUESTS;
            index_of__serialization_request++) {
        Serialization_Request *p_serialization_request =
            &p_PLATFORM_file_system_context->serialization_requests[
                index_of__serialization_request];

        if (!is_serialization_request__active(
                    p_serialization_request)) {
            if (index_of__serialization_request > 0
                    && p_PLATFORM_file_system_context
                        ->f_audio_stream__callback) {
                p_PLATFORM_file_system_context
                    ->f_audio_stream__callback();
            }
            break;
        }
        if (is_serialization_request__using_serializer(
                    p_serialization_request)) {
            if (is_serialization_request__reading(
                        p_serialization_request)) {
                p_serialization_request
                    ->p_serializer
                    ->m_deserialize_handler(
                            p_game,
                            p_serialization_request,
                            p_serialization_request
                            ->p_serializer);
            } else {
                p_serialization_request
                    ->p_serializer
                    ->m_serialize_handler(
                            p_game,
                            p_serialization_request,
                            p_serialization_request
                            ->p_serializer);
            }
        } else {
            if (is_serialization_request__reading(
                        p_serialization_request)) {
                PLATFORM_read_file(
                        p_PLATFORM_file_system_context,
                        p_serialization_request
                        ->p_buffer,
                        &p_serialization_request
                        ->size_of__serialization,
                        p_serialization_request
                        ->quantity_of__writes_or_reads,
                        p_serialization_request
                        ->p_file_handler);
            } else {
                PLATFORM_write_file(
                        p_PLATFORM_file_system_context, 
                        p_serialization_request
                        ->p_buffer, 
                        p_serialization_request
                        ->size_of__serialization, 
                        p_serialization_request
                        ->quantity_of__writes_or_reads,
                        p_serialization_request
                        ->p_file_handler);
            }
        }
    }

    for (Index__u16 index_of__serialization_request = 0;
            index_of__serialization_request
            < FILE_SYSTEM_CONTEXT__QUANTITY_OF__SERIALIZAITON_REQUESTS;
            index_of__serialization_request++) {
        Serialization_Request *p_serialization_request =
            &p_PLATFORM_file_system_context->serialization_requests[
                index_of__serialization_request];
        if (!is_serialization_request__active(
                    p_serialization_request)) {
            p_PLATFORM_file_system_context
                ->index_of__next_serialization_request = 0;
            return;
        }
        if (is_serialization_request__fire_and_forget(
                    p_serialization_request)) {
            PLATFORM_close_file(
                    p_PLATFORM_file_system_context, 
                    p_serialization_request);
        }
    }
}
