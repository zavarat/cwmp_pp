#include <iostream> // debug
#include <fstream> // ifstream
#include "boost/program_options/parsers.hpp"
#include "boost/program_options/variables_map.hpp"
#include "boost/any.hpp"
#include "cwmp_config.h"

namespace cwmp_pp
{

void config_file::set_member( const opt_t & opt, int & n )
{
    using namespace boost;
    using namespace std;

    // here we getting profit from likely consistent order
    switch( n )
    {
        case -1: // order mismatch: walk through all possible options (unlikely)
        case  0: 
            if(opt.string_key==ACS_ADDR) {acs_addr_in=opt.value[0]; break;} 
            else n=-1;
        case  1: 
            if(opt.string_key==ACS_PORT) {acs_port_in=stoi(opt.value[0]); break;} 
            else n=-1;
    }
    if( n >= 0 ) ++n;
}

void config_file::set_members_from_var_list( const opt_vector & v )
{
    int parsed_n = 0;
    for( const auto& itt : v ) set_member( itt, parsed_n );
}

void config_file::load()
{
    // TODO: move something to private?
    std::ifstream cf_stream{this->filename};
    po::options_description opts;
    auto parsed = po::parse_config_file( cf_stream, opts, true );
    set_members_from_var_list( parsed.options );
}

void config_file::save() const
{
}

} // namespace cwmp_pp
