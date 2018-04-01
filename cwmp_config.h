#ifndef CWMP_CONFIG_H
#define CWMP_CONFIG_H

#include <cstdint> // fixed length ints
#include <string>

#define   DEFAULT_ACS_ADDR "127.0.0.1" 

namespace cwmp_pp {

constexpr uint16_t DEFAULT_ACS_PORT = 5555      ;

// basic class for operating with CWMP setting
class basic_config
{
    protected:
        uint16_t    acs_port_in ;
        std::string acs_addr_in ;

    public:
        basic_config(const std::string & addr, const uint16_t port ) :
            acs_port_in{port}, acs_addr_in{addr} {}

        basic_config() : basic_config(DEFAULT_ACS_ADDR, DEFAULT_ACS_PORT) {}; 
        
        virtual void save() const {}; // basic config has no storage mechanisms
        virtual void load() {};

        const std::string & acs_addr() const { return acs_addr_in ; } 
        uint16_t            acs_port() const { return acs_port_in ; }
};

class config_file : public basic_config
{
    public:
};

} // namespace cwmp_pp

#endif // CWMP_CONFIG_H
