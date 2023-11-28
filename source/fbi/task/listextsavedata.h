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

typedef struct linked_list_s linked_list;
typedef struct list_item_s list_item;

typedef struct ext_save_data_info_s {
    FS_MediaType mediaType;
    u64 extSaveDataId;
    bool shared;
    bool hasMeta;
    meta_info meta;
} ext_save_data_info;

typedef struct populate_ext_save_data_data_s {
    linked_list* items;

    void* userData;
    bool (*filter)(void* data, u64 extSaveDataId, FS_MediaType mediaType);
    int (*compare)(void* data, const void* p1, const void* p2);

    volatile bool finished;
    Result result;
    Handle cancelEvent;
} populate_ext_save_data_data;

void task_free_ext_save_data(list_item* item);
void task_clear_ext_save_data(linked_list* items);
Result task_populate_ext_save_data(populate_ext_save_data_data* data);