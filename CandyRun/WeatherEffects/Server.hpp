//
//  Server.hpp
//  CandyRun
//
//  Created by Ciro De Vita on 11/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef Server_hpp
#define Server_hpp

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json/json.h>

class Server{
public:
    Server();
    ~Server();
    
    std::string getWeather();
private:
    std::string url = "http://193.205.230.6/products/wrf5/forecast/com63049";
    static std::size_t callback(const char* in, std::size_t size, std::size_t num,std::string* out);
};

#endif /* Server_hpp */
