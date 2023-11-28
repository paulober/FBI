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

typedef enum capture_cam_camera_e {
    CAMERA_OUTER,
    CAMERA_INNER
} capture_cam_camera;

typedef struct capture_cam_data_s {
    u16* buffer;
    s16 width;
    s16 height;
    capture_cam_camera camera;

    Handle mutex;

    volatile bool finished;
    Result result;
    Handle cancelEvent;
} capture_cam_data;

Result task_capture_cam(capture_cam_data* data);