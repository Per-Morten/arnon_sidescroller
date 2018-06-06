// ImGui GLFW binding with OpenGL3 + shaders
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

// Implemented features:
//  [X] User texture binding. Cast 'GLuint' OpenGL texture identifier as void*/ImTextureID. Read the FAQ about ImTextureID in imgui.cpp.
//  [X] Gamepad navigation mapping. Enable with 'io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad'.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

// CHANGELOG
// (minor and older changes stripped away, please see git history for details)
//  2018-02-23: OpenGL: Create the VAO in the render function so the setup can more easily be used with multiple shared GL context.
//  2018-02-20: Inputs: Added support for mouse cursors (ImGui::GetMouseCursor() value and WM_SETCURSOR message handling).
//  2018-02-20: Inputs: Renamed GLFW callbacks exposed in .h to not include GL3 in their name.
//  2018-02-16: Misc: Obsoleted the io.RenderDrawListsFn callback and exposed ImGui_ImplGlfwGL3_RenderDrawData() in the .h file so you can call it yourself.
//  2018-02-06: Misc: Removed call to ImGui::Shutdown() which is not available from 1.60 WIP, user needs to call CreateContext/DestroyContext themselves.
//  2018-02-06: Inputs: Added mapping for ImGuiKey_Space.
//  2018-01-25: Inputs: Added gamepad support if ImGuiConfigFlags_NavEnableGamepad is set.
//  2018-01-25: Inputs: Honoring the io.WantMoveMouse by repositioning the mouse (when using navigation and ImGuiConfigFlags_NavMoveMouse is set).
//  2018-01-20: Inputs: Added Horizontal Mouse Wheel support.
//  2018-01-18: Inputs: Added mapping for ImGuiKey_Insert.
//  2018-01-07: OpenGL: Changed GLSL shader version from 330 to 150. (Also changed GL context from 3.3 to 3.2 in example's main.cpp)
//  2017-09-01: OpenGL: Save and restore current bound sampler. Save and restore current polygon mode.
//  2017-08-25: Inputs: MousePos set to -FLT_MAX,-FLT_MAX when mouse is unavailable/missing (instead of -1,-1).
//  2017-05-01: OpenGL: Fixed save and restore of current blend function state.
//  2016-10-15: Misc: Added a void* user_data parameter to Clipboard function handlers.
//  2016-09-05: OpenGL: Fixed save and restore of current scissor rectangle.
//  2016-04-30: OpenGL: Fixed save and restore of current gl::ACTIVE_TEXTURE.

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_glfw.h"
#include "GL/glCore45.h"

#include <GLFW/glfw3.h>
#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif

// GLFW data
static GLFWwindow*  g_Window = nullptr;
static double       g_Time = 0.0;
       bool         g_MouseJustPressed[3] = { false, false, false };
       static GLFWcursor* g_MouseCursors[ImGuiMouseCursor_COUNT] = { 0 };

// OpenGL3 data
static char         g_GlslVersion[32] = "#version 450 core";
static GLuint       g_FontTexture = 0;
static int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
static int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
static int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int g_VboHandle = 0, g_ElementsHandle = 0;

// OpenGL3 Render function.
// (this used to be set in io.RenderDrawListsFn and called by ImGui::Render(), but you can now call this directly from your main loop)
// Note that this implementation is little overcomplicated because we are saving/setting up/restoring every OpenGL state explicitly, in order to be able to run within any OpenGL engine that doesn't do so.
void ImGui_ImplGlfwGL3_RenderDrawData(ImDrawData* draw_data)
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    ImGuiIO& io = ImGui::GetIO();
    auto fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    auto fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width == 0 || fb_height == 0)
        return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    // Backup GL state
    GLenum last_active_texture; gl::GetIntegerv(gl::ACTIVE_TEXTURE, (GLint*)&last_active_texture);
    gl::ActiveTexture(gl::TEXTURE0);
    GLint last_program; gl::GetIntegerv(gl::CURRENT_PROGRAM, &last_program);
    GLint last_texture; gl::GetIntegerv(gl::TEXTURE_BINDING_2D, &last_texture);
    GLint last_sampler; gl::GetIntegerv(gl::SAMPLER_BINDING, &last_sampler);
