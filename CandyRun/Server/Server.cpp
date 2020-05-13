//
//  Server.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 11/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "Server.hpp"

Server::Server(){}

Server::~Server(){}

size_t Server::callback(const char *in, std::size_t size, std::size_t num, std::string *out){
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

std::string Server::getWeather(){
    CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200)
    {
        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << jsonData["forecast"]["text"]["it"].toStyledString()<< std::endl;
            
            return jsonData["forecast"]["text"]["it"].toStyledString();
        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            return "Error";
        }
    }
    else{
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
        return "Error";
    }
}
