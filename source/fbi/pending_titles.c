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
#include <stdio.h>

#include <3ds.h>

#include "../core/core.h"
#include "action/action.h"
#include "resources.h"
#include "section.h"
#include "task/ui_task.h"

static list_item delete_pending_title = {"Delete Pending Title", COLOR_TEXT, action_delete_pending_title};
static list_item delete_all_pending_titles = {"Delete All Pending Titles", COLOR_TEXT, action_delete_all_pending_titles};

typedef struct
{
    populate_pending_titles_data populateData;

    bool populated;
} pendingtitles_data;

typedef struct
{
    linked_list *items;
    list_item *selected;
} pendingtitles_action_data;

static void pendingtitles_action_draw_top(ui_view *view, void *data, float x1, float y1, float x2, float y2, list_item *selected)
{
    task_draw_pending_title_info(view, ((pendingtitles_action_data *)data)->selected->data, x1, y1, x2, y2);
}

static void pendingtitles_action_update(ui_view *view, void *data, linked_list *items, list_item *selected, bool selectedTouched)
{
    pendingtitles_action_data *actionData = (pendingtitles_action_data *)data;

    if (hidKeysDown() & KEY_B)
    {
        ui_pop();
        list_destroy(view);

        free(data);

        return;
    }

    if (selected != NULL && selected->data != NULL && (selectedTouched || (hidKeysDown() & KEY_A)))
    {
        void (*action)(linked_list *, list_item *) = (void (*)(linked_list *, list_item *))selected->data;

        ui_pop();
        list_destroy(view);

        action(actionData->items, actionData->selected);

        free(data);

        return;
    }

    if (linked_list_size(items) == 0)
    {
        linked_list_add(items, &delete_pending_title);
        linked_list_add(items, &delete_all_pending_titles);
    }
}

static void pendingtitles_action_open(linked_list *items, list_item *selected)
{
    pendingtitles_action_data *data = (pendingtitles_action_data *)calloc(1, sizeof(pendingtitles_action_data));
    if (data == NULL)
    {
        error_display(NULL, NULL, "Failed to allocate pending titles action data.");

        return;
    }

    data->items = items;
    data->selected = selected;

    list_display("Pending Title Action", "A: Select, B: Return", data, pendingtitles_action_update, pendingtitles_action_draw_top);
}

static void pendingtitles_draw_top(ui_view *view, void *data, float x1, float y1, float x2, float y2, list_item *selected)
{
    if (selected != NULL && selected->data != NULL)
    {
        task_draw_pending_title_info(view, selected->data, x1, y1, x2, y2);
    }
}

static void pendingtitles_update(ui_view *view, void *data, linked_list *items, list_item *selected, bool selectedTouched)
{
    pendingtitles_data *listData = (pendingtitles_data *)data;

    if (hidKeysDown() & KEY_B)
    {
        if (!listData->populateData.finished)
        {
            svcSignalEvent(listData->populateData.cancelEvent);
            while (!listData->populateData.finished)
            {
                svcSleepThread(1000000);
            }
        }

        ui_pop();

        task_clear_pending_titles(items);
        list_destroy(view);

        free(listData);
        return;
    }

    if (!listData->populated || (hidKeysDown() & KEY_X))
    {
        if (!listData->populateData.finished)
        {
            svcSignalEvent(listData->populateData.cancelEvent);
            while (!listData->populateData.finished)
            {
                svcSleepThread(1000000);
            }
        }

        listData->populateData.items = items;
        Result res = task_populate_pending_titles(&listData->populateData);
        if (R_FAILED(res))
        {
            error_display_res(NULL, NULL, res, "Failed to initiate pending title list population.");
        }

        listData->populated = true;
    }

    if (listData->populateData.finished && R_FAILED(listData->populateData.result))
    {
        error_display_res(NULL, NULL, listData->populateData.result, "Failed to populate pending title list.");

        listData->populateData.result = 0;
    }

    if (selected != NULL && selected->data != NULL && (selectedTouched || (hidKeysDown() & KEY_A)))
    {
        pendingtitles_action_open(items, selected);
        return;
    }
}

void pendingtitles_open()
{
    pendingtitles_data *data = (pendingtitles_data *)calloc(1, sizeof(pendingtitles_data));
    if (data == NULL)
    {
        error_display(NULL, NULL, "Failed to allocate pending titles data.");

        return;
    }

    data->populateData.finished = true;

    list_display("Pending Titles", "A: Select, B: Return, X: Refresh", data, pendingtitles_update, pendingtitles_draw_top);
}
