#pragma once
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include "../../structs/EntityRenderInfo.h"

class Renderer {
private:
    static constexpr int WINDOW_WIDTH = 900;
    static constexpr int WINDOW_HEIGHT = 800;

    sf::RenderWindow m_window{};
    TextureManager m_textures{};
    FontManager m_fonts{};
    sf::Sprite m_background{};
    sf::Text m_healthText{};

    bool loadAllAssets();
    void initTexts();
public:
    bool initWindow();

    bool isOpen() const;
    bool pollEvent(sf::Event &);

    void close();
    void clear();
    void draw(const std::vector<EntityRenderInfo> &entities, int playerHealth);
    void display();

    std::pair<float, float> getWindowSize() const;
};

