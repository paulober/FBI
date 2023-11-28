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

#include <stdio.h>

#include <3ds.h>

#include "../string_util.h"
#include "smdh.h"

#define SMDH_NUM_REGIONS 7
#define SMDH_ALL_REGIONS 0x7F

static const char *smdh_region_strings[SMDH_NUM_REGIONS] = {
    "Japan",
    "North America",
    "Europe",
    "Australia",
    "China",
    "Korea",
    "Taiwan"};

void smdh_region_to_string(char *out, u32 region, size_t size)
{
    if (out == NULL)
    {
        return;
    }

    if (region == 0)
    {
        snprintf(out, size, "Unknown");
    }
    else if ((region & SMDH_ALL_REGIONS) == SMDH_ALL_REGIONS)
    {
        snprintf(out, size, "Region Free");
    }
    else
    {
        size_t pos = 0;

        for (u32 i = 0; i < SMDH_NUM_REGIONS; i++)
        {
            if (region & (1 << i))
            {
                if (pos > 0)
                {
                    pos += snprintf(out + pos, size - pos, ", ");
                }

                pos += snprintf(out + pos, size - pos, smdh_region_strings[i]);
            }
        }
    }
}

static CFG_Language region_default_language[] = {
    CFG_LANGUAGE_JP,
    CFG_LANGUAGE_EN,
    CFG_LANGUAGE_EN,
    CFG_LANGUAGE_EN,
    CFG_LANGUAGE_ZH,
    CFG_LANGUAGE_KO,
    CFG_LANGUAGE_ZH};

SMDH_title *smdh_select_title(SMDH *smdh)
{
    char shortDescription[0x100] = {'\0'};

    CFG_Language systemLanguage;
    if (R_SUCCEEDED(CFGU_GetSystemLanguage((u8 *)&systemLanguage)))
    {
        utf16_to_utf8((uint8_t *)shortDescription, smdh->titles[systemLanguage].shortDescription, sizeof(shortDescription) - 1);
    }

    if (string_is_empty(shortDescription))
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

    return &smdh->titles[systemLanguage];
}
