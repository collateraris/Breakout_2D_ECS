#pragma once

#include <XPath.h>

namespace breakout
{
    class Config
    {
    public:
        Config(const std::string fileName) : mFileName(fileName) { Load(); }
        ~Config() { Save(); }

        XPath GetRoot() const { return XPath(mDocument.FirstChildElement()); };

    private:
        std::string mFileName;
        tinyxml2::XMLDocument mDocument;

        void Load();
        void Save();
    };
}

