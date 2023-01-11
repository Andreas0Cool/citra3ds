// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"
#include "core/frontend/input.h"

#define CTROLL3D_INPUT_PORT 6542

#define CTROLL3DINFO_SZ 22
typedef struct {
    uint16_t pressedButtons;
    int16_t cPadX;
    int16_t cPadY;
    uint16_t touchX;
    uint16_t touchY;
    uint16_t accelX;
    uint16_t accelY;
    uint16_t accelZ;
    uint16_t gyroX;
    uint16_t gyroY;
    uint16_t gyroZ;
} CTroll3DInfo;


namespace CTroll3D {

class CTroll3DInterface {
public:
    virtual ~CTroll3DInterface();
    virtual void UpdateStatus(char *addr, CTroll3DInfo *info) = 0;
};


} // namespace CTroll3D
