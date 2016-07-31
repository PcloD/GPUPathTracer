#ifndef RENDERER_H
#define RENDERER_H

#include "GL/glew.h"

#include "Scene.h"
#include "Camera.h"
#include "Image.h"
#include "Kernels.h"

class HRenderer
{
public:
	HRenderer(HCamera* Camera);
	virtual ~HRenderer();

	/**
	 * TODO: Doc
	 */
	HImage* Render();
	
	void InitScene(HScene* Scene);
	void Reset();
	void Resize(HCameraData* CameraData);

	unsigned int PassCounter;
	unsigned int FPSCounter;

private:
	bool bFirstRenderPass;

	/**
	 * Initializes OpenGL Vertex Buffer Object and registers it for access by CUDA.
	 *
	 * @param VBO
	 * @param VBOResource
	 * @param VBOFlags
	 */
	void CreateVBO(GLuint* Buffer, cudaGraphicsResource** BufferResource, unsigned int BufferFlags);

	/**
	 * TODO: Doc
	 *
	 * @param VBO
	 * @param VBOResource
	 */
	void DeleteVBO(GLuint* Buffer, cudaGraphicsResource* BufferResource);

	void InitGPUData(HCameraData* CameraData);
	void FreeGPUData();

	cudaGraphicsResource* BufferResource;

	float3* AccumulationBuffer;
	HImage* Image;

	HCameraData* CameraData;
	HRay* Rays;

	HSceneData* SceneData; // Not working, storing HSphere* for now
	// Temporary Scene storage
	HSphere* Spheres;
	unsigned int NumSpheres;

};

#endif // RENDERER_H
