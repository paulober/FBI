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

#include "ui.h"
#include "ui_error.h"
#include "ui_kbd.h"

typedef struct
{
    const char *hint;
    const char *initialText;
    SwkbdType type;
    u32 features;
    SwkbdValidInput validation;
    u32 maxSize;

    char *response;

    void *data;
    void (*onResponse)(ui_view *view, void *data, SwkbdButton button, const char *response);
} kbd_data;

static void kbd_update(ui_view *view, void *data, float bx1, float by1, float bx2, float by2)
{
    kbd_data *kbdData = (kbd_data *)data;

    SwkbdState swkbd;
    swkbdInit(&swkbd, kbdData->type, 2, kbdData->maxSize < 65000 ? (int)kbdData->maxSize : 65000);
    swkbdSetHintText(&swkbd, kbdData->hint);
    swkbdSetInitialText(&swkbd, kbdData->initialText);
    swkbdSetFeatures(&swkbd, kbdData->features);
    swkbdSetValidation(&swkbd, kbdData->validation, 0, 0);
    SwkbdButton button = swkbdInputText(&swkbd, kbdData->response, kbdData->maxSize);

    ui_pop();

    if (kbdData->onResponse != NULL)
    {
        kbdData->onResponse(view, kbdData->data, button, kbdData->response);
    }

    free(kbdData->response);
    free(kbdData);
    ui_destroy(view);
}

ui_view *kbd_display(const char *hint, const char *initialText, SwkbdType type, u32 features, SwkbdValidInput validation, u32 maxSize, void *data, void (*onResponse)(ui_view *view, void *data, SwkbdButton button, const char *response))
{
    kbd_data *kbdData = (kbd_data *)calloc(1, sizeof(kbd_data));
    if (kbdData == NULL)
    {
        error_display(NULL, NULL, "Failed to allocate keyboard data.");

        return NULL;
    }

    kbdData->hint = hint;
    kbdData->initialText = initialText;
    kbdData->type = type;
    kbdData->features = features;
    kbdData->validation = validation;
    kbdData->maxSize = maxSize;

    kbdData->response = (char *)calloc(1, maxSize);
    if (kbdData->response == NULL)
    {
        error_display(NULL, NULL, "Failed to allocate keyboard response buffer.");

        free(kbdData);
        return NULL;
    }

    kbdData->data = data;
    kbdData->onResponse = onResponse;

    ui_view *view = ui_create();
    view->name = "";
    view->info = "";
    view->data = kbdData;
    view->update = kbd_update;
    view->drawTop = NULL;
    view->drawBottom = NULL;
    ui_push(view);

    return view;
}
