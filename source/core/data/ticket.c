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

#include "ticket.h"
#include "../core.h"

#define NUM_SIG_TYPES 6
static u32 sigSizes[NUM_SIG_TYPES] = {0x240, 0x140, 0x80, 0x240, 0x140, 0x80};

Result ticket_get_title_id(u64* titleId, u8* ticket, size_t size) {
    if(ticket == NULL) {
        return R_APP_INVALID_ARGUMENT;
    }

    if(size < 4) {
        return R_APP_BAD_DATA;
    }

    u8 sigType = ticket[0x03];
    if(sigType >= NUM_SIG_TYPES) {
        return R_APP_BAD_DATA;
    }

    u32 offset = sigSizes[sigType] + 0x9C;
    if(offset + sizeof(u64) > size) {
        return R_APP_BAD_DATA;
    }

    if(titleId != NULL) {
        *titleId = __builtin_bswap64(*(u64*) &ticket[offset]);
    }

    return 0;
}