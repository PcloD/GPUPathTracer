#include "Scene.h"

#include <stdlib.h>
#include <time.h>

HScene::HScene()
{

}

HScene::~HScene() {}

void HScene::LoadSceneFile()
{

	/*// Closed Cornell box
	NumSpheres = 8;
	Spheres = new HSphere[NumSpheres];

	// Yellow sphere
	Spheres[0].Position = make_float3(-0.25f, 0.15f, -0.3f);
	Spheres[0].Radius = 0.15f;
	Spheres[0].Material.Diffuse = make_float3(0.87f, 0.87f, 0.15f);
	Spheres[0].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Blue sphere
	Spheres[1].Position = make_float3(0.2f, 0.2f, -0.1f);
	Spheres[1].Radius = 0.2f;
	Spheres[1].Material.Diffuse = make_float3(0.87f, 0.15f, 0.87f);
	Spheres[1].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Light sphere
	Spheres[2].Position = make_float3(0.0f, 0.75f, 0.0f);
	Spheres[2].Radius = 0.15f;
	Spheres[2].Material.Diffuse = make_float3(0.0f, 0.0f, 0.0f);
	Spheres[2].Material.Emission = make_float3(3.0f, 3.0f, 3.4f);

	// Floor sphere
	Spheres[3].Position = make_float3(0.0f, -1e5f, 0.0f);
	Spheres[3].Radius = 1e5f;
	Spheres[3].Material.Diffuse = make_float3(0.87f, 0.87f, 0.87f);
	Spheres[3].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Right wall sphere
	Spheres[4].Position = make_float3(0.5f + 1e5f, 0.5f, 0.0f);
	Spheres[4].Radius = 1e5f;
	Spheres[4].Material.Diffuse = make_float3(0.15f, 0.87f, 0.15f);
	Spheres[4].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Left wall sphere
	Spheres[5].Position = make_float3(-0.5f - 1e5f, 0.5f, 0.0f);
	Spheres[5].Radius = 1e5f;
	Spheres[5].Material.Diffuse = make_float3(0.87f, 0.15f, 0.15f);
	Spheres[5].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Back wall sphere
	Spheres[6].Position = make_float3(0.0f, 0.5f, -0.5f - 1e5f);
	Spheres[6].Radius = 1e5f;
	Spheres[6].Material.Diffuse = make_float3(0.87f, 0.87f, 0.87f);
	Spheres[6].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Roof sphere
	Spheres[7].Position = make_float3(0.0f, 1.0f + 1e5f, 0.0f);
	Spheres[7].Radius = 1e5f;
	Spheres[7].Material.Diffuse = make_float3(0.87f, 0.87f, 0.87f);
	Spheres[7].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);*/

	// Open sphere scene
	/*NumSpheres = 6;
	Spheres = new HSphere[NumSpheres];

	// Yellow sphere
	Spheres[0].Position = make_float3(0.1f, 0.8f, -2.0f);
	Spheres[0].Radius = 0.8f;
	Spheres[0].Material.Diffuse = make_float3(0.60f, 0.40f, 0.87f);
	Spheres[0].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Blue sphere
	Spheres[1].Position = make_float3(1.4f, 0.9f, -0.3f);
	Spheres[1].Radius = 0.8f;
	Spheres[1].Material.Diffuse = make_float3(0.15f, 0.35f, 0.87f);
	Spheres[1].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Light sphere
	Spheres[2].Position = make_float3(0.0f, 3.0f, 0.0f);
	Spheres[2].Radius = 0.8f;
	Spheres[2].Material.Diffuse = make_float3(0.0f, 0.0f, 0.0f);
	Spheres[2].Material.Emission = make_float3(5.0f, 5.0f, 5.4f);

	// Floor sphere
	Spheres[3].Position = make_float3(0.0f, -1e5f, 0.0f);
	Spheres[3].Radius = 1e5f;
	Spheres[3].Material.Diffuse = make_float3(0.15f, 0.15f, 0.15f);
	Spheres[3].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Blue sphere
	Spheres[4].Position = make_float3(-2.0f, 1.3f, -3.4f);
	Spheres[4].Radius = 1.2f;
	Spheres[4].Material.Diffuse = make_float3(0.80f, 0.30f, 0.80f);
	Spheres[4].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

	// Blue sphere
	Spheres[5].Position = make_float3(0.0f, 0.4f, -0.3f);
	Spheres[5].Radius = 0.3f;
	Spheres[5].Material.Diffuse = make_float3(0.40f, 0.87f, 0.87f);
	Spheres[5].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);*/

	// Random colored sphere scene
	NumSpheres = 300;
	Spheres = new HSphere[NumSpheres];

	srand(time(nullptr));

	for (int i = 0; i < NumSpheres-1; i++)
	{

		Spheres[i].Position = make_float3(
			2.0f - 4.0f*(float)rand() / (float)RAND_MAX,
			0.1f + 1.4f*(float)rand() / (float)RAND_MAX,
			-4.0f*(float)rand() / (float)RAND_MAX);
		Spheres[i].Radius = 0.01f + 0.2f*(float)rand() / (float)RAND_MAX;
		Spheres[i].Material.Diffuse = make_float3(
			(float)rand() / (float)RAND_MAX,
			(float)rand() / (float)RAND_MAX,
			(float)rand() / (float)RAND_MAX);
		
		if ((float)rand() / (float)RAND_MAX > 0.8f)
		{
			Spheres[i].Material.Emission = make_float3(
				5.0f * (float)rand() / (float)RAND_MAX,
				5.0f * (float)rand() / (float)RAND_MAX,
				5.4f * (float)rand() / (float)RAND_MAX);
		}
		else
		{
			Spheres[i].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);
		}

	}
	
	Spheres[NumSpheres - 2].Position = make_float3(0.0f, 3.0f, 0.0f);
	Spheres[NumSpheres - 2].Radius = 0.8f;
	Spheres[NumSpheres - 2].Material.Diffuse = make_float3(0.0f, 0.0f, 0.0f);
	Spheres[NumSpheres - 2].Material.Emission = make_float3(5.0f, 5.0f, 5.4f);

	Spheres[NumSpheres - 1].Position = make_float3(0.0f, -1e5f, 0.0f);
	Spheres[NumSpheres - 1].Radius = 1e5f;
	Spheres[NumSpheres - 1].Material.Diffuse = make_float3(0.15f, 0.15f, 0.15f);
	Spheres[NumSpheres - 1].Material.Emission = make_float3(0.0f, 0.0f, 0.0f);

}
