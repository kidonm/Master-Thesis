#include <iostream>
#include <chrono>
#include <ctime>

#include "iphash.h"
#include "MurmurHash3.h"
#include "MurmurHash2.h"
#include "Spooky.h"
#include "lookup3.cpp"
#include "SuperFastHash.cpp"

uint32_t octets_dataset [][4] = 
    { {147,32,184,48}
    , {147,32,115,47}
    , {147,230,27,233}
    , {195,113,55,9}
    , {195,113,36,116}
    , {147,251,110,22}
    , {147,228,89,216}
    , {147,230,72,120}
    , {147,229,179,151}
    , {78,128,254,220}
    , {147,32,97,216}
    , {195,113,233,229}
    , {195,178,72,28}
    , {195,113,128,16}
    , {195,113,187,35}
    , {195,113,40,51}
    , {147,32,101,79}
    , {147,228,41,56}
    , {147,230,21,11}
    , {78,128,253,196}
    , {147,228,101,153}
    , {147,228,41,155}
    , {147,32,198,3}
    , {78,128,204,99}
    , {195,113,47,143}
    , {147,32,204,145}
    , {195,113,119,5}
    , {147,32,138,106}
    , {78,128,255,177}
    , {147,229,179,68}
    , {147,229,107,95}
    , {147,251,238,9}
    , {147,32,197,101}
    , {158,196,54,80}
    , {147,32,242,91}
    , {147,229,85,101}
    , {147,230,173,19}
    , {160,217,215,241}
    , {146,102,248,223}
    , {147,228,179,28}
    , {193,84,172,226}
    , {147,229,1,1}
    , {147,32,87,60}
    , {147,229,12,110}
    , {195,113,226,126}
    , {147,229,179,74}
    , {158,196,112,46}
    , {147,228,174,213}
    , {147,229,169,104}
    , {147,32,48,3}
    , {158,196,175,72}
    , {147,32,232,135}
    , {195,113,31,140}
    , {158,196,42,55}
    , {78,128,166,223}
    , {158,196,202,38}
    , {195,113,82,30}
    , {147,32,163,54}
    , {147,228,136,233}
    , {147,251,85,23}
    , {147,229,104,76}
    , {147,251,162,191}
    , {195,113,230,249}
    , {147,229,220,160}
    , {147,229,11,15}
    , {160,217,96,36}
    , {147,229,159,174}
    , {147,251,221,185}
    , {146,102,141,51}
    , {147,32,6,14}
    , {193,84,40,206}
    , {147,231,100,205}
    , {147,229,220,159}
    , {146,102,25,5}
    , {195,113,48,131}
    , {147,229,86,141}
    , {147,231,32,17}
    , {147,231,161,65}
    , {147,228,89,111}
    , {158,194,75,1}
    , {158,196,72,126}
    , {147,33,180,199}
    , {147,32,108,165}
    , {195,113,126,192}
    , {147,229,86,245}
    , {195,113,12,38}
    , {195,178,78,184}
    , {195,113,41,39}
    , {147,229,183,247}
    , {195,113,89,71}
    , {78,128,185,33}
    , {147,228,13,34}
    , {195,113,231,158}
    , {147,229,216,26}
    , {160,217,229,39}
    , {158,194,34,209}
    , {147,251,129,195}
    , {147,32,162,248}
    , {158,194,148,1}
    , {147,229,86,245}
    };

typedef struct {
    const char *identifier;
    double elapsed_avg_seconds = 0; 
} TimeResult;

typedef struct {
    std::chrono::time_point<std::chrono::system_clock> start, end; 
    std::chrono::duration<double> elapsed_seconds;
} TimeMeasurement;

void printMeasurementResults(TimeResult *res) {
    std::cout 
        << res->identifier 
	<< " : " 
	<< res->elapsed_avg_seconds
	<< " seconds\n";
}

