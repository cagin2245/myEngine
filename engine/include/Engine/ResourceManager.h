#pragma once
#include <string>
#include <map>
#include <memory>
#include "Texture.h"
#include "Shader.h"

class ResourceManager {
public:
    // Yüklenen tüm shaderlar ve texturelar burada tutulur
    static std::map<std::string, std::shared_ptr<Shader>>    Shaders;
    static std::map<std::string, std::shared_ptr<Texture>>   Textures;

    // Shader yükle ve sakla
    static std::shared_ptr<Shader> LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& name);
    static std::shared_ptr<Shader> GetShader(const std::string& name);

    // Texture yükle ve sakla
    static std::shared_ptr<Texture> LoadTexture(const std::string& file, const std::string& name);
    static std::shared_ptr<Texture> GetTexture(const std::string& name);

    // Tüm kaynakları temizle
    static void Clear();

private:
    ResourceManager() { }
};
