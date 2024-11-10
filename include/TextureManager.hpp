#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include "ResourceManager.hpp"
#include <SFML/Graphics/Texture.hpp>

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
    sf::Texture* Load(const std::string& l_path)
    {
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(Utils::GetWorkingDirectory() + l_path))
        {
            delete texture;
            texture = nullptr;
            std::cerr << " ! Failed to load texture: " << l_path << std::endl;
        }
        return texture;
    }
};

#endif // __TEXTUREMANAGER_H__