//     GLint last_array_buffer; gl::GetIntegerv(gl::ARRAY_BUFFER_BINDING, &last_array_buffer);
//     GLint last_element_array_buffer; gl::GetIntegerv(gl::ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
//     GLint last_vertex_array; gl::GetIntegerv(gl::VERTEX_ARRAY_BINDING, &last_vertex_array);
    GLint last_polygon_mode[2]; gl::GetIntegerv(gl::POLYGON_MODE, last_polygon_mode);
    GLint last_viewport[4]; gl::GetIntegerv(gl::VIEWPORT, last_viewport);
    GLint last_scissor_box[4]; gl::GetIntegerv(gl::SCISSOR_BOX, last_scissor_box);
    GLenum last_blend_src_rgb; gl::GetIntegerv(gl::BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb);
    GLenum last_blend_dst_rgb; gl::GetIntegerv(gl::BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb);
    GLenum last_blend_src_alpha; gl::GetIntegerv(gl::BLEND_SRC_ALPHA, (GLint*)&last_blend_src_alpha);
    GLenum last_blend_dst_alpha; gl::GetIntegerv(gl::BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha);
    GLenum last_blend_equation_rgb; gl::GetIntegerv(gl::BLEND_EQUATION_RGB, (GLint*)&last_blend_equation_rgb);
    GLenum last_blend_equation_alpha; gl::GetIntegerv(gl::BLEND_EQUATION_ALPHA, (GLint*)&last_blend_equation_alpha);
    GLboolean last_enable_blend = gl::IsEnabled(gl::BLEND);
    GLboolean last_enable_cull_face = gl::IsEnabled(gl::CULL_FACE);
    GLboolean last_enable_depth_test = gl::IsEnabled(gl::DEPTH_TEST);
    GLboolean last_enable_scissor_test = gl::IsEnabled(gl::SCISSOR_TEST);

    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
    gl::Enable(gl::BLEND);
    gl::BlendEquation(gl::FUNC_ADD);
    gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
    gl::Disable(gl::CULL_FACE);
    gl::Disable(gl::DEPTH_TEST);
    gl::Enable(gl::SCISSOR_TEST);
    gl::PolygonMode(gl::FRONT_AND_BACK, gl::FILL);

    // Setup viewport, orthographic projection matrix
    gl::Viewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
    const float ortho_projection[4][4] =
    {
    { 2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
    { 0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
    { 0.0f,                  0.0f,                    -1.0f, 0.0f },
    { -1.0f,                  1.0f,                    0.0f, 1.0f },
    };
    gl::UseProgram(g_ShaderHandle);
    gl::Uniform1i(g_AttribLocationTex, 0);
    gl::UniformMatrix4fv(g_AttribLocationProjMtx, 1, gl::FALSE_, &ortho_projection[0][0]);
    gl::BindSampler(0, 0); // Rely on combined texture/sampler state.

    // Recreate the VAO every time
    // (This is to easily allow multiple GL contexts. VAO are not shared among GL contexts, and we don't track creation/deletion of windows so we don't have an obvious key to use to cache them.)
    GLuint vao_handle = 0;
    gl::GenVertexArrays(1, &vao_handle);
    gl::BindVertexArray(vao_handle);
    gl::BindBuffer(gl::ARRAY_BUFFER, g_VboHandle);
    gl::EnableVertexAttribArray(g_AttribLocationPosition);
    gl::EnableVertexAttribArray(g_AttribLocationUV);
    gl::EnableVertexAttribArray(g_AttribLocationColor);
    gl::VertexAttribPointer(g_AttribLocationPosition, 2, gl::FLOAT, gl::FALSE_, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, pos));
    gl::VertexAttribPointer(g_AttribLocationUV, 2, gl::FLOAT, gl::FALSE_, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, uv));
    gl::VertexAttribPointer(g_AttribLocationColor, 4, gl::UNSIGNED_BYTE, gl::TRUE_, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, col));

    // Draw
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawIdx* idx_buffer_offset = 0;

        gl::BindBuffer(gl::ARRAY_BUFFER, g_VboHandle);
        gl::BufferData(gl::ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, gl::STREAM_DRAW);

        gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
        gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, gl::STREAM_DRAW);

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                gl::BindTexture(gl::TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                gl::Scissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                gl::DrawElements(gl::TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? gl::UNSIGNED_SHORT : gl::UNSIGNED_INT, idx_buffer_offset);
            }
            idx_buffer_offset += pcmd->ElemCount;
        }
    }
    gl::DeleteVertexArrays(1, &vao_handle);

    // Restore modified GL state
    gl::UseProgram(last_program);
    gl::BindTexture(gl::TEXTURE_2D, last_texture);
    gl::BindSampler(0, last_sampler);
    gl::ActiveTexture(last_active_texture);
