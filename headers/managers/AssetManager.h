#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include <unordered_map>

template<typename asset_t>
struct SFMLLoadPolicy {
    using valueType = asset_t;

    std::optional<valueType> load(const std::string &path) {
        valueType value;
        if (value.loadFromFile(path)) {
            return std::optional<valueType>(value);
        } else {
            return std::optional<valueType>();
        }
    }
};

template<typename load_policy_t>
class basicAssetManager {
private:
    using valueType = typename load_policy_t::valueType;
    std::unordered_map<std::string, valueType> m_data;

    load_policy_t m_loader;
public:
    bool load(const std::string &name, const std::string &path) {
        auto result {m_loader.load(path)};
        const bool was_loaded {result.has_value()};

        if (was_loaded) {
            m_data[name] = std::move(result.value());
        }

        return was_loaded;
    }
};

template<typename manager_t>
bool loadAssets(manager_t &manager, const std::vector<std::pair<std::string, std::string>> &assets) {
    for (const auto &[name, path] : assets) {
        if (!manager.load(name, path)) {
            std::cerr << "Asset with name: " << name << "can not be loaded with path: " << path << std::endl;
            return false;
        }
    }

    return true;
}

using TextureManager = basicAssetManager<SFMLLoadPolicy<sf::Texture>>;
using FontManager = basicAssetManager<SFMLLoadPolicy<sf::Font>>;