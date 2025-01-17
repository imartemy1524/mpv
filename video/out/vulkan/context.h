#pragma once

#include "video/out/gpu/context.h"
#include "common.h"
#include "options/m_config.h"

struct ra_vk_ctx_params {
    // See ra_swapchain_fns.get_vsync.
    void (*get_vsync)(struct ra_ctx *ctx, struct vo_vsync_info *info);

    // For special contexts (i.e. wayland) that want to check visibility
    // before drawing a frame.
    bool (*check_visible)(struct ra_ctx *ctx);

    // In case something special needs to be done on the buffer swap.
    void (*swap_buffers)(struct ra_ctx *ctx);
};

// Helpers for ra_ctx based on ra_vk. These initialize ctx->ra and ctx->swchain.
void ra_vk_ctx_uninit(struct ra_ctx *ctx);
bool ra_vk_ctx_init(struct ra_ctx *ctx, struct mpvk_ctx *vk,
                    struct ra_vk_ctx_params params,
                    VkPresentModeKHR preferred_mode);

// Handles a resize request, and updates ctx->vo->dwidth/dheight
bool ra_vk_ctx_resize(struct ra_ctx *ctx, int width, int height);

// May be called on a ra_ctx of any type.
struct mpvk_ctx *ra_vk_ctx_get(struct ra_ctx *ctx);

// Get the user requested Vulkan device name.
char *ra_vk_ctx_get_device_name(struct ra_ctx *ctx);

extern struct vulkan_opts {
    char *device; // force a specific GPU
    int swap_mode;
    int queue_count;
    bool async_transfer;
    bool async_compute;
};

extern const struct m_sub_options vulkan_conf;
