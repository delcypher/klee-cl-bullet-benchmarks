/* ============================================================

Copyright (c) 2009 Advanced Micro Devices, Inc.  All rights reserved.
 
Redistribution and use of this material is permitted under the following 
conditions:
 
Redistributions must retain the above copyright notice and all terms of this 
license.
 
In no event shall anyone redistributing or accessing or using this material 
commence or participate in any arbitration or legal action relating to this 
material against Advanced Micro Devices, Inc. or any copyright holders or 
contributors. The foregoing shall survive any expiration or termination of 
this license or any agreement or access or use related to this material. 

ANY BREACH OF ANY TERM OF THIS LICENSE SHALL RESULT IN THE IMMEDIATE REVOCATION 
OF ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE THIS MATERIAL.

THIS MATERIAL IS PROVIDED BY ADVANCED MICRO DEVICES, INC. AND ANY COPYRIGHT 
HOLDERS AND CONTRIBUTORS "AS IS" IN ITS CURRENT CONDITION AND WITHOUT ANY 
REPRESENTATIONS, GUARANTEE, OR WARRANTY OF ANY KIND OR IN ANY WAY RELATED TO 
SUPPORT, INDEMNITY, ERROR FREE OR UNINTERRUPTED OPERA TION, OR THAT IT IS FREE 
FROM DEFECTS OR VIRUSES.  ALL OBLIGATIONS ARE HEREBY DISCLAIMED - WHETHER 
EXPRESS, IMPLIED, OR STATUTORY - INCLUDING, BUT NOT LIMITED TO, ANY IMPLIED 
WARRANTIES OF TITLE, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, 
ACCURACY, COMPLETENESS, OPERABILITY, QUALITY OF SERVICE, OR NON-INFRINGEMENT. 
IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, REVENUE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED OR BASED ON ANY THEORY OF LIABILITY 
ARISING IN ANY WAY RELATED TO THIS MATERIAL, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE. THE ENTIRE AND AGGREGATE LIABILITY OF ADVANCED MICRO DEVICES, 
INC. AND ANY COPYRIGHT HOLDERS AND CONTRIBUTORS SHALL NOT EXCEED TEN DOLLARS 
(US $10.00). ANYONE REDISTRIBUTING OR ACCESSING OR USING THIS MATERIAL ACCEPTS 
THIS ALLOCATION OF RISK AND AGREES TO RELEASE ADVANCED MICRO DEVICES, INC. AND 
ANY COPYRIGHT HOLDERS AND CONTRIBUTORS FROM ANY AND ALL LIABILITIES, 
OBLIGATIONS, CLAIMS, OR DEMANDS IN EXCESS OF TEN DOLLARS (US $10.00). THE 
FOREGOING ARE ESSENTIAL TERMS OF THIS LICENSE AND, IF ANY OF THESE TERMS ARE 
CONSTRUED AS UNENFORCEABLE, FAIL IN ESSENTIAL PURPOSE, OR BECOME VOID OR 
DETRIMENTAL TO ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR 
CONTRIBUTORS FOR ANY REASON, THEN ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE 
THIS MATERIAL SHALL TERMINATE IMMEDIATELY. MOREOVER, THE FOREGOING SHALL 
SURVIVE ANY EXPIRATION OR TERMINATION OF THIS LICENSE OR ANY AGREEMENT OR 
ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE IS HEREBY PROVIDED, AND BY REDISTRIBUTING OR ACCESSING OR USING THIS 
MATERIAL SUCH NOTICE IS ACKNOWLEDGED, THAT THIS MATERIAL MAY BE SUBJECT TO 
RESTRICTIONS UNDER THE LAWS AND REGULATIONS OF THE UNITED STATES OR OTHER 
COUNTRIES, WHICH INCLUDE BUT ARE NOT LIMITED TO, U.S. EXPORT CONTROL LAWS SUCH 
AS THE EXPORT ADMINISTRATION REGULATIONS AND NATIONAL SECURITY CONTROLS AS 
DEFINED THEREUNDER, AS WELL AS STATE DEPARTMENT CONTROLS UNDER THE U.S. 
MUNITIONS LIST. THIS MATERIAL MAY NOT BE USED, RELEASED, TRANSFERRED, IMPORTED,
EXPORTED AND/OR RE-EXPORTED IN ANY MANNER PROHIBITED UNDER ANY APPLICABLE LAWS, 
INCLUDING U.S. EXPORT CONTROL LAWS REGARDING SPECIFICALLY DESIGNATED PERSONS, 
COUNTRIES AND NATIONALS OF COUNTRIES SUBJECT TO NATIONAL SECURITY CONTROLS. 
MOREOVER, THE FOREGOING SHALL SURVIVE ANY EXPIRATION OR TERMINATION OF ANY 
LICENSE OR AGREEMENT OR ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE REGARDING THE U.S. GOVERNMENT AND DOD AGENCIES: This material is 
provided with "RESTRICTED RIGHTS" and/or "LIMITED RIGHTS" as applicable to 
computer software and technical data, respectively. Use, duplication, 
distribution or disclosure by the U.S. Government and/or DOD agencies is 
subject to the full extent of restrictions in all applicable regulations, 
including those found at FAR52.227 and DFARS252.227 et seq. and any successor 
regulations thereof. Use of this material by the U.S. Government and/or DOD 
agencies is acknowledgment of the proprietary rights of any copyright holders 
and contributors, including those of Advanced Micro Devices, Inc., as well as 
the provisions of FAR52.227-14 through 23 regarding privately developed and/or 
commercial computer software.

This license forms the entire agreement regarding the subject matter hereof and 
supersedes all proposals and prior discussions and writings between the parties 
with respect thereto. This license does not affect any ownership, rights, title,
or interest in, or relating to, this material. No terms of this license can be 
modified or waived, and no breach of this license can be excused, unless done 
so in a writing signed by all affected parties. Each term of this license is 
separately enforceable. If any term of this license is determined to be or 
becomes unenforceable or illegal, such term shall be reformed to the minimum 
extent necessary in order for this license to remain in effect in accordance 
with its terms as modified by such reformation. This license shall be governed 
by and construed in accordance with the laws of the State of Texas without 
regard to rules on conflicts of law of any state or jurisdiction or the United 
Nations Convention on the International Sale of Goods. All disputes arising out 
of this license shall be subject to the jurisdiction of the federal and state 
courts in Austin, Texas, and all defenses are hereby waived concerning personal 
jurisdiction and venue of these courts.

============================================================ */


