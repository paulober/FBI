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

static void action_import_secure_value_update(ui_view *view, void *data, float *progress, char *text)
{
    title_info *info = (title_info *)data;

    char pathBuf[64];
    snprintf(pathBuf, 64, "/fbi/securevalue/%016llX.dat", info->titleId);

    Result res = 0;

    FS_Path *fsPath = fs_make_path_utf8(pathBuf);
    if (fsPath != NULL)
    {
        Handle fileHandle = 0;
        if (R_SUCCEEDED(res = FSUSER_OpenFileDirectly(&fileHandle, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""), *fsPath, FS_OPEN_READ, 0)))
        {
            u32 bytesRead = 0;
            u64 value = 0;
            if (R_SUCCEEDED(res = FSFILE_Read(fileHandle, &bytesRead, 0, &value, sizeof(u64))))
            {
                res = FSUSER_SetSaveDataSecureValue(value, SECUREVALUE_SLOT_SD, (u32)((info->titleId >> 8) & 0xFFFFF), (u8)(info->titleId & 0xFF));
            }

            FSFILE_Close(fileHandle);
        }

        fs_free_path_utf8(fsPath);
    }
    else
    {
        res = R_APP_OUT_OF_MEMORY;
    }

    ui_pop();
    info_destroy(view);

    if (R_SUCCEEDED(res))
    {
        prompt_display_notify("Success", "Secure value imported.", COLOR_TEXT, info, task_draw_title_info, NULL);
    }
    else
    {
        error_display_res(info, task_draw_title_info, res, "Failed to import secure value.");
    }
}

static void action_import_secure_value_onresponse(ui_view *view, void *data, u32 response)
{
    if (response == PROMPT_YES)
    {
        info_display("Importing Secure Value", "", false, data, action_import_secure_value_update, task_draw_title_info);
    }
}

void action_import_secure_value(linked_list *items, list_item *selected)
{
    prompt_display_yes_no("Confirmation", "Import the secure value of the selected title?", COLOR_TEXT, selected->data, task_draw_title_info, action_import_secure_value_onresponse);
}
