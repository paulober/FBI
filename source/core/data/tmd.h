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

Result tmd_get_title_id(u64 *titleId, u8 *tmd, size_t size);
Result tmd_get_content_count(u16 *contentCount, u8 *tmd, size_t size);
Result tmd_get_content_id(u32 *id, u8 *tmd, size_t size, u32 num);
Result tmd_get_content_index(u16 *index, u8 *tmd, size_t size, u32 num);