#include "TemplateC.hpp"

#ifdef __KLEE
#include <klee/klee.h>
#endif

/*
 * \brief Host Initialization 
 *        Allocate and initialize memory 
 *        on the host. Print input array. 
 */
void
initializeHost(void)
{
	width				= 256;
	input				= NULL;
	output				= NULL;
	multiplier			= 2;

	/////////////////////////////////////////////////////////////////
	// Allocate and initialize memory used by host 
	/////////////////////////////////////////////////////////////////
    cl_uint sizeInBytes = width * sizeof(cl_uint);
    input = (cl_uint *) malloc(sizeInBytes);
	if(input == NULL)
	{
		printf("Error: Failed to allocate input memory on host\n");
		return; 
	}

    output = (cl_uint *) malloc(sizeInBytes);
	if(output == NULL)
	{
		printf("Error: Failed to allocate output memory on host\n");
		return; 
	}

#ifdef __KLEE
    klee_make_symbolic(input, sizeInBytes, "input");
#else
    for(cl_uint i = 0; i < width; i++)
        input[i] = i;
#endif

	// print input array
	print1DArray("Input", input, width);
}

/*
 * Converts the contents of a file into a string
 */
char *
convertToString(const char *filename)
{
	size_t size;
	char*  str;

	std::fstream f(filename, (std::fstream::in | std::fstream::binary));

	if(f.is_open())
	{
		size_t fileSize;
		f.seekg(0, std::fstream::end);
		size = fileSize = f.tellg();
		f.seekg(0, std::fstream::beg);

		str = new char[size+1];
		if(!str)
		{
			f.close();
			return NULL;
		}

		f.read(str, fileSize);
		f.close();
		str[size] = '\0';
	
		return str;
	}
	return NULL;
}

