// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <unordered_map>
#include "common/logging/log.h"
#include "core/frontend/ctroll3d/factory.h"

namespace CTroll3D {

static std::unordered_map<std::string, std::unique_ptr<CTroll3DFactory>> factories;

CTroll3DFactory::~CTroll3DFactory() = default;

void RegisterFactory(const std::string& name, std::unique_ptr<CTroll3DFactory> factory) {
    factories[name] = std::move(factory);
}

std::unique_ptr<CTroll3DInterface> CreateCTroll3D(const std::string& name) {
    auto pair = factories.find(name);
    if (pair != factories.end()) {
        return pair->second->Create();
    }

    if (name != "blank") {
        LOG_ERROR(Service_CAM, "Unknown CTroll3D {}", name);
    }
    return nullptr;
}

} // namespace CTroll3D
