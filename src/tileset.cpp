
#include "tileset/tileset.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

#include <iostream>
#include <boost/filesystem.hpp>

namespace assets {

    struct tileset::Impl {
        std::string name, url;
        std::string image;
        float unit;
        std::map<std::string, tile> _tiles;
    };

    tileset::tileset() : pImpl(std::make_unique<Impl>()) {}

    tileset::tileset(const tileset& other) : pImpl(std::make_unique<Impl>(*other.pImpl)) {
        pImpl->_tiles = other.pImpl->_tiles;
    }

    tileset::~tileset() {}

    tileset& tileset::operator=(const tileset& other) {
        pImpl->name = other.pImpl->name;
        pImpl->url = other.pImpl->url;
        pImpl->image = other.pImpl->image;
        pImpl->unit = other.pImpl->unit;
        pImpl->_tiles = other.pImpl->_tiles;
        return *this;
    }

    tileset tileset::load(const std::string &assets) {
        rapidxml::file<> xmlFile(assets.c_str());
        rapidxml::xml_document<> doc;
        try {
            tileset tile_set;
            auto basepath = boost::filesystem::path(assets).parent_path();

            doc.parse<0>(xmlFile.data());
            auto root = doc.first_node();

            // Parse metainformation about the asset
            auto package = root->first_node("package");
            tile_set.pImpl->name = package->first_node("name")->value();
            tile_set.pImpl->url = package->first_node("url")->value();
            auto image_path = basepath / boost::filesystem::path(package->first_node("image")->value());
            tile_set.pImpl->image = image_path.normalize().generic_string();

            // Parse all the tiles
            auto tiles = root->first_node("tiles");
            tile_set.pImpl->unit = atof(tiles->first_attribute("unit")->value());
            auto tile_node = tiles->first_node("tile");
            while(tile_node) {
                auto id = tile_node->first_attribute("id")->value();
                auto [tile_it, inserted] = tile_set.pImpl->_tiles.insert(std::make_pair<std::string, tile>(id, tile()));
                assert(inserted);
                auto& tile_ = tile_it->second;

                // Get the image file, zindex and properties
                tile_.filename = (basepath / tile_node->first_node("file")->value()).normalize().generic_string();
                auto property_node = tile_node->first_node("property");
                while (property_node) {
                    if (strcmp(property_node->name(), "property") == 0) {
                        auto name = property_node->first_attribute("name")->value();
                        auto value = property_node->first_attribute("value")->value();
                        if (strcmp(name, "zindex") == 0) {
                            tile_.zindex = atoi(value);
                        }
                        else {
                            auto [_, inserted] = tile_.properties.insert(std::make_pair(name, value));
                            assert(inserted);
                        }
                    }
                    property_node = property_node->next_sibling();
                }
                tile_node = tile_node->next_sibling("tile");
            }
            return tile_set;
        }
        catch(rapidxml::parse_error & e) {
            std::cerr << "Parse error: " << e.what() << std::endl << "At: " << e.where<char>() << std::endl;
            throw std::runtime_error("Invalid file"); // TODO
        }
        catch(std::exception& e) {
            // TODO:
            throw e;
        }
    }

    float tileset::units() const {
        return pImpl->unit;
    }

    const tile& tileset::get(const std::string& id) const {
        return pImpl->_tiles.at(id);
    }

}
