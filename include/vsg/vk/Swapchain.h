#pragma once

/* <editor-fold desc="MIT License">

Copyright(c) 2018 Robert Osfield

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</editor-fold> */

#include <vsg/vk/Surface.h>
#include <vsg/vk/ImageView.h>

namespace vsg
{
    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR        capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR>   presentModes;
    };

    extern VSG_EXPORT SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
    extern VSG_EXPORT VkSurfaceFormatKHR selectSwapSurfaceFormat(SwapChainSupportDetails& details);
    extern VSG_EXPORT VkExtent2D selectSwapExtent(SwapChainSupportDetails& details, uint32_t width, uint32_t height);
    extern VSG_EXPORT VkPresentModeKHR selectSwapPresentMode(SwapChainSupportDetails& details);

    class VSG_EXPORT Swapchain : public vsg::Object
    {
    public:
        Swapchain(VkSwapchainKHR swapchain, Device* device, Surface* surface, AllocationCallbacks*  allocator=nullptr);

        using Result = vsg::Result<Swapchain, VkResult, VK_SUCCESS>;
        static Result create(PhysicalDevice* physicalDevice, Device* device, Surface* surface, uint32_t width, uint32_t height, AllocationCallbacks*  allocator=nullptr);

        operator VkSwapchainKHR() const { return _swapchain; }

        VkFormat getImageFormat() const { return _format; }

        const VkExtent2D& getExtent() const { return _extent; }

        using ImageViews = std::vector<ref_ptr<ImageView>>;
        ImageViews& getImageViews() { return _imageViews; }
        const ImageViews& getImageViews() const { return _imageViews; }

    protected:

        virtual ~Swapchain();

        vsg::ref_ptr<Device>                _device;
        vsg::ref_ptr<Surface>               _surface;
        VkSwapchainKHR                      _swapchain;
        VkFormat                            _format;
        VkExtent2D                          _extent;
        ImageViews                          _imageViews;

        vsg::ref_ptr<AllocationCallbacks>   _allocator;

    };
}