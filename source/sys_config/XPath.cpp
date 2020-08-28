#include <XPath.h>

using namespace breakout;

const txml::XMLElement* XPath::GetElement(const txml::XMLElement* elem, const std::string& path) const
{
    if (elem == nullptr)
        return nullptr;

    std::size_t pos = path.find_first_of(PATH_DELIMITER);

    if (pos == std::string::npos)
        return elem->FirstChildElement(path.c_str());

    std::string step = path.substr(0, pos);

    const txml::XMLElement* child = elem->FirstChildElement(step.c_str());
    if (child == nullptr)
        return nullptr;

    return GetElement(child, path.substr(pos + 1));

}

std::vector<XPath> XPath::GetChildren() const
{
    std::vector<XPath> children;

    const txml::XMLElement* child = root->FirstChildElement();

    while (child != nullptr)
    {
        children.push_back(XPath(child));
        child = child->NextSiblingElement();
    }

    return children;
}

