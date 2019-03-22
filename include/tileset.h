
#pragma once


#include <memory>
#include "tile.h"


namespace assets {

    class tileset {
    public:
        ~tileset();
        static tileset load(const std::string &assets);

        float units() const;
        const tile& get(const std::string& id) const;

    protected:
        tileset();
        tileset(const tileset&);


    protected:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };

}