int main(void) {
    const unsigned int experiments = 50;
    const unsigned int hashDataSetTimes = 1000000;
    const unsigned int hashes = 7;
    TimeMeasurement measurement[hashes][experiments];
    TimeResult results[hashes];

    uint32_t testIP = 0;
    uint32_t testOutput = 0;

    // INITIALIZATION
    results[0].identifier = "MurmurHash3";
    results[1].identifier = "IPHash 1";
    results[2].identifier = "IPHash 2";
    results[3].identifier = "MurmurHash2";
    results[4].identifier = "SpookyHash";
    results[5].identifier = "lookup3";
    results[6].identifier = "SuperFastHash";


    // EXPERIMENTS
    for (unsigned int experiment = 0; experiment < experiments; experiment++) {
        // MURMURHASH3
        measurement[0][experiment].start = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < hashDataSetTimes; i++) {
            for (unsigned int ipc = 0; ipc < 100; ipc++) {
                for (unsigned int octet = 0; octet < 4; octet++) {
                    testIP += octets_dataset[ipc][octet];
                    testIP = testIP << 8;
                }
                MurmurHash3_x86_32(&testIP, 32, 1, &testOutput);  
            }
        }
        measurement[0][experiment].end = std::chrono::system_clock::now();
        measurement[0][experiment].elapsed_seconds 
	    = measurement[0][experiment].end-measurement[0][experiment].start;

        // IPHASH1
        measurement[1][experiment].start = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < hashDataSetTimes; i++) {
            for (unsigned int ipc = 0; ipc < 100; ipc++) {
                hash1
            	( octets_dataset[ipc][0]
            	, octets_dataset[ipc][1]
            	, octets_dataset[ipc][2]
            	, octets_dataset[ipc][3]
            	);  
            }
        }
        measurement[1][experiment].end = std::chrono::system_clock::now();
        measurement[1][experiment].elapsed_seconds 
	    = measurement[1][experiment].end-measurement[1][experiment].start;
        
        // IPHASH2
        measurement[2][experiment].start = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < hashDataSetTimes; i++) {
            for (unsigned int ipc = 0; ipc < 100; ipc++) {
                hash2
            	( octets_dataset[ipc][0]
            	, octets_dataset[ipc][1]
            	, octets_dataset[ipc][2]
            	, octets_dataset[ipc][3]
            	);  
            }
        }
        measurement[2][experiment].end = std::chrono::system_clock::now();
        measurement[2][experiment].elapsed_seconds 
	    = measurement[2][experiment].end-measurement[2][experiment].start;

        // MURMURHASH2
        measurement[3][experiment].start = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < hashDataSetTimes; i++) {
            for (unsigned int ipc = 0; ipc < 100; ipc++) {
                for (unsigned int octet = 0; octet < 4; octet++) {
                    testIP += octets_dataset[ipc][octet];
                    testIP = testIP << 8;
                }
                MurmurHash2(&testIP, 32, 1);  
            }
        }
        measurement[3][experiment].end = std::chrono::system_clock::now();
        measurement[3][experiment].elapsed_seconds 
	    = measurement[3][experiment].end-measurement[3][experiment].start;
	
        // SPOOKYHASH
        measurement[4][experiment].start = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < hashDataSetTimes; i++) {
            for (unsigned int ipc = 0; ipc < 100; ipc++) {
                for (unsigned int octet = 0; octet < 4; octet++) {
                    testIP += octets_dataset[ipc][octet];
                    testIP = testIP << 8;
                }
		SpookyHash::Hash32(&testIP, 32, 1);  
            }
        }
        measurement[4][experiment].end = std::chrono::system_clock::now();
        measurement[4][experiment].elapsed_seconds 
	    = measurement[4][experiment].end-measurement[4][experiment].start;
	
        // lookup3
        measurement[5][experiment].start = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < hashDataSetTimes; i++) {
            for (unsigned int ipc = 0; ipc < 100; ipc++) {
                for (unsigned int octet = 0; octet < 4; octet++) {
                    testIP += octets_dataset[ipc][octet];
                    testIP = testIP << 8;
                }
    		lookup3(&testIP, 32, 1);
            }
        }
        measurement[5][experiment].end = std::chrono::system_clock::now();
        measurement[5][experiment].elapsed_seconds 
	    = measurement[5][experiment].end-measurement[5][experiment].start;
	
        // SuperFastHash
        measurement[6][experiment].start = std::chrono::system_clock::now();
        for (unsigned int i = 0; i < hashDataSetTimes; i++) {
            for (unsigned int ipc = 0; ipc < 100; ipc++) {
                for (unsigned int octet = 0; octet < 4; octet++) {
                    testIP += octets_dataset[ipc][octet];
                    testIP = testIP << 8;
                }
    		SuperFastHash(&testIP, 32, 1, &testOutput);
            }
        }
        measurement[6][experiment].end = std::chrono::system_clock::now();
        measurement[6][experiment].elapsed_seconds 
	    = measurement[6][experiment].end-measurement[6][experiment].start;
    }

    for (unsigned int hash = 0; hash < hashes; hash++) {
        for (unsigned int experiment = 0; experiment < experiments; experiment++) {
	   results[hash].elapsed_avg_seconds += measurement[hash][experiment].elapsed_seconds.count();
        }
	   results[hash].elapsed_avg_seconds /= experiments;
    }

    for (unsigned int mes = 0; mes < hashes; mes++) {
        printMeasurementResults(&results[mes]);
    }

    return 0;
}