/*
 * \brief OpenCL related initialization 
 *        Create Context, Device list, Command Queue
 *        Create OpenCL memory buffer objects
 *        Load CL file, compile, link CL source 
 *		  Build program and kernel objects
 */
void
initializeCL(void)
{
    cl_int status = 0;
    size_t deviceListSize;

    /*
     * Have a look at the available platforms and pick either
     * the AMD one if available or a reasonable default.
     */

    cl_uint numPlatforms;
    cl_platform_id platform = NULL;
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
    if(status != CL_SUCCESS)
    {
        printf("Error: Getting Platforms. (clGetPlatformsIDs)\n");
        return;
    }
    
    if(numPlatforms > 0)
    {
        cl_platform_id* platforms = (cl_platform_id *)malloc(numPlatforms*sizeof(cl_platform_id));
        status = clGetPlatformIDs(numPlatforms, platforms, NULL);
        if(status != CL_SUCCESS)
        {
            printf("Error: Getting Platform Ids. (clGetPlatformsIDs)\n");
            return;
        }
        for(unsigned int i=0; i < numPlatforms; ++i)
        {
            char pbuff[100];
            status = clGetPlatformInfo(
                        platforms[i],
                        CL_PLATFORM_VENDOR,
                        sizeof(pbuff),
                        pbuff,
                        NULL);
            if(status != CL_SUCCESS)
            {
                printf("Error: Getting Platform Info. (clGetPlatformInfo)\n");
                return;
            }
            platform = platforms[i];
            if(!strcmp(pbuff, "Advanced Micro Devices, Inc."))
            {
                break;
            }
        }
        delete platforms;
    }

    if(NULL == platform)
    {
        puts("NULL platform found so Exiting Application.");
        return;
    }

    /*
     * If we could find our platform, use it. Otherwise use just available platform.
     */

    cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0 };


	/////////////////////////////////////////////////////////////////
	// Create an OpenCL context
	/////////////////////////////////////////////////////////////////
    context = clCreateContextFromType(cps, 
                                      CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_CPU, 
                                      NULL, 
                                      NULL, 
                                      &status);
    if(status != CL_SUCCESS) 
	{  
		printf("Error: Creating Context. (clCreateContextFromType)\n");
		return; 
	}

    /* First, get the size of device list data */
    status = clGetContextInfo(context, 
                              CL_CONTEXT_DEVICES, 
                              0, 
                              NULL, 
                              &deviceListSize);
    if(status != CL_SUCCESS) 
	{  
		printf(
			"Error: Getting Context Info \
		    (device list size, clGetContextInfo)\n");
		return;
	}

	/////////////////////////////////////////////////////////////////
	// Detect OpenCL devices
	/////////////////////////////////////////////////////////////////
    devices = (cl_device_id *)malloc(deviceListSize);
	if(devices == 0)
	{
		printf("Error: No devices found.\n");
		return;
	}

    /* Now, get the device list data */
    status = clGetContextInfo(
			     context, 
                 CL_CONTEXT_DEVICES, 
                 deviceListSize, 
                 devices, 
                 NULL);
    if(status != CL_SUCCESS) 
	{ 
		printf("Error: Getting Context Info \
		    (device list, clGetContextInfo)\n");
		return;
	}

	/////////////////////////////////////////////////////////////////
	// Create an OpenCL command queue
	/////////////////////////////////////////////////////////////////
    commandQueue = clCreateCommandQueue(
					   context, 
                       devices[0], 
                       0, 
                       &status);
    if(status != CL_SUCCESS) 
	{ 
		printf("Creating Command Queue. (clCreateCommandQueue)\n");
		return;
	}

	/////////////////////////////////////////////////////////////////
	// Create OpenCL memory buffers
	/////////////////////////////////////////////////////////////////
    inputBuffer = clCreateBuffer(
				      context, 
                      CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
                      sizeof(cl_uint) * width,
                      input, 
                      &status);
    if(status != CL_SUCCESS) 
	{ 
		printf("Error: clCreateBuffer (inputBuffer)\n");
		return;
	}

    outputBuffer = clCreateBuffer(
					   context, 
                       CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
                       sizeof(cl_uint) * width,
                       output, 
                       &status);
    if(status != CL_SUCCESS) 
	{ 
		printf("Error: clCreateBuffer (outputBuffer)\n");
		return;
	}


	/////////////////////////////////////////////////////////////////
	// Load CL file, build CL program object, create CL kernel object
	/////////////////////////////////////////////////////////////////
    const char * filename  = "TemplateC_Kernels.cl";
    const char * source    = convertToString(filename);
    size_t sourceSize[]    = { strlen(source) };

    program = clCreateProgramWithSource(
			      context, 
                  1, 
                  &source,
				  sourceSize,
                  &status);
	if(status != CL_SUCCESS) 
	{ 
	    printf("Error: Loading Binary into cl_program \
			   (clCreateProgramWithBinary)\n");
	  return;
	}

    /* create a cl program executable for all the devices specified */
    status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);
    if(status != CL_SUCCESS) 
	{ 
		printf("Error: Building Program (clBuildProgram)\n");
		return; 
	}

    /* get a kernel object handle for a kernel with the given name */
    kernel = clCreateKernel(program, "templateKernel", &status);
    if(status != CL_SUCCESS) 
	{  
		printf("Error: Creating Kernel from program. (clCreateKernel)\n");
		return;
	}
}