//     gl::BindVertexArray(last_vertex_array);
//     gl::BindBuffer(gl::ARRAY_BUFFER, last_array_buffer);
//     gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
    gl::BlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
    gl::BlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
    if (last_enable_blend) gl::Enable(gl::BLEND); else gl::Disable(gl::BLEND);
    if (last_enable_cull_face) gl::Enable(gl::CULL_FACE); else gl::Disable(gl::CULL_FACE);
    if (last_enable_depth_test) gl::Enable(gl::DEPTH_TEST); else gl::Disable(gl::DEPTH_TEST);
    if (last_enable_scissor_test) gl::Enable(gl::SCISSOR_TEST); else gl::Disable(gl::SCISSOR_TEST);
    gl::PolygonMode(gl::FRONT_AND_BACK, (GLenum)last_polygon_mode[0]);
    gl::Viewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
    gl::Scissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
}

static const char* ImGui_ImplGlfwGL3_GetClipboardText(void* user_data)
{
    return glfwGetClipboardString((GLFWwindow*)user_data);
}

static void ImGui_ImplGlfwGL3_SetClipboardText(void* user_data, const char* text)
{
    glfwSetClipboardString((GLFWwindow*)user_data, text);
}

void ImGui_ImplGlfw_CharCallback(GLFWwindow*, unsigned int c)
{
    ImGuiIO& io = ImGui::GetIO();
    if (c > 0 && c < 0x10000)
        io.AddInputCharacter((unsigned short)c);
}

