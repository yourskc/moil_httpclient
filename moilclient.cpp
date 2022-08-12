/*
 *    Copyright (c) <2002-2005> <Jean-Philippe Barrette-LaPierre>
 *    
 *    Permission is hereby granted, free of charge, to any person obtaining
 *    a copy of this software and associated documentation files 
 *    (curlpp), to deal in the Software without restriction, 
 *    including without limitation the rights to use, copy, modify, merge,
 *    publish, distribute, sublicense, and/or sell copies of the Software,
 *    and to permit persons to whom the Software is furnished to do so, 
 *    subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included
 *    in all copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 *    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
* \file
* Using WriteStream option.
* 
*/


#include <sstream>
#include <cstdlib>

#include <fstream>
#include <iostream>

#include <stdio.h>
#include <string.h>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

using namespace std;
int main(int argc, char *argv[])
{

  const char *url = "localhost:1111/panorama.jpg?camerasensorwidth=1.4&camerasensorheight=1.4&icx=1320.0&icy=1017.0&ratio=1.048&imagewidth=2592&imageheight=1944&calibrationratio=3.4&para0=0&para1=0&para2=0&para3=10.11&para4=-85.241&para5=282.21&apmode=2&w_dest=2592&h_dest=1944";

// size_t length = 2000000;
char pBuf[2000000];
std::stringstream out; 
std::ofstream myFile("panorama.jpg");

  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;
cout << out.str().size() << endl;
    // Set the writer callback to enable cURL 
    // to write result in a memory area
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    request.setOpt(new curlpp::options::WriteStream(&out));

    // Setting the URL to retrive.
    request.setOpt(new curlpp::options::Url(url));

    request.perform();
cout << out.str().size() << endl;    
    int size = out.str().size();

// 1. output the received data to a file
    myFile << out.rdbuf(); 
	  myFile.flush();

// 2. check the data in the buffer. for opencv, save it to a mat for other processes  
    // out >> pBuf;  // not success, only 61 bytes copied 
    memcpy( pBuf, out.str().c_str(), size);  
    fstream file2;
    file2.open("buffer.jpg", ios::out | ios::trunc);
    file2.write(pBuf, size);  
    file2.close();    

    return EXIT_SUCCESS;
  }
  catch ( curlpp::LogicError & e ) {
    std::cout << e.what() << std::endl;
  }
  catch ( curlpp::RuntimeError & e ) {
    std::cout << e.what() << std::endl;
  }

  return EXIT_FAILURE;
}