/*
 * \brief Run OpenCL program 
 *		  
 *        Bind host variables to kernel arguments 
 *		  Run the CL kernel
 */
void 
runCLKernels(void)
{
    cl_int   status;
    cl_event events[2];
    size_t globalThreads[1];
    size_t localThreads[1];
    
    globalThreads[0] = width;
    localThreads[0]  = 1;

    /*** Set appropriate arguments to the kernel ***/
    /* the output array to the kernel */
    status = clSetKernelArg(
                    kernel, 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&outputBuffer);
    if(status != CL_SUCCESS) 
	{ 
		printf("Error: Setting kernel argument. (output)\n");
		return;
	}

    /* the input array to the kernel */
    status = clSetKernelArg(
                    kernel, 
                    1, 
                    sizeof(cl_mem), 
                    (void *)&inputBuffer);
    if(status != CL_SUCCESS) 
	{ 
		printf("Error: Setting kernel argument. (input)\n");
		return;
	}

    /*multiplier*/
    status = clSetKernelArg(
                    kernel, 
                    2, 
                    sizeof(cl_uint), 
                    (void *)&multiplier);
    if(status != CL_SUCCESS) 
	{ 
		printf( "Error: Setting kernel argument. (multiplier)\n");
		return;
	}

    /* 
     * Enqueue a kernel run call.
     */
    status = clEnqueueNDRangeKernel(
			     commandQueue,
                 kernel,
                 1,
                 NULL,
                 globalThreads,
                 localThreads,
                 0,
                 NULL,
                 &events[0]);
    if(status != CL_SUCCESS) 
	{ 
		printf(
			"Error: Enqueueing kernel onto command queue. \
			(clEnqueueNDRangeKernel)\n");
		return;
	}


    /* wait for the kernel call to finish execution */
    status = clWaitForEvents(1, &events[0]);
    if(status != CL_SUCCESS) 
	{ 
		printf(
		    "Error: Waiting for kernel run to finish. \
			(clWaitForEvents)\n");
		return;
	}

    status = clReleaseEvent(events[0]);
    if(status != CL_SUCCESS)
    {
        printf("Error: clReleaseEvent. (events[0])\n");
        return;
    }

    /* Enqueue readBuffer*/
    status = clEnqueueReadBuffer(
                commandQueue,
                outputBuffer,
                CL_TRUE,
                0,
                width * sizeof(cl_uint),
                output,
                0,
                NULL,
                &events[1]);
    
    if(status != CL_SUCCESS) 
	{
        printf( 
    		"Error: clEnqueueReadBuffer failed. \
             (clEnqueueReadBuffer)\n");
    }
    
    /* Wait for the read buffer to finish execution */
    status = clWaitForEvents(1, &events[1]);
    if(status != CL_SUCCESS) 
	{ 
		printf(
		    "Error: Waiting for read buffer call to finish. \
			(clWaitForEvents)\n");
		return;
	}
    
    status = clReleaseEvent(events[1]);
    if(status != CL_SUCCESS)
    {
        printf("Error: clReleaseEvent. (events[1])\n");
        return;
    }

}


