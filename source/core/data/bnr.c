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

#include "../string_util.h"
#include "bnr.h"

static CFG_Language region_default_language[] = {
    CFG_LANGUAGE_JP,
    CFG_LANGUAGE_EN,
    CFG_LANGUAGE_EN,
    CFG_LANGUAGE_EN,
    CFG_LANGUAGE_ZH,
    CFG_LANGUAGE_KO,
    CFG_LANGUAGE_ZH};

u16 *bnr_select_title(BNR *bnr)
{
    char title[0x100] = {'\0'};

    CFG_Language systemLanguage;
    if (R_SUCCEEDED(CFGU_GetSystemLanguage((u8 *)&systemLanguage)))
    {
        utf16_to_utf8((uint8_t *)title, bnr->titles[systemLanguage], sizeof(title) - 1);
    }

    if (string_is_empty(title))
    {
        CFG_Region systemRegion;
        if (R_SUCCEEDED(CFGU_SecureInfoGetRegion((u8 *)&systemRegion)))
        {
            systemLanguage = region_default_language[systemRegion];
        }
        else
        {
            systemLanguage = CFG_LANGUAGE_JP;
        }
    }

    return bnr->titles[systemLanguage];
}
