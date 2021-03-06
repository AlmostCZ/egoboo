#include "egolib/App.hpp"

#include "egolib/Graphics/GraphicsSystem.hpp"
#include "egolib/Graphics/GraphicsWindow.hpp"
#include "egolib/Graphics/TextureManager.hpp"
#include "egolib/Image/ImageManager.hpp"
#include "egolib/Graphics/FontManager.hpp"
#include "egolib/Renderer/Renderer.hpp"
#include "egolib/Extensions/ogl_include.h"

namespace Ego {

AppImpl::AppImpl(const std::string& title, const std::string& version)
{
    // Initialize the graphics system.
    GraphicsSystem::initialize();
    // Initialize the image manager.
    ImageManager::initialize();
    // Initialize the renderer.
    Renderer::initialize();
    // Initialize the texture manager.
    TextureManager::initialize();
    // Initialize the font manager.
    FontManager::initialize();

    auto& renderer = Renderer::get();
    // Set clear colour and clear depth.
    renderer.getColourBuffer().setClearValue(Math::Colour4f(0, 0, 0, 0)); // Set black/transparent background.
    renderer.getDepthBuffer().setClearValue(1.0f);

    // Enable writing to the depth buffer.
    renderer.setDepthWriteEnabled(true);

    // Enable depth test. Incoming fragment's depth value must be less.
    renderer.setDepthTestEnabled(true);
    renderer.setDepthFunction(CompareFunction::Less);

    // Disable blending.
    renderer.setBlendingEnabled(false);

    // Enable alpha testing: Hide fully transparent parts.
    renderer.setAlphaTestEnabled(true);
    renderer.setAlphaFunction(CompareFunction::Greater, 0.0f);

    /// @todo Including backface culling here prevents the mesh from getting rendered
    /// backface culling
    // oglx_begin_culling(Ego::CullingMode::Back, Ego::WindingMode::Clockwise); // GL_ENABLE_BIT | GL_POLYGON_BIT

    // disable OpenGL lighting
    renderer.setLightingEnabled(false);

    // fill mode
    renderer.setRasterizationMode(RasterizationMode::Solid);

    // set up environment mapping
    /// @todo: this isn't used anywhere
    GL_DEBUG(glTexGeni)(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);  // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
    GL_DEBUG(glTexGeni)(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);  // Set The Texture Generation Mode For T To Sphere Mapping (NEW)

                                                                    //Initialize the motion blur buffer
    renderer.getAccumulationBuffer().setClearValue(Math::Colour4f(0.0f, 0.0f, 0.0f, 1.0f));
    renderer.getAccumulationBuffer().clear();

    GraphicsSystem::window->setTitle(title + " " + version);
}

AppImpl::~AppImpl()
{
    // Uninitialize the font manager.
    FontManager::uninitialize();
    // Uninitialize the texture manager.
    TextureManager::uninitialize();
    // Uninitialize the renderer.
    Renderer::uninitialize();
    // Uninitialize the image manager.
    ImageManager::uninitialize();
    // Uninitialize the graphics system.
    GraphicsSystem::uninitialize();
}

}