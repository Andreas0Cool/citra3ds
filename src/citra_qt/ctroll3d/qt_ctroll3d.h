// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <string>
#include "core/frontend/ctroll3d/factory.h"

namespace CTroll3D {

// Base class for CTroll3D interfaces of citra_qt
class QtCTroll3D : public CTroll3DInterface {
public:
    QtCTroll3D();
    void UpdateStatus(char *addr, CTroll3DInfo *info) override;

private:
};

// Base class for CTroll3D factories of citra_qt
class QtCTroll3DFactory : public CTroll3DFactory {
    std::unique_ptr<CTroll3DInterface> Create() override;
};

} // namespace CTroll3D
