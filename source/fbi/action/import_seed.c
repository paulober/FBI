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

#include <stdio.h>

#include <3ds.h>

#include "../../core/core.h"
#include "../resources.h"
#include "../task/ui_task.h"
#include "action.h"

static void action_import_seed_update(ui_view *view, void *data, float *progress, char *text)
{
    title_info *info = (title_info *)data;

    Result res = http_download_seed(info->titleId);

    ui_pop();
    info_destroy(view);

    if (R_SUCCEEDED(res))
    {
        prompt_display_notify("Success", "Seed imported.", COLOR_TEXT, info, task_draw_title_info, NULL);
    }
    else
    {
        error_display_res(info, task_draw_title_info, res, "Failed to import seed.");
    }
}

static void action_import_seed_onresponse(ui_view *view, void *data, u32 response)
{
    if (response == PROMPT_YES)
    {
        info_display("Importing Seed", "", false, data, action_import_seed_update, task_draw_title_info);
    }
}

void action_import_seed(linked_list *items, list_item *selected)
{
    prompt_display_yes_no("Confirmation", "Import the seed of the selected title?", COLOR_TEXT, selected->data, task_draw_title_info, action_import_seed_onresponse);
}