bool ImGui_ImplGlfwGL3_CreateFontsTexture()
{
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.

    // Upload texture to graphics system
    gl::CreateTextures(gl::TEXTURE_2D, 1, &g_FontTexture);
    gl::TextureStorage2D(g_FontTexture, 1, gl::RGBA8, width, height);
    gl::TextureParameteri(g_FontTexture, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
    gl::TextureParameteri(g_FontTexture, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
    gl::PixelStorei(gl::UNPACK_ROW_LENGTH, 0);
    gl::TextureSubImage2D(g_FontTexture, 0, 0, 0, width, height, gl::RGBA, gl::UNSIGNED_BYTE, pixels);

    // Store our identifier
    io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

    return true;
}

bool ImGui_ImplGlfwGL3_CreateDeviceObjects()
{
    // Backup GL state
    GLint last_texture;
    gl::GetIntegerv(gl::TEXTURE_BINDING_2D, &last_texture);

    const GLchar *vertex_shader =
        "#version 150\n"
        "uniform mat4 ProjMtx;\n"
        "in vec2 Position;\n"
        "in vec2 UV;\n"
        "in vec4 Color;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "	Frag_UV = UV;\n"
        "	Frag_Color = Color;\n"
        "	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

    const GLchar* fragment_shader =
        "#version 150\n"
        "uniform sampler2D Texture;\n"
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
        "}\n";

    g_ShaderHandle = gl::CreateProgram();
    g_VertHandle = gl::CreateShader(gl::VERTEX_SHADER);
    g_FragHandle = gl::CreateShader(gl::FRAGMENT_SHADER);
    gl::ShaderSource(g_VertHandle, 1, &vertex_shader, 0);
    gl::ShaderSource(g_FragHandle, 1, &fragment_shader, 0);
    gl::CompileShader(g_VertHandle);
    gl::CompileShader(g_FragHandle);
    gl::AttachShader(g_ShaderHandle, g_VertHandle);
    gl::AttachShader(g_ShaderHandle, g_FragHandle);
    gl::LinkProgram(g_ShaderHandle);

    g_AttribLocationTex = gl::GetUniformLocation(g_ShaderHandle, "Texture");
    g_AttribLocationProjMtx = gl::GetUniformLocation(g_ShaderHandle, "ProjMtx");
    g_AttribLocationPosition = gl::GetAttribLocation(g_ShaderHandle, "Position");
    g_AttribLocationUV = gl::GetAttribLocation(g_ShaderHandle, "UV");
    g_AttribLocationColor = gl::GetAttribLocation(g_ShaderHandle, "Color");

    gl::CreateBuffers(1, &g_VboHandle);
    gl::CreateBuffers(1, &g_ElementsHandle);

    ImGui_ImplGlfwGL3_CreateFontsTexture();

    // Restore modified GL state
    gl::BindTexture(gl::TEXTURE_2D, last_texture);

    return true;
}

void    ImGui_ImplGlfwGL3_InvalidateDeviceObjects()
{
    if (g_VboHandle) gl::DeleteBuffers(1, &g_VboHandle);
    if (g_ElementsHandle) gl::DeleteBuffers(1, &g_ElementsHandle);
    g_VboHandle = g_ElementsHandle = 0;

    if (g_ShaderHandle && g_VertHandle) gl::DetachShader(g_ShaderHandle, g_VertHandle);
    if (g_VertHandle) gl::DeleteShader(g_VertHandle);
    g_VertHandle = 0;

    if (g_ShaderHandle && g_FragHandle) gl::DetachShader(g_ShaderHandle, g_FragHandle);
    if (g_FragHandle) gl::DeleteShader(g_FragHandle);
    g_FragHandle = 0;

    if (g_ShaderHandle) gl::DeleteProgram(g_ShaderHandle);
    g_ShaderHandle = 0;

    if (g_FontTexture)
    {
        gl::DeleteTextures(1, &g_FontTexture);
        ImGui::GetIO().Fonts->TexID = 0;
        g_FontTexture = 0;
    }
}

bool ImGui_ImplGlfwGL3_Init(GLFWwindow* window)
{
    g_Window = window;
    g_Time = 0.0;

    const char* glsl_version = NULL;
    // Store GLSL version string so we can refer to it later in case we recreate shaders. Note: GLSL version is NOT the same as GL version. Leave this to NULL if unsure.
    if (glsl_version == NULL)
        glsl_version = "#version 150";
    IM_ASSERT((int)strlen(glsl_version) + 2 < IM_ARRAYSIZE(g_GlslVersion));
    strcpy(g_GlslVersion, glsl_version);
    strcat(g_GlslVersion, "\n");

    // Setup back-end capabilities flags
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;   // We can honor GetMouseCursor() values (optional)
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;    // We can honor io.WantSetMousePos requests (optional, rarely used)
                                                            // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    io.SetClipboardTextFn = ImGui_ImplGlfwGL3_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplGlfwGL3_GetClipboardText;
    io.ClipboardUserData = g_Window;
#ifdef _WIN32
    io.ImeWindowHandle = glfwGetWin32Window(g_Window);
#endif

    // Load cursors
    // FIXME: GLFW doesn't expose suitable cursors for ResizeAll, ResizeNESW, ResizeNWSE. We revert to arrow cursor for those.
    g_MouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);

    return true;
}

void ImGui_ImplGlfwGL3_Shutdown()
{
    // Destroy GLFW mouse cursors
    for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_Count_; cursor_n++)
        glfwDestroyCursor(g_MouseCursors[cursor_n]);
    memset(g_MouseCursors, 0, sizeof(g_MouseCursors));

    // Destroy OpenGL objects
    ImGui_ImplGlfwGL3_InvalidateDeviceObjects();
}

