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

typedef struct system_save_data_info_s {
    u32 systemSaveDataId;
} system_save_data_info;

typedef struct populate_system_save_data_data_s {
    linked_list* items;

    volatile bool finished;
    Result result;
    Handle cancelEvent;
} populate_system_save_data_data;

void task_free_system_save_data(list_item* item);
void task_clear_system_save_data(linked_list* items);
Result task_populate_system_save_data(populate_system_save_data_data* data);