/*
 * \brief Release OpenCL resources (Context, Memory etc.) 
 */
void 
cleanupCL(void)
{
    cl_int status;

    status = clReleaseKernel(kernel);
    if(status != CL_SUCCESS)
	{
		printf("Error: In clReleaseKernel \n");
		return; 
	}
    status = clReleaseProgram(program);
    if(status != CL_SUCCESS)
	{
		printf("Error: In clReleaseProgram\n");
		return; 
	}
    status = clReleaseMemObject(inputBuffer);
    if(status != CL_SUCCESS)
	{
		printf("Error: In clReleaseMemObject (inputBuffer)\n");
		return; 
	}
	status = clReleaseMemObject(outputBuffer);
    if(status != CL_SUCCESS)
	{
		printf("Error: In clReleaseMemObject (outputBuffer)\n");
		return; 
	}
    status = clReleaseCommandQueue(commandQueue);
    if(status != CL_SUCCESS)
	{
		printf("Error: In clReleaseCommandQueue\n");
		return;
	}
    status = clReleaseContext(context);
    if(status != CL_SUCCESS)
	{
		printf("Error: In clReleaseContext\n");
		return;
	}
}


/* 
 * \brief Releases program's resources 
 */
void
cleanupHost(void)
{
    if(input != NULL)
    {
        free(input);
        input = NULL;
    }
	if(output != NULL)
	{
		free(output);
		output = NULL;
	}
    if(devices != NULL)
    {
        free(devices);
        devices = NULL;
    }
}


/*
 * \brief Print no more than 256 elements of the given array.
 *
 *        Print Array name followed by elements.
 */
void print1DArray(
		 const char *arrayName, 
         const unsigned int * arrayData, 
         const unsigned int length)
{
    cl_uint i;
    cl_uint numElementsToPrint = (256 < length) ? 256 : length;

    printf("\n%s:\n", arrayName);
    for(i = 0; i < numElementsToPrint; ++i)
    {
#ifdef __KLEE
        klee_print_expr("arrayData", arrayData[i]);
#else
        printf("%u ", arrayData[i]);
#endif
    }
    puts("");
}

void verify()
{
    bool passed = true;
    for(unsigned int i = 0; i < width; ++i)
        if(input[i] * multiplier != output[i])
            passed = false;

    if(passed == true)
        puts("Passed!");
    else
        puts("Failed!");
}

int 
main(int argc, char * argv[])
{
    // Initialize Host application 
	initializeHost(); 

    // Initialize OpenCL resources
    initializeCL();

    // Run the CL program
    runCLKernels();

    // Print output array
    print1DArray("Output", output, width);

    // verify output
    verify();

    // Releases OpenCL resources 
    cleanupCL();

    // Release host resources
    cleanupHost();

    return 0;
}
