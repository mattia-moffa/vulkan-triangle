#include <cstdint>
#include <optional>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

struct queue_family_indices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool is_complete() {
        return graphics_family.has_value() && present_family.has_value();
    }
};

struct swap_chain_support_details {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

class triangle_application {
    public:
        void run();
    private:
        void init_window();
        void init_vulkan();
        void main_loop();
        void cleanup();

        void create_instance();
        void setup_debug_messenger();
        void create_surface();
        void pick_physical_device();
        void create_logical_device();
        void create_swap_chain();
        void cleanup_swap_chain();
        void recreate_swap_chain();
        void create_image_views();
        void create_render_pass();
        void create_graphics_pipeline();
        void create_framebuffers();
        void create_command_pool();
        void create_command_buffers();
        void create_sync_objects();

        static void framebuffer_resize_callback(GLFWwindow *window, int width, int height);


        static bool check_validation_layer_support();
        static std::vector<const char *> get_required_extensions();
        static void show_available_extensions();
        static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
                VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                VkDebugUtilsMessageTypeFlagsEXT message_type,
                const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
                void *p_user_data);

        void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &create_info);


        static bool is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR surface);
        static bool check_device_extension_support(VkPhysicalDevice device);
        static queue_family_indices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface);

        static swap_chain_support_details query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR surface);
        static VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats);
        static VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR> &available_present_modes);
        static VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);

        static std::vector<char> read_file(const std::string &filename);
        VkShaderModule create_shader_module(const std::vector<char> &code);


        void draw_frame();

        void record_command_buffer(VkCommandBuffer command_buffer, std::uint32_t image_index);


        GLFWwindow *window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debug_messenger;
        VkSurfaceKHR surface;
        VkPhysicalDevice physical_device = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphics_queue;
        VkQueue present_queue;
        VkSwapchainKHR swap_chain;
        std::vector<VkImage> swap_chain_images;
        VkFormat swap_chain_image_format;
        VkExtent2D swap_chain_extent;
        std::vector<VkImageView> swap_chain_image_views;
        VkRenderPass render_pass;
        VkPipelineLayout pipeline_layout;
        VkPipeline graphics_pipeline;
        std::vector<VkFramebuffer> swap_chain_framebuffers;
        VkCommandPool command_pool;
        std::vector<VkCommandBuffer> command_buffers;
        std::vector<VkSemaphore> image_available_semaphores;
        std::vector<VkSemaphore> render_finished_semaphores;
        std::vector<VkFence> in_flight_fences;
        bool framebuffer_resized = false;
        std::uint32_t current_frame = 0;
};