void ImGui_ImplGlfwGL3_NewFrame()
{
    if (!g_FontTexture)
        ImGui_ImplGlfwGL3_CreateDeviceObjects();

    ImGuiIO& io = ImGui::GetIO();

    // Setup display size (every frame to accommodate for window resizing)
    int w, h;
    int display_w, display_h;
    glfwGetWindowSize(g_Window, &w, &h);
    glfwGetFramebufferSize(g_Window, &display_w, &display_h);
    io.DisplaySize = ImVec2((float)w, (float)h);
    io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

    // Setup time step
    double current_time = glfwGetTime();
    io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
    g_Time = current_time;

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
    if (glfwGetWindowAttrib(g_Window, GLFW_FOCUSED))
    {
        // Set OS mouse position if requested (only used when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
        if (io.WantSetMousePos)
        {
            glfwSetCursorPos(g_Window, (double)io.MousePos.x, (double)io.MousePos.y);
        }
        else
        {
            double mouse_x, mouse_y;
            glfwGetCursorPos(g_Window, &mouse_x, &mouse_y);
            io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
        }
    }
    else
    {
        io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
    }

    for (int i = 0; i < 3; i++)
    {
        // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
        io.MouseDown[i] = g_MouseJustPressed[i] || glfwGetMouseButton(g_Window, i) != 0;
        g_MouseJustPressed[i] = false;
    }

    // Update OS/hardware mouse cursor if imgui isn't drawing a software cursor
    if ((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) == 0 && glfwGetInputMode(g_Window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
    {
        ImGuiMouseCursor cursor = ImGui::GetMouseCursor();
        if (io.MouseDrawCursor || cursor == ImGuiMouseCursor_None)
        {
            glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
        else
        {
            glfwSetCursor(g_Window, g_MouseCursors[cursor] ? g_MouseCursors[cursor] : g_MouseCursors[ImGuiMouseCursor_Arrow]);
            glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    // Gamepad navigation mapping [BETA]
    memset(io.NavInputs, 0, sizeof(io.NavInputs));
    if (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad)
    {
        // Update gamepad inputs
#define MAP_BUTTON(NAV_NO, BUTTON_NO)       { if (buttons_count > BUTTON_NO && buttons[BUTTON_NO] == GLFW_PRESS) io.NavInputs[NAV_NO] = 1.0f; }
#define MAP_ANALOG(NAV_NO, AXIS_NO, V0, V1) { float v = (axes_count > AXIS_NO) ? axes[AXIS_NO] : V0; v = (v - V0) / (V1 - V0); if (v > 1.0f) v = 1.0f; if (io.NavInputs[NAV_NO] < v) io.NavInputs[NAV_NO] = v; }
        int axes_count = 0, buttons_count = 0;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
        const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
        MAP_BUTTON(ImGuiNavInput_Activate, 0);     // Cross / A
        MAP_BUTTON(ImGuiNavInput_Cancel, 1);     // Circle / B
        MAP_BUTTON(ImGuiNavInput_Menu, 2);     // Square / X
        MAP_BUTTON(ImGuiNavInput_Input, 3);     // Triangle / Y
        MAP_BUTTON(ImGuiNavInput_DpadLeft, 13);    // D-Pad Left
        MAP_BUTTON(ImGuiNavInput_DpadRight, 11);    // D-Pad Right
        MAP_BUTTON(ImGuiNavInput_DpadUp, 10);    // D-Pad Up
        MAP_BUTTON(ImGuiNavInput_DpadDown, 12);    // D-Pad Down
        MAP_BUTTON(ImGuiNavInput_FocusPrev, 4);     // L1 / LB
        MAP_BUTTON(ImGuiNavInput_FocusNext, 5);     // R1 / RB
        MAP_BUTTON(ImGuiNavInput_TweakSlow, 4);     // L1 / LB
        MAP_BUTTON(ImGuiNavInput_TweakFast, 5);     // R1 / RB
        MAP_ANALOG(ImGuiNavInput_LStickLeft, 0, -0.3f, -0.9f);
        MAP_ANALOG(ImGuiNavInput_LStickRight, 0, +0.3f, +0.9f);
        MAP_ANALOG(ImGuiNavInput_LStickUp, 1, +0.3f, +0.9f);
        MAP_ANALOG(ImGuiNavInput_LStickDown, 1, -0.3f, -0.9f);
#undef MAP_BUTTON
#undef MAP_ANALOG
        if (axes_count > 0 && buttons_count > 0)
            io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
        else
            io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
    }

    // Start the frame. This call will update the io.WantCaptureMouse, io.WantCaptureKeyboard flag that you can use to dispatch inputs (or not) to your application.
    ImGui::NewFrame();
}
