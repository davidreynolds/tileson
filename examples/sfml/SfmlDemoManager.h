//
// Created by robin on 22.09.2019.
//

#ifndef TILESON_SFMLDEMOMANAGER_H
#define TILESON_SFMLDEMOMANAGER_H


#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <map>
#include "vera_font.h"

#include "../../include/tileson.h"
//#include "../../single_include/tileson.hpp"
//#include "../../include/external/json.hpp"
//#include "../../single_include/tileson_min.hpp"

#if __clang__
#include <mach-o/dyld.h>
#endif

class SfmlDemoManager
{
    public:
        SfmlDemoManager() = default;

        void initialize( const sf::Vector2i &windowSize, const sf::Vector2i &resolution = {400, 240},
                         const std::string &title = "SFML Tileson demo",
                         const fs::path &basePath = fs::path("../../../content/test-maps/"));
        bool parseMap(const std::string &filename = "ultimate_test.json");
        bool parseProject(const std::string &filename = "test.tiled-project");
        void run();

    private:
        #if __clang__
        fs::path getMacApplicationFolder(bool isAppPath);
        #endif
        
        void drawMap();
        void drawImgui();

        static constexpr int CURRENT_VERSION = 120; //v1.2.0

        void drawLayer(tson::Layer& layer);
        void drawTileLayer(const tson::Layer& layer);//, tson::Tileset* tileset);
        void drawImageLayer(tson::Layer& layer);
        void drawObjectLayer(tson::Layer& layer);

        sf::Vector2f getTileOffset(int tileId, tson::Map *map, tson::Tileset* tileset);

        sf::Sprite * storeAndLoadImage(const std::string &image, const sf::Vector2f &position);
        fs::path getTilesetImagePath(const tson::Tileset &tileset);

        fs::path m_basePath {};
        sf::RenderWindow m_window;
        std::unique_ptr<tson::Map> m_map;

        std::map<std::string, std::unique_ptr<tson::Map>> m_projectMaps; //Non-world maps in project

        std::vector<std::unique_ptr<tson::Map>> m_worldMaps; //World-related maps in project
        std::vector<tson::WorldMapData> m_worldData; //World-related data in project
        std::vector<bool> m_worldVisibilityFlags; //World-related data in project
        std::vector<std::string> m_worldMapInfo;
        std::vector<std::string> m_projectMapInfo;

        tson::Map *m_currentMap;
        std::string m_currentInfo;
        bool m_isImguiSizeSet = false;

        tson::Project m_project;

        sf::Font m_font;
        sf::Text m_demoText;

        int m_mapIndex {0};
        const int m_maxMapIndex {4};
        tson::Vector2i m_positionOffset {0,0}; //Used for world related stuff

        std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
        std::map<std::string, std::unique_ptr<sf::Sprite>> m_sprites;
};


#endif //TILESON_SFMLDEMOMANAGER_H
