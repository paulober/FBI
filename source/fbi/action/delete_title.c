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

#include <malloc.h>

#include <3ds.h>

#include "../../core/core.h"
#include "../resources.h"
#include "../task/ui_task.h"
#include "action.h"

typedef struct
{
    linked_list *items;
    list_item *selected;
    bool ticket;
} delete_title_data;

static void action_delete_title_draw_top(ui_view *view, void *data, float x1, float y1, float x2, float y2)
{
    task_draw_title_info(view, ((delete_title_data *)data)->selected->data, x1, y1, x2, y2);
}

static void action_delete_title_update(ui_view *view, void *data, float *progress, char *text)
{
    delete_title_data *deleteData = (delete_title_data *)data;

    title_info *info = (title_info *)deleteData->selected->data;

    Result res = 0;

    if (R_SUCCEEDED(res = AM_DeleteTitle(info->mediaType, info->titleId)) && deleteData->ticket)
    {
        res = AM_DeleteTicket(info->titleId);
    }

    ui_pop();
    info_destroy(view);

    if (R_FAILED(res))
    {
        error_display_res(info, task_draw_title_info, res, "Failed to delete title.");
    }
    else
    {
        linked_list_remove(deleteData->items, deleteData->selected);
        task_free_title(deleteData->selected);

        prompt_display_notify("Success", "Title deleted.", COLOR_TEXT, NULL, NULL, NULL);
    }

    free(data);
}

static void action_delete_title_onresponse(ui_view *view, void *data, u32 response)
{
    if (response == PROMPT_YES)
    {
        info_display("Deleting Title", "", false, data, action_delete_title_update, action_delete_title_draw_top);
    }
    else
    {
        free(data);
    }
}

static void action_delete_title_internal(linked_list *items, list_item *selected, const char *message, bool ticket)
{
    delete_title_data *data = (delete_title_data *)calloc(1, sizeof(delete_title_data));
    if (data == NULL)
    {
        error_display(NULL, NULL, "Failed to allocate delete title data.");

        return;
    }

    data->items = items;
    data->selected = selected;
    data->ticket = ticket;

    prompt_display_yes_no("Confirmation", message, COLOR_TEXT, data, action_delete_title_draw_top, action_delete_title_onresponse);
}

void action_delete_title(linked_list *items, list_item *selected)
{
    action_delete_title_internal(items, selected, "Delete the selected title?", false);
}

void action_delete_title_ticket(linked_list *items, list_item *selected)
{
    action_delete_title_internal(items, selected, "Delete the selected title and ticket?", true);
}
