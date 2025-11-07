//Sam Emison
//11/06/2025
//Main.cpp

#include <iostream>
#include <string>
#include <curl/curl.h>

//Function to write fetched data into a string
size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

int main() {
  //Asks for URL
  std::string url;
  std::cout << "Enter URL: ";
  std::cin >> url;

  //Initialize curl
  CURL* curl = curl_easy_init();
  if(curl) {
    std::string readBuffer;

    //Options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    //Does the request
    CURLcode res = curl_easy_perform(curl);

    //Clean up
    curl_easy_cleanup(curl);

    if(res == CURLE_OK) {
      std::cout << readBuffer << std::endl; //Prints content
    }
    else {
      std::cerr << "Error fetching page: " << curl_easy_strerror(res) << std::endl;
    }
  }
  else {
    std::cerr << "Failed to initialize CURL" << std::endl;
  }

  return 0;
}

