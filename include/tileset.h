
#pragma once


#include <memory>
#include "tile.h"


namespace assets {

    class tileset {
    public:
        tileset();
        tileset(const tileset&);
        ~tileset();
        static tileset load(const std::string &assets);

        tileset& operator=(const tileset&);

        float units() const;
        const tile& get(const std::string& id) const;

    protected:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };

}
