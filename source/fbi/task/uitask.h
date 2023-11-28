/*
 * Copyright (c) 2015-2019 Steveice10
 * All rights reserved.
 *
 * This source code is licensed under the MIT License found in the
 * LICENSE-MIT file in the root directory of this source tree.
 *
 * Copyright (c) 2023 paulober
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

typedef struct ui_view_s ui_view;

typedef struct meta_info_s {
    char shortDescription[0x100];
    char longDescription[0x200];
    char publisher[0x100];
    u32 region;
    u32 texture;
} meta_info;

void task_draw_meta_info(ui_view* view, void* data, float x1, float y1, float x2, float y2);
void task_draw_ext_save_data_info(ui_view* view, void* data, float x1, float y1, float x2, float y2);
void task_draw_file_info(ui_view* view, void* data, float x1, float y1, float x2, float y2);
void task_draw_pending_title_info(ui_view* view, void* data, float x1, float y1, float x2, float y2);
void task_draw_system_save_data_info(ui_view* view, void* data, float x1, float y1, float x2, float y2);
void task_draw_ticket_info(ui_view* view, void* data, float x1, float y1, float x2, float y2);
void task_draw_title_info(ui_view* view, void* data, float x1, float y1, float x2, float y2);

#include "listextsavedata.h"
#include "listpendingtitles.h"
#include "listsystemsavedata.h"
#include "listtickets.h"
#include "listtitles.h"
#include "listfiles.h"