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

#include <3ds.h>

#include "../../core/core.h"
#include "../section.h"
#include "../task/ui_task.h"
#include "action.h"

void action_browse_system_save_data(linked_list *items, list_item *selected)
{
    system_save_data_info *info = (system_save_data_info *)selected->data;

    u32 path[2] = {MEDIATYPE_NAND, info->systemSaveDataId};
    files_open(ARCHIVE_SYSTEM_SAVEDATA, fs_make_path_binary(path, sizeof(path)));
}
