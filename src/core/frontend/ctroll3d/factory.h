// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <string>
#include "core/frontend/ctroll3d/interface.h"

namespace CTroll3D {

class CTroll3DFactory {
public:
    virtual ~CTroll3DFactory();

    /**
     * Creates a CTroll3D object based on the ip address string.
     * @param address IP address of the remote CTroll3D input device.
     * @returns a unique_ptr to the created CTroll3D object.
     */
    virtual std::unique_ptr<CTroll3DInterface> Create() = 0;
};

/**
 * Registers an external CTroll3D factory.
 * @param name Identifier of the CTroll3D factory.
 * @param factory CTroll3D factory to register.
 */
void RegisterFactory(const std::string& name, std::unique_ptr<CTroll3DFactory> factory);

/**
 * Creates a CTroll3D from the factory.
 * @param name Identifier of the CTroll3D factory.
 * @param address IP address of the remote CTroll3D input device.
 */
std::unique_ptr<CTroll3DInterface> CreateCTroll3D(const std::string& name);

} // namespace CTroll3D
