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
#pragma once

#include "ui.h"

typedef struct ui_view_s ui_view;

ui_view *error_display(void *data, void (*drawTop)(ui_view *view, void *data, float x1, float y1, float x2, float y2), const char *text, ...);
ui_view *error_display_res(void *data, void (*drawTop)(ui_view *view, void *data, float x1, float y1, float x2, float y2), Result result, const char *text, ...);
ui_view *error_display_errno(void *data, void (*drawTop)(ui_view *view, void *data, float x1, float y1, float x2, float y2), int err, const char *text, ...);
