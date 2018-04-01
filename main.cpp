#include <iostream>
#include <cstdint>      // fixed length ints
#include <stdexcept>    // runtime_error
#include <memory>       // unique_ptr
#include <evhttp.h>

int start_http_server();

int main(int argrc, const char ** argv)
{
    std::cout << "CWMP_pp start" << std::endl;
    // restore data from last launch
    // get ACS data from config
    
    // start http server
    start_http_server(); 

    // init event_engine 
    std::cout << "CWMP_pp finish" << std::endl;
    return 0;
}

int start_http_server()
{
    using namespace std;
    using server_sp = unique_ptr<evhttp, decltype(&evhttp_free)> ;
    try {
        if( !event_init() ) throw( runtime_error("Failed to init libevent") ) ;
        char const srv_addr[] = "127.0.0.1" ; // change to config
        uint16_t srv_port     = 5555        ; // -=-
        server_sp server( evhttp_start(srv_addr, srv_port), &evhttp_free );
        if( !server ) throw( runtime_error("Failed to init http server") ) ;

        // on request action
        auto on_req = [] ( evhttp_request * req, void * ) {
            auto out_buf = evhttp_request_get_output_buffer(req);
            if( !out_buf ) return;
            evbuffer_add_printf( out_buf, 
                "<html><body><center><h1>Hello World!</h1></center></body></html>");
            evhttp_send_reply( req, HTTP_OK, "",  out_buf );
        };
        
        evhttp_set_gencb( server.get(), on_req, nullptr );
        if( event_dispatch() == -1 ) 
            throw( runtime_error("Failed to run message loop") ) ;
        return 0; // we are happy and little bit sad that all's over
    }
    catch( exception& err ) { cerr << "Error: " << err.what() << endl; }
    catch( ... ) { cerr << "Unknown exception" << endl; }
    return -1; // we're here only if catched something
}
