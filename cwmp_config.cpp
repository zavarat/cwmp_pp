#include <fstream> // ifstream
#include "boost/program_options/parsers.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "cwmp_config.h"

namespace cwmp_pp
{

// constructor
basic_config::basic_config( const std::string & addr, 
                            const uint16_t port = DEFAULT_ACS_PORT ) :
    acs_port_in{port}, 
    acs_addr_in{addr}, 
    manufacturer_in{DEFAULT_MANUFACTURER},
    oui_in{DEFAULT_OUI},
    prod_class_in{DEFAULT_PROD_CLASS},
    sn_in{DEFAULT_SN},
    spec_ver_in{DEFAULT_SPEC_VER},
    hw_ver_in{DEFAULT_HW_VER},
    sw_ver_in{DEFAULT_SW_VER},
    prov_code_in{DEFAULT_PROV_CODE}
{
}

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
            else n=-1; __attribute__((fallthrough));
        case  1: 
            if(opt.string_key==ACS_PORT) {acs_port_in=stoi(opt.value[0]); break;} 
            else n=-1; __attribute__((fallthrough));
        case  2: 
            if(opt.string_key==CPE_MANUFACTURER) {manufacturer_in=opt.value[0]; break;} 
            else n=-1; __attribute__((fallthrough));
        case  3: 
            if(opt.string_key==CPE_OUI) {oui_in=opt.value[0]; break;} 
            else n=-1; __attribute__((fallthrough));
        case  4: 
            if(opt.string_key==CPE_PROD_CLASS) {prod_class_in=opt.value[0]; break;} 
            else n=-1; __attribute__((fallthrough));
        case  5: 
            if(opt.string_key==CPE_SN) {sn_in=opt.value[0]; break;} 
            else n=-1; __attribute__((fallthrough));
        case  6: 
            if(opt.string_key==CPE_SPEC_VER) {spec_ver_in=opt.value[0]; break;} 
            else n=-1; __attribute__((fallthrough));
        case  7: 
            if(opt.string_key==CPE_HW_VER) {hw_ver_in=opt.value[0]; break;} 
            else n=-1; __attribute__((fallthrough));
        case  8: 
            if(opt.string_key==CPE_SW_VER) {sw_ver_in=opt.value[0]; break;} 
            else n=-1; __attribute__((fallthrough));
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
    using boost::property_tree::ptree;
    ptree pt;
    pt.add( ACS_ADDR         , acs_addr_in      );
    pt.add( ACS_PORT         , acs_port_in      );
    pt.add( CPE_MANUFACTURER , manufacturer_in  );
    pt.add( CPE_OUI          , oui_in           );
    pt.add( CPE_PROD_CLASS   , prod_class_in    ); 
    pt.add( CPE_SN           , sn_in            );
    pt.add( CPE_SPEC_VER     , spec_ver_in      );
    pt.add( CPE_HW_VER       , hw_ver_in        );
    pt.add( CPE_SW_VER       , sw_ver_in        );
    pt.add( CPE_PROV_CODE    , prov_code_in     );
    write_ini( filename, pt );
    // option names
}

} // namespace cwmp_pp
