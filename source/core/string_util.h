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

bool string_is_empty(const char *str);
void string_copy(char *dst, const char *src, size_t size);

void string_get_file_name(char *out, const char *file, u32 size);
void string_escape_file_name(char *out, const char *file, size_t size);
void string_get_path_file(char *out, const char *path, u32 size);
void string_get_parent_path(char *out, const char *path, u32 size);
