#include "fdxx/Event.hpp"

std::string fdxx::to_string(fdxx::Event event)
{
    switch (event)
    {
        case fdxx::Event::read:
            return "Read";
        case fdxx::Event::write:
            return "Write";
        case fdxx::Event::error:
            return "Error";
        default:
            return std::to_string(static_cast<unsigned>(event));
    }
}