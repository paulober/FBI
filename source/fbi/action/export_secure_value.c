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

static void action_export_secure_value_update(ui_view *view, void *data, float *progress, char *text)
{
    title_info *info = (title_info *)data;

    Result res = 0;

    bool exists = false;
    u64 value = 0;
    if (R_SUCCEEDED(res = FSUSER_GetSaveDataSecureValue(&exists, &value, SECUREVALUE_SLOT_SD, (u32)((info->titleId >> 8) & 0xFFFFF), (u8)(info->titleId & 0xFF))))
    {
        if (!exists)
        {
            ui_pop();
            info_destroy(view);

            prompt_display_notify("Failure", "Secure value not set.", COLOR_TEXT, info, task_draw_title_info, NULL);

            return;
        }

        FS_Archive sdmcArchive = 0;
        if (R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""))))
        {
            if (R_SUCCEEDED(res = fs_ensure_dir(sdmcArchive, "/fbi/")) && R_SUCCEEDED(res = fs_ensure_dir(sdmcArchive, "/fbi/securevalue/")))
            {
                char pathBuf[64];
                snprintf(pathBuf, 64, "/fbi/securevalue/%016llX.dat", info->titleId);

                FS_Path *fsPath = fs_make_path_utf8(pathBuf);
                if (fsPath != NULL)
                {
                    Handle fileHandle = 0;
                    if (R_SUCCEEDED(res = FSUSER_OpenFile(&fileHandle, sdmcArchive, *fsPath, FS_OPEN_WRITE | FS_OPEN_CREATE, 0)))
                    {
                        u32 bytesWritten = 0;
                        res = FSFILE_Write(fileHandle, &bytesWritten, 0, &value, sizeof(u64), FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
                        FSFILE_Close(fileHandle);
                    }

                    fs_free_path_utf8(fsPath);
                }
                else
                {
                    res = R_APP_OUT_OF_MEMORY;
                }
            }

            FSUSER_CloseArchive(sdmcArchive);
        }
    }

    ui_pop();
    info_destroy(view);

    if (R_SUCCEEDED(res))
    {
        prompt_display_notify("Success", "Secure value exported.", COLOR_TEXT, info, task_draw_title_info, NULL);
    }
    else
    {
        error_display_res(info, task_draw_title_info, res, "Failed to export secure value.");
    }
}

static void action_export_secure_value_onresponse(ui_view *view, void *data, u32 response)
{
    if (response == PROMPT_YES)
    {
        info_display("Exporting Secure Value", "", false, data, action_export_secure_value_update, task_draw_title_info);
    }
}

void action_export_secure_value(linked_list *items, list_item *selected)
{
    prompt_display_yes_no("Confirmation", "Export the secure value of the selected title?", COLOR_TEXT, selected->data, task_draw_title_info, action_export_secure_value_onresponse);
}
