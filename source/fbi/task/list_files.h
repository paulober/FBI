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

#include "../action/action.h"
#include "ui_task.h"

#ifndef FILE_NAME_MAX
#define FILE_NAME_MAX 256
#define FILE_PATH_MAX 512
#endif

typedef struct linked_list_s linked_list;
typedef struct list_item_s list_item;

typedef struct cia_info_s
{
    bool loaded;

    u64 titleId;
    u16 version;
    u64 installedSize;
    bool hasMeta;
    meta_info meta;
} cia_info;

typedef struct file_info_s
{
    FS_Archive archive;
    char name[FILE_NAME_MAX];
    char path[FILE_PATH_MAX];
    u32 attributes;

    // Files only
    u64 size;
    bool isCia;
    cia_info ciaInfo;
    bool isTicket;
    ticket_info ticketInfo;
} file_info;

typedef struct populate_files_data_s
{
    linked_list *items;

    FS_Archive archive;
    char path[FILE_PATH_MAX];

    bool recursive;
    bool includeBase;
    bool meta;

    bool (*filter)(void *data, const char *name, u32 attributes);
    void *filterData;

    volatile bool finished;
    Result result;
    Handle cancelEvent;
} populate_files_data;

int task_compare_files(void *userData, const void *p1, const void *p2);
void task_free_file(list_item *item);
void task_clear_files(linked_list *items);
Result task_create_file_item(list_item **out, FS_Archive archive, const char *path, u32 attributes, bool meta);
Result task_populate_files(populate_files_data *data);
