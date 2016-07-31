#include "Renderer.h"

#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <helper_functions.h>
#include <helper_cuda.h>
#include <helper_cuda_gl.h>
#include <iostream>

HRenderer::HRenderer(HCamera* Camera)
{

	PassCounter = 0;
	FPSCounter = 0;
	bFirstRenderPass = true;
	Image = new HImage(Camera->GetCameraData()->Resolution);
	InitGPUData(Camera->GetCameraData());

}

HRenderer::~HRenderer()
{
	// TODO: Destructor, free CUDA pointers, delete Image, CameraData etc.
}

HImage* HRenderer::Render()
{

	if (bFirstRenderPass)
	{
		// TODO: Should be renamed to bReset or similar. Happens when camera is moved, reset GPU memory etc
		// TODO: perhaps not even needed
		bFirstRenderPass = false;

	}

	++PassCounter;

	cudaStream_t CUDAStream;
	checkCudaErrors(cudaStreamCreate(&CUDAStream));
	checkCudaErrors(cudaGraphicsMapResources(1, &BufferResource, CUDAStream));

	// Launches CUDA kernel to modify Image pixels
	// Temporary test kernel for now
	HKernels::LaunchRenderKernel(
		Image,
		AccumulationBuffer,
		CameraData,
		PassCounter,
		Rays,
		Spheres,
		NumSpheres);

	checkCudaErrors(cudaGraphicsUnmapResources(1, &BufferResource, 0));
	checkCudaErrors(cudaStreamDestroy(CUDAStream));

	return Image;

}

void HRenderer::InitScene(HScene* Scene)
{

	NumSpheres = Scene->NumSpheres;
	checkCudaErrors(cudaMalloc(&Spheres, NumSpheres*sizeof(HSphere)));
	checkCudaErrors(cudaMemcpy(Spheres, Scene->Spheres, NumSpheres*sizeof(HSphere), cudaMemcpyHostToDevice));

	
	// TODO: Unified memory to skip this tedious deep copy
	/*HSphere* TempSpheres;
	checkCudaErrors(cudaMalloc(&SceneData, sizeof(HSceneData)));
	checkCudaErrors(cudaMalloc(&TempSpheres, Scene->GetSceneData()->NumSpheres * sizeof(HSphere)));
	checkCudaErrors(cudaMemcpy(this->SceneData, Scene->GetSceneData(), sizeof(HSceneData), cudaMemcpyHostToDevice));
	checkCudaErrors(cudaMemcpy(TempSpheres, Scene->GetSceneData()->Spheres, Scene->GetSceneData()->NumSpheres * sizeof(HSphere), cudaMemcpyHostToDevice));
	checkCudaErrors(cudaMemcpy(&(SceneData->Spheres), &TempSpheres, sizeof(HSphere*), cudaMemcpyHostToDevice));*/

	// This unified memory snipped doesn't work, copies data but crashes when trying to access
	// Spheres pointer in SceneData struct on GPU
	/*checkCudaErrors(cudaMallocManaged(&SceneData, sizeof(HSceneData)));
	checkCudaErrors(cudaMemcpy(this->SceneData, Scene->GetSceneData(), sizeof(HSceneData), cudaMemcpyHostToDevice));*/

}

void HRenderer::Reset()
{

}

void HRenderer::Resize(HCameraData* CameraData)
{
	// TODO: This does not work properly.
	// Does resize but the image but the rendering is messed up.
	// Seems to extend or reduce rendered dimension twice the amount needed
	// Unsure if it's a GL mapping issue or a CUDA kernel issue.

	FreeGPUData();

	Image->Resize(CameraData->Resolution.x, CameraData->Resolution.y);

	PassCounter = 0;

	InitGPUData(CameraData);

}

void HRenderer::CreateVBO(GLuint* Buffer, cudaGraphicsResource** BufferResource, unsigned int BufferFlags)
{

	assert(Buffer);

	// Create buffer
	glGenBuffers(1, Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *Buffer);

	// Initialize buffer
	glBufferData(GL_ARRAY_BUFFER, Image->NumPixels * sizeof(float3), 0, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Register VBO with CUDA and perform error checks
	checkCudaErrors(cudaGraphicsGLRegisterBuffer(BufferResource, *Buffer, BufferFlags));

}

void HRenderer::DeleteVBO(GLuint* Buffer, cudaGraphicsResource* BufferResource)
{

	// Unregister VBO with CUDA
	checkCudaErrors(cudaGraphicsUnregisterResource(BufferResource));

	// Delete VBO
	glBindBuffer(GL_ARRAY_BUFFER, *Buffer);
	glDeleteBuffers(GL_ARRAY_BUFFER, Buffer);
	*Buffer = 0;

}

void HRenderer::InitGPUData(HCameraData* CameraData)
{

	// Allocate memory on GPU for the accumulation buffer
	checkCudaErrors(cudaMalloc(&AccumulationBuffer, Image->NumPixels * sizeof(float3)));

	// Allocate memory on GPU for Camera data and copy over Camera data
	checkCudaErrors(cudaMalloc(&(this->CameraData), sizeof(HCameraData)));
	checkCudaErrors(cudaMemcpy(this->CameraData, CameraData, sizeof(HCameraData), cudaMemcpyHostToDevice));

	// Allocate memory on GPU for rays
	checkCudaErrors(cudaMalloc(&Rays, Image->NumPixels * sizeof(HRay)));

	// Allocate memory on GPU for 

	CreateVBO(&(Image->Buffer), &(this->BufferResource), cudaGraphicsRegisterFlagsNone);

	// Set up device synchronization stream
	cudaStream_t CUDAStream;
	checkCudaErrors(cudaStreamCreate(&CUDAStream));

	// Map graphics resource to CUDA
	checkCudaErrors(cudaGraphicsMapResources(1, &BufferResource, CUDAStream));

	// Set up access to mapped graphics resource through OutImage
	size_t NumBytes;
	checkCudaErrors(cudaGraphicsResourceGetMappedPointer((void**)&(Image->GPUPixels), &NumBytes, BufferResource));

	// Unmap graphics resource, ensures synchronization
	checkCudaErrors(cudaGraphicsUnmapResources(1, &BufferResource, CUDAStream));

	// Clean up synchronization stream
	checkCudaErrors(cudaStreamDestroy(CUDAStream));

}

void HRenderer::FreeGPUData()
{
	// TODO: Finish and add comments.
	// This is used when resizing the window which is not properly working.
	// This should probably be called when moving the camera as well.
	DeleteVBO(&(Image->Buffer), this->BufferResource);

	checkCudaErrors(cudaFree(AccumulationBuffer));
	checkCudaErrors(cudaFree(CameraData));
	checkCudaErrors(cudaFree(Rays));	

}