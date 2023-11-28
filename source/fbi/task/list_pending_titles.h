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

typedef struct pending_title_info_s
{
    FS_MediaType mediaType;
    u64 titleId;
    u16 version;
} pending_title_info;

typedef struct populate_pending_titles_data_s
{
    linked_list *items;

    volatile bool finished;
    Result result;
    Handle cancelEvent;
} populate_pending_titles_data;

void task_free_pending_title(list_item *item);
void task_clear_pending_titles(linked_list *items);
Result task_populate_pending_titles(populate_pending_titles_data *data);
