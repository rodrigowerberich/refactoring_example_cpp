#pragma once

#include <string>
#include <stdexcept>

namespace TheaterBilling
{

class Play {
public:
    enum class Type{
        Tragedy,
        Comedy,
        Invalid
    };

    Play(): m_name{""}, m_type{Type::Invalid}{}
    Play(const std::string& _name, Play::Type _type): m_name{_name}, m_type{_type}{}
    const std::string& name() const{ return m_name; }
    Type type() const{ return m_type; }

    static std::string type2str(Play::Type _type){
        switch (_type)
        {
        case Type::Tragedy:
            return "Tragedy";
        case Type::Comedy:
            return "Comedy";
        case Type::Invalid:
            return "Invalid";
        default:
            throw std::runtime_error("Unsupported play type for str conversion.");
        }
    }
private:
    std::string m_name;
    Play::Type m_type;
};

} // namespace TheaterBilling
