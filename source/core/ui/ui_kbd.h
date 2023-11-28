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

typedef struct ui_view_s ui_view;

ui_view* kbd_display(const char* hint, const char* initialText, SwkbdType type, u32 features, SwkbdValidInput validation, u32 maxSize, void* data, void (*onResponse)(ui_view* view, void* data, SwkbdButton button, const char* response));
