//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: directionalLight.cpp
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Demonstrates using a directional light with D3DX objects.  You can orbit
//       the scene using the left and right arrow keys.  In addition you can 
//       elevate the camera with the up and down arrow keys.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"

const int numOfObjects = 8;
//
// Globals
//

IDirect3DDevice9* Device = 0; 

const int Width  = 640;
const int Height = 480;
 
ID3DXMesh* Objects[numOfObjects] = {0, 0, 0, 0,0,0};
D3DXMATRIX  Worlds[numOfObjects];
D3DMATERIAL9 Mtrls[numOfObjects];

//
// Framework Functions
//
bool Setup()
{
	//
	// Create objects.
	//

	D3DXCreateBox(Device,1.0f,1.5f,0.50f, &Objects[0], 0); //W
	D3DXCreateBox(Device, 0.250f, 1.0f, 0.25f, &Objects[1], 0); //b
	D3DXCreateBox(Device, 0.250f, 1.0f, 0.25f, &Objects[2], 0); //g
	D3DXCreateBox(Device, 0.2f, 0.85f, 0.25f, &Objects[3],0); //y
	D3DXCreateBox(Device, 0.2f, .85f, 0.25f, &Objects[4], 0);
	D3DXCreateSphere(Device, 0.4f, 10.0f, 10.0f, &Objects[5], 0);//R
	D3DXCreateBox(Device, 900000.0f, 0.0f, 90000.25f, &Objects[6], 0);
	D3DXCreateBox(Device, 10000.10f, 0.0f, 10000.25f, &Objects[7], 0);
	//
	// Build world matrices - position the objects in world space.
	//

	D3DXMatrixTranslation(&Worlds[0],  0.0f,  0.0f, 0.0f); //W
	D3DXMatrixTranslation(&Worlds[1],  0.250f,  -1.250f, 0.0f); //b
	D3DXMatrixTranslation(&Worlds[2], -0.250f,  -1.250f, 0.0f); //g
	D3DXMatrixTranslation(&Worlds[3], -0.6f,  0.320f, 0.0f); //y
	D3DXMatrixTranslation(&Worlds[4], +0.6f, 0.320f, 0.0f);//R
	D3DXMatrixTranslation(&Worlds[5], 0.0f, 1.1f, 0.0f);//W
	D3DXMatrixTranslation(&Worlds[6], 0.0f, 5.1f, 0.0f);
	D3DXMatrixTranslation(&Worlds[7], 0.0f,-2.0f, 0.0f);
	//
	// Setup the object's materials.
	//

	Mtrls[0] = d3d::YELLOW_MTRL;
	Mtrls[1] = d3d::BLUE_MTRL;
	Mtrls[2] = d3d::BLUE_MTRL;
	Mtrls[3] = d3d::BLUE_MTRL;
	Mtrls[4] = d3d::BLUE_MTRL;
	Mtrls[5] = d3d::WHITE_MTRL;
	Mtrls[6] = d3d::BLUE_MTRL;
	Mtrls[7] = d3d::GREEN_MTRL;
	//
	// Setup a directional light.
	//

	D3DXVECTOR3 dir(1.0f, -0.0f, 0.25f);
	D3DXCOLOR   c = d3d::WHITE;
	D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);

	//
	// Set and Enable the light.
	//

	Device->SetLight(0, &dirLight);
	Device->LightEnable(0, true);

	//
	// Set lighting related render states.
	//

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);

	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.25f, // 45 - degree
			(float)Width / (float)Height,
			1.0f,
			1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

void Cleanup()
{
	for(int i = 0; i < numOfObjects; i++)
		d3d::Release<ID3DXMesh*>(Objects[i]);
}

bool Display(float timeDelta)
{
	if( Device )
	{
		// 
		// Update the scene: update camera position.
		//

		static float angle  = (3.0f * D3DX_PI) / 2.0f;
		static float height = 5.0f;
	
		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
			angle -= 0.5f * timeDelta;

		if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
			angle += 0.5f * timeDelta;

		if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
			height += 5.0f * timeDelta;

		if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
			height -= 5.0f * timeDelta;

		D3DXVECTOR3 position( cosf(angle) * 7.0f, height, sinf(angle) * 7.0f );
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);

		Device->SetTransform(D3DTS_VIEW, &V);

		//
		// Draw the scene:
		//
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();

		for(int i = 0; i < numOfObjects; i++)
		{
			// set material and world matrix for ith object, then render
			// the ith object.
			Device->SetMaterial(&Mtrls[i]);
			Device->SetTransform(D3DTS_WORLD, &Worlds[i]);
			Objects[i]->DrawSubset(0);
		}

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}


//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, L"InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, L"Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}