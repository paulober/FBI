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
#include "resources.h"
#include "section.h"

static list_item sd = {"SD", COLOR_TEXT, files_open_sd};
static list_item ctr_nand = {"CTR NAND", COLOR_TEXT, files_open_ctr_nand};
static list_item twl_nand = {"TWL NAND", COLOR_TEXT, files_open_twl_nand};
static list_item twl_photo = {"TWL Photo", COLOR_TEXT, files_open_twl_photo};
static list_item twl_sound = {"TWL Sound", COLOR_TEXT, files_open_twl_sound};
static list_item dump_nand = {"Dump NAND", COLOR_TEXT, dumpnand_open};
static list_item titles = {"Titles", COLOR_TEXT, titles_open};
static list_item pending_titles = {"Pending Titles", COLOR_TEXT, pendingtitles_open};
static list_item tickets = {"Tickets", COLOR_TEXT, tickets_open};
static list_item ext_save_data = {"Ext Save Data", COLOR_TEXT, extsavedata_open};
static list_item system_save_data = {"System Save Data", COLOR_TEXT, systemsavedata_open};
static list_item remote_install = {"Remote Install", COLOR_TEXT, remoteinstall_open};
static list_item update = {"Update", COLOR_TEXT, update_open};

static void mainmenu_draw_top(ui_view *view, void *data, float x1, float y1, float x2, float y2, list_item *selected)
{
    u32 logoWidth;
    u32 logoHeight;
    screen_get_texture_size(&logoWidth, &logoHeight, TEXTURE_LOGO);

    float logoX = x1 + (x2 - x1 - logoWidth) / 2;
    float logoY = y1 + (y2 - y1 - logoHeight) / 2;
    screen_draw_texture(TEXTURE_LOGO, logoX, logoY, logoWidth, logoHeight);
}

static void mainmenu_update(ui_view *view, void *data, linked_list *items, list_item *selected, bool selectedTouched)
{
    if (hidKeysDown() & KEY_START)
    {
        ui_pop();
        list_destroy(view);

        return;
    }

    if (selected != NULL && (selectedTouched || hidKeysDown() & KEY_A) && selected->data != NULL)
    {
        ((void (*)())selected->data)();
        return;
    }

    if (linked_list_size(items) == 0)
    {
        linked_list_add(items, &sd);
        linked_list_add(items, &ctr_nand);
        linked_list_add(items, &twl_nand);
        linked_list_add(items, &twl_photo);
        linked_list_add(items, &twl_sound);
        linked_list_add(items, &dump_nand);
        linked_list_add(items, &titles);
        linked_list_add(items, &pending_titles);
        linked_list_add(items, &tickets);
        linked_list_add(items, &ext_save_data);
        linked_list_add(items, &system_save_data);
        linked_list_add(items, &remote_install);
        linked_list_add(items, &update);
    }
}

void mainmenu_open()
{
    resources_load();

    list_display("Main Menu", "A: Select, START: Exit", NULL, mainmenu_update, mainmenu_draw_top);
}
