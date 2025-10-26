#pragma once
#include "AssetManager.h"
#include <SFML/Graphics.hpp>

class Renderer {
private:
    static constexpr int m_windowWidth = 900;
    static constexpr int m_windowHeight = 800;

    sf::RenderWindow m_window{};
    TextureManager m_textures{};
    FontManager m_fonts{};

    bool loadAllAssets();
public:
    bool initWindow();

    bool isOpen() const;
    bool pollEvent(sf::Event &);

    void close();
    void clear();
    void draw();
    void display();
};

