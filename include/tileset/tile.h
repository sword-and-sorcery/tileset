#pragma once

#include <utility>
#include <string>
#include <map>
#include <optional>

namespace assets {

    struct tile {
        std::string filename;
        //std::pair<int, int> size;
        std::optional<int> zindex;
        std::map<std::string, std::string> properties;
    };

}
