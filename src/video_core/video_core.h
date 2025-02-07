// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include "core/frontend/emu_window.h"

namespace Frontend {
class EmuWindow;
}

class RendererBase;

namespace Memory {
class MemorySystem;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Video Core namespace

namespace VideoCore {

extern std::unique_ptr<RendererBase> g_renderer; ///< Renderer plugin

// TODO: Wrap these in a user settings struct along with any other graphics settings (often set from
// qt ui)
extern std::atomic<bool> g_hw_renderer_enabled;
extern std::atomic<bool> g_shader_jit_enabled;
extern std::atomic<bool> g_hw_shader_enabled;
extern std::atomic<bool> g_separable_shader_enabled;
extern std::atomic<bool> g_hw_shader_accurate_mul;
extern std::atomic<bool> g_use_disk_shader_cache;
extern std::atomic<bool> g_renderer_bg_color_update_requested;
extern std::atomic<bool> g_renderer_sampler_update_requested;
extern std::atomic<bool> g_renderer_shader_update_requested;
extern std::atomic<bool> g_texture_filter_update_requested;
// Screenshot
extern std::atomic<bool> g_renderer_screenshot_requested;
extern void* g_screenshot_bits;
extern std::function<void()> g_screenshot_complete_callback;
extern Layout::FramebufferLayout g_screenshot_framebuffer_layout;

extern void* g_ctroll3d_bits;
extern std::function<int(char *)> g_ctroll3d_complete_callback;
extern Layout::FramebufferLayout g_ctroll3d_framebuffer_layout;
extern char *g_ctroll3d_addr;

extern Memory::MemorySystem* g_memory;

enum class ResultStatus {
    Success,
    ErrorGenericDrivers,
    ErrorBelowGL43,
};

/// Initialize the video core
ResultStatus Init(Frontend::EmuWindow& emu_window, Frontend::EmuWindow* secondary_window,
                  Memory::MemorySystem& memory);

/// Shutdown the video core
void Shutdown();

/// Request a screenshot of the next frame
void RequestScreenshot(void* data, std::function<void()> callback,
                       const Layout::FramebufferLayout& layout);

// Request connection to CTroll3D
void RequestCTroll3D(void* data, std::function<uint8_t(char *)> callback, const char *address,
                      const Layout::FramebufferLayout& layout);

u16 GetResolutionScaleFactor();

template <class Archive>
void serialize(Archive& ar, const unsigned int file_version);

} // namespace VideoCore
