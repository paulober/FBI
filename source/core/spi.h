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

Result spi_init_card();
Result spi_deinit_card();
Result spi_get_save_size(u32* size);
Result spi_read_save(u32* bytesRead, void* data, u32 offset, u32 size);
Result spi_write_save(u32* bytesWritten, void* data, u32 offset, u32 size);