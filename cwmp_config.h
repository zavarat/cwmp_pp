#ifndef CWMP_CONFIG_H
#define CWMP_CONFIG_H

#include <cstdint> // fixed length ints
#include <string>
#include <vector>
#include <boost/program_options/option.hpp>

#define   DEFAULT_CONFIG_FNAME  "cwmp_config.cfg"
#define   DEFAULT_ACS_ADDR      "127.0.0.1" 
#define   DEFAULT_MANUFACTURER  "dflt_manufacturer"
#define   DEFAULT_OUI           "df1234"
#define   DEFAULT_PROD_CLASS    "dflt"
#define   DEFAULT_SN            "DFSN0001"
#define   DEFAULT_SPEC_VER      "1.0"
#define   DEFAULT_HW_VER        "HW_DFLT"
#define   DEFAULT_SW_VER        "SW_DFLT"
#define   DEFAULT_PROV_CODE     "CNFG.DFLT"

namespace po = boost::program_options;

namespace cwmp_pp {

constexpr uint16_t DEFAULT_ACS_PORT = 5555      ;

// basic class for operating with CWMP setting
class basic_config
{
    protected:
        uint16_t    acs_port_in      ;
        std::string acs_addr_in      ;
        std::string manufacturer_in  ;
        std::string oui_in           ;
        std::string prod_class_in    ;
        std::string sn_in            ;
        std::string spec_ver_in      ;
        std::string hw_ver_in        ;
        std::string sw_ver_in        ;
        std::string prov_code_in     ;

    public:
        basic_config(const std::string & addr, const uint16_t port );
        basic_config() : basic_config(DEFAULT_ACS_ADDR, DEFAULT_ACS_PORT) {}; 
        
        virtual void save() const {}; // basic config has no storage mechanisms
        virtual void load() {};

        const std::string & acs_addr() const { return acs_addr_in ; } 
        uint16_t            acs_port() const { return acs_port_in ; }
};

// option names
#define ACS_PORT            "acs.port"
#define ACS_ADDR            "acs.addr"
#define CPE_MANUFACTURER    "cpe.manufacturer"
#define CPE_OUI             "cpe.oui"
#define CPE_PROD_CLASS      "cpe.product_class"
#define CPE_SN              "cpe.serial_number"
#define CPE_SPEC_VER        "cpe.spec_version"
#define CPE_HW_VER          "cpe.hardware_version"
#define CPE_SW_VER          "cpe.software_version"
#define CPE_PROV_CODE       "cpe.provisioning_code"

using opt_t = po::basic_option<char>;
using opt_vector = std::vector< opt_t >;

class config_file : public basic_config
{
    private:
        std::string filename;
        void set_members_from_var_list( const opt_vector & v );
        void set_member( const opt_t & opt, int & n );
    public:
        config_file(const std::string & fname) : filename{fname} { load(); }
        config_file() : config_file(DEFAULT_CONFIG_FNAME) {}
        void load();
        void save() const;
        ~config_file() { try{ save(); } catch(...) {} }
};

} // namespace cwmp_pp

#endif // CWMP_CONFIG_H
