#include "ResourceManager.h"
#include "Core/Logger.h"
#include <iostream>
#include <memory>

#include "ResourceManager.h"
#include "Core/Logger.h"
#include <iostream>
#include <memory>

namespace Engine {

std::unordered_map<std::string, std::shared_ptr<Shader>>    ResourceManager::Shaders;
std::unordered_map<std::string, std::shared_ptr<Texture>>   ResourceManager::Textures;


std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& name) {
    try {
    auto shader = std::make_shared<Shader>(vShaderFile, fShaderFile);
    ResourceManager::Shaders[name] = shader;

#ifdef ENGINE_DEV_MODE
    Logger::log(std::string("Shader loaded: ") + name, LogLevel::Info);
#endif
    return shader;
    } catch (const std::exception& e) {

#ifdef ENGINE_DEV_MODE
    Logger::log(std::string("Shader load failed: ") + name + " | " + e.what(), LogLevel::Error);
#endif
    return nullptr;
    }
}

std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& name) {
    auto it = ResourceManager::Shaders.find(name);
    if (it == ResourceManager::Shaders.end()) return nullptr;
    return it->second;
}


std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& file, const std::string& name) {
    try {
        auto texture = std::make_shared<Texture>(file);
        if (texture && texture->getWidth() > 0 && texture->getHeight() > 0) {
            ResourceManager::Textures[name] = texture;
#ifdef ENGINE_DEV_MODE
            Logger::log(std::string("Texture loaded: ") + name, LogLevel::Info);
#endif
            return texture;
        } else {
#ifdef ENGINE_DEV_MODE
            Logger::log(std::string("Texture load failed: ") + name + " | File: " + file, LogLevel::Error);
#endif
            return nullptr;
        }
    } catch (const std::exception& e) {
#ifdef ENGINE_DEV_MODE
        Logger::log(std::string("Texture load exception: ") + name + " | " + e.what(), LogLevel::Error);
#endif
        return nullptr;
    }
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& name) {
    auto it = ResourceManager::Textures.find(name);
    if (it == ResourceManager::Textures.end()) return nullptr;
    return it->second;
}

void ResourceManager::Clear() {
    ResourceManager::Shaders.clear();
    ResourceManager::Textures.clear();
}

} // namespace Engine
