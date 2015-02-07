/* \file timing_harness.cpp
 * Copyright (c) 2015 Thomas S. Phillips.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Compile me with:
// g++ -std=c++11 -pthread -lpcap timing_harness.cpp -o timing_harness

#include <chrono>
#include <iostream>
#include <pcap.h>

/**
 * Sample Throughputs:
 * 1Gb/s link
 * Max frame rate: 1,488,096 frames per second ( 0.67 us/frame)
 * Min frame rate:    81,274 frames per second (12.30 us/frame)
 *
 * References
 * http://www.cisco.com/web/about/security/intelligence/network_performance_metrics.html
 */
void callback1 (
  u_char *arg,
  const struct pcap_pkthdr* pkthdr,
  const u_char* packet
  )
{
  // This function should process an Ethernet frame.
  // Plug in code to do "work."
} // callback1()

void callback2 (
  u_char *arg,
  const struct pcap_pkthdr* pkthdr,
  const u_char* packet
  )
{
  // This function should process an Ethernet frame.
  // Plug in code to do "work."
} // callback2()

/**
 * Main loop for reading passive interfaces.
 * See: http://linux.die.net/man/3/pcap_dispatch
 * See: http://linux.die.net/man/3/pcap_setnonblock
 */
void loop(const char* interface1, const char* interface2) {

  // libpcap variables
  char errbuf[PCAP_ERRBUF_SIZE]; // Error buffer for libpcap.
  pcap_t* handle1 = nullptr;
  pcap_t* handle2 = nullptr;

  // Initialize interface 1
  if (interface1 != nullptr) {
    handle1 = pcap_open_live(interface1, BUFSIZ, 1, 1000, errbuf);
    if (handle1 == nullptr) {
      std::cerr << "ERROR: (interface1) pcap_open_live(): " << errbuf << std::endl;
      exit(1);
    } // if open failed
    if (pcap_setnonblock(handle1, 1, errbuf) == -1) {
      std::cerr << "ERROR: (interface1) pcap_setnonblock(): " << errbuf << std::endl;
      exit(1);
    } // if nonblock error
    std::cout << "Initialized " << interface1 << std::endl;
  } // if interface1

  // Initialize interface 2
  if (interface2 != nullptr) {
    handle2 = pcap_open_live(interface2, BUFSIZ, 1, 1000, errbuf);
    if (handle2 == nullptr) {
      std::cerr << "ERROR: (interface2) pcap_open_live(): " << errbuf << std::endl;
      exit(1);
    } // if open failed
    if (pcap_setnonblock(handle2, 1, errbuf) == -1) {
      std::cerr << "ERROR: (interface2) pcap_setnonblock(): " << errbuf << std::endl;
      exit(1);
    } // if nonblock error
    std::cout << "Initialized " << interface2 << std::endl;
  } // if interface2

  // Capture Ethernet frames in an infinite loop.
  while (true) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> finish;
    int frame_count1;
    int frame_count2;

    // Capture on interface 1
    start = std::chrono::high_resolution_clock::now();
    if (handle1 != nullptr) {
      frame_count1 = pcap_dispatch(handle1, -1, callback1, NULL);
      if (frame_count1 > 0) {
        finish = std::chrono::high_resolution_clock::now();
        std::cout << interface1 << ": " << frame_count1 << " frames in " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << " ns\n";
      } // if any frames captured
    } // if handle1

    // Capture on interface 2
    start = std::chrono::high_resolution_clock::now();
    if (handle2 != nullptr) {
      frame_count2 = pcap_dispatch(handle2, -1, callback2, NULL);
      if (frame_count2 > 0) {
        finish = std::chrono::high_resolution_clock::now();
        std::cout << interface2 << ": " << frame_count2 << " frames in " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << " ns\n";
      } // if any frames captured
    } // if handle2

  } // while true
} // loop()

/**
 * main() function
 */
int main(int argc, char* argv[]) {
  const char* interface1; // E.g., "eth0"
  const char* interface2; // E.g., "eth1"

  std::cout << "Ethernet Timing Harness" << std::endl;

  // if arg1 specified
  if (argc > 1) {
    interface1 = argv[1];
  } else {
    // Exit if there are no arguments
    exit(0);
  } // if-else

  // if arg2 specified
  if (argc > 2) {
    interface2 = argv[2];
  } // if

  // main loop (which is infinite)
  loop(interface1, interface2);

  // This code is never reached, but returning a value makes a happy compiler
  return 0;
} // main()
