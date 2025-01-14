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
#include <string.h>

#include <3ds.h>

#include "clipboard.h"
#include "core_fs.h"
#include "string_util.h"

static bool clipboard_has = false;
static bool clipboard_contents_only;

static FS_Archive clipboard_archive;
static char clipboard_path[FILE_PATH_MAX];

bool clipboard_has_contents()
{
    return clipboard_has;
}

FS_Archive clipboard_get_archive()
{
    return clipboard_archive;
}

char *clipboard_get_path()
{
    return clipboard_path;
}

bool clipboard_is_contents_only()
{
    return clipboard_contents_only;
}

Result clipboard_set_contents(FS_Archive archive, const char *path, bool contentsOnly)
{
    clipboard_clear();

    Result res = 0;
    if (R_SUCCEEDED(res = fs_ref_archive(archive)))
    {
        clipboard_has = true;
        clipboard_contents_only = contentsOnly;

        clipboard_archive = archive;
        string_copy(clipboard_path, path, FILE_PATH_MAX);
    }

    return res;
}

void clipboard_clear()
{
    if (clipboard_archive != 0)
    {
        fs_close_archive(clipboard_archive);
    }

    clipboard_has = false;
    clipboard_contents_only = false;

    clipboard_archive = 0;
    memset(clipboard_path, '\0', FILE_PATH_MAX);
}
