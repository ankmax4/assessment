/*

In this example, we use the curl_easy_init function to initialize a cURL session. The curl_easy_setopt function is used to
configure various options for the request, such as the URL to download the image from and a callback function that will be used to write the data to a local file.
The curl_easy_perform function is then used to send the request and receive the response.
The response data is written to a local file using the ofstream class, which is a C++ standard library class for output file streams.
The write_data function is the callback function that will be called by cURL for each chunk of data received. The function writes the data to the output file stream.
*/



#include <iostream>
#include <fstream>
#include <curl/curl.h>

size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
  std::ofstream *stream = (std::ofstream*)userdata;
  stream->write(ptr, size * nmemb);
  return size * nmemb;
}

int main(void) {
  CURL *curl;
  CURLcode res;
  std::ofstream ofs;

  curl = curl_easy_init();
  if (curl) {
    ofs.open("image.jpg", std::ios::binary);

    curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com/image.jpg");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);

    res = curl_easy_perform(curl);

    /* Check for errors */
    if (res != CURLE_OK) {
      std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
    }

    /* Clean up */
    curl_easy_cleanup(curl);
    ofs.close();
  }

  return 0;
}
