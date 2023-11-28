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

#include <3ds.h>

Result http_download_callback(const char *url, u32 bufferSize, void *userData, Result (*callback)(void *userData, void *buffer, size_t size),
                              Result (*checkRunning)(void *userData),
                              Result (*progress)(void *userData, u64 total, u64 curr));
Result http_download_buffer(const char *url, u32 *downloadedSize, void *buf, size_t size);
Result http_download_json(const char *url, json_t **json, size_t maxSize);
Result http_download_seed(u64 titleId);
