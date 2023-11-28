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

#include "task.h"
#include "../error.h"

static bool task_quit;

static Handle task_pause_event;
static Handle task_suspend_event;

static aptHookCookie cookie;

static void task_apt_hook(APT_HookType hook, void* param) {
    switch(hook) {
        case APTHOOK_ONRESTORE:
            svcSignalEvent(task_suspend_event);
        case APTHOOK_ONWAKEUP:
            svcSignalEvent(task_pause_event);
            break;
        case APTHOOK_ONSUSPEND:
            svcClearEvent(task_suspend_event);
        case APTHOOK_ONSLEEP:
            svcClearEvent(task_pause_event);
            break;
        default:
            break;
    }
}

void task_init() {
    task_quit = false;

    Result res = 0;

    if(R_FAILED(res = svcCreateEvent(&task_pause_event, RESET_STICKY))) {
        error_panic("Failed to create task pause event: 0x%08lX", res);
        return;
    }

    if(R_FAILED(res = svcCreateEvent(&task_suspend_event, RESET_STICKY))) {
        svcCloseHandle(task_pause_event);

        error_panic("Failed to create task suspend event: 0x%08lX", res);
        return;
    }

    svcSignalEvent(task_pause_event);
    svcSignalEvent(task_suspend_event);

    aptHook(&cookie, task_apt_hook, NULL);
}

void task_exit() {
    task_quit = true;

    aptUnhook(&cookie);

    if(task_pause_event != 0) {
        svcCloseHandle(task_pause_event);
        task_pause_event = 0;
    }

    if(task_suspend_event != 0) {
        svcCloseHandle(task_suspend_event);
        task_suspend_event = 0;
    }
}

bool task_is_quit_all() {
    return task_quit;
}

Handle task_get_pause_event() {
    return task_pause_event;
}

Handle task_get_suspend_event() {
    return task_suspend_event;
}