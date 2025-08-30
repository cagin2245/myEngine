#include "ResourceManager.h"
#include <iostream>
#include <memory>

std::map<std::string, std::shared_ptr<Shader>>    ResourceManager::Shaders;
std::map<std::string, std::shared_ptr<Texture>>   ResourceManager::Textures;


std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& name) {
    try {
    auto shader = std::make_shared<Shader>(vShaderFile, fShaderFile);
    Shaders[name] = shader;
#ifdef ENGINE_DEV_MODE
    std::cout << "Shader loaded: " << name << std::endl;
#endif
    return shader;
    } catch (const std::exception& e) {
#ifdef ENGINE_DEV_MODE
    std::cerr << "Shader load failed: " << name << " | " << e.what() << std::endl;
#endif
    return nullptr;
    }
}

std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& name) {
    return Shaders.at(name);
}


std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& file, const std::string& name) {
    try {
        auto texture = std::make_shared<Texture>(file);
        if (texture && texture->getWidth() > 0 && texture->getHeight() > 0) {
            Textures[name] = texture;
#ifdef ENGINE_DEV_MODE
            std::cout << "Texture loaded: " << name << std::endl;
#endif
            return texture;
        } else {
#ifdef ENGINE_DEV_MODE
            std::cerr << "Texture load failed: " << name << " | File: " << file << std::endl;
#endif
            return nullptr;
        }
    } catch (const std::exception& e) {
#ifdef ENGINE_DEV_MODE
        std::cerr << "Texture load exception: " << name << " | " << e.what() << std::endl;
#endif
        return nullptr;
    }
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& name) {
    return Textures.at(name);
}

void ResourceManager::Clear() {
    Shaders.clear();
    Textures.clear();
}
