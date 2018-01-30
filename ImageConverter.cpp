#include<iostream>
#include <fstream>
#include<cstdio>
#include<string>
#include<vector>
#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/opencv.hpp>

#include <alpr.h>

// memory consumption monitoring
#include<mach/mach.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>


using namespace cv;
using namespace std;
const char* _filename = "Car image_second worst resolution.jpg";


int main(int argc, char* argv[])
{
    
    // =============== memory consumption ===============
    cout << endl << endl << "memory consumption:" << endl;
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count))
    {
        long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        printf("free memory: %lld\nused memory: %lld\n", free_memory, used_memory);
    }
    cout << endl;

    // =============== memory consumption ===============
  
	IplImage *img;
   
	if (!strcmp(argv[1], "0")) {
		cout << "parsing built-in image..." << endl;
		img = cvLoadImage(_filename);
	} else {
		cout << "parsing assigned image..." << endl;
		img = cvLoadImage(argv[1]);
	}

	// Initialize the library using United States-style license plates.  
    // You can use other countries/regions as well (for example: "eu", "au", or "kr").
/*    
    alpr::Alpr openalpr("us", "/openalpr/src/build/config/openalpr.conf");

    // Optionally, you can specify the top N possible plates to return (with confidences). The default is ten.
    openalpr.setTopN(5);

    // Optionally, you can provide the library with a region for pattern matching. This improves accuracy by 
    // comparing the plate text with the regional pattern.
    openalpr.setDefaultRegion("md");

    // Make sure the library loads before continuing.  
    // For example, it could fail if the config/runtime_data is not found.
    if (openalpr.isLoaded() == false){
        std::cerr << "Error loading OpenALPR" << std::endl;
        return 1;
    }

    // Recognize an image file. Alternatively, you could provide the image bytes in-memory.
    alpr::AlprResults results = openalpr.recognize(argv[1]);

    // Carefully observe the results. There may be multiple plates in an image, 
    // and each plate returns the top N candidates.
    for (int i = 0; i < results.plates.size(); i++){
		alpr::AlprPlateResult plate = results.plates[i];
		cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << endl;

		for (int k = 0; k < plate.topNPlates.size(); k++){
			alpr::AlprPlate candidate = plate.topNPlates[k];
			cout << "    - " << candidate.characters << "\t confidence: " << candidate.overall_confidence << endl;
		}
    }
    */  
    int p[3];

    p[0] = CV_IMWRITE_JPEG_QUALITY;
    p[1] = 5;
    p[2] = 0;
    cvSaveImage("CompressedImage.jpg", img, p);

    cout << "Image compressed as CompressedImage." << endl;
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count))
    {
        long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        printf("free memory: %lld\nused memory: %lld\n", free_memory, used_memory);
    }
    cout << endl;
    
	// convert to greyscale
	//Mat image;
	//image = imread("CompressedImage.jpg", 1);
	//Mat gray_image;
	//cvtColor( image, gray_image, COLOR_BGR2GRAY );
	//imwrite( "GreyImage.jpg", gray_image );

	return 0;
}