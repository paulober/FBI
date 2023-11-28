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

void mainmenu_open();

void dumpnand_open();
void extsavedata_open();
void files_open(FS_ArchiveID archiveId, FS_Path archivePath);
void files_open_sd();
void files_open_ctr_nand();
void files_open_twl_nand();
void files_open_twl_photo();
void files_open_twl_sound();
void pendingtitles_open();
void remoteinstall_open();
void systemsavedata_open();
void tickets_open();
void titles_open();
void update_open();