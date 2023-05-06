#include "d3dUtility.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

IDirect3DDevice9* Device;

const int width = 800;
const int height = 600;

LPD3DXMESH          g_pMesh[5]; // Our mesh object in sysmem
D3DXMATRIXA16 matWorld[5];
LPD3DXMESH Mesh;

int mati;
HRESULT InitGeometry()
{
    D3DXCreateBox(Device, 2, 2, 2, &Mesh, NULL);
	D3DXCreateBox(Device, 2, 2, 2, &g_pMesh[0], NULL);
	D3DXCreateSphere(Device, 0.55, 30, 10, &g_pMesh[1], NULL);
	D3DXCreateCylinder(Device, 0.5, 0.5, 5, 20, 20, &g_pMesh[2], NULL);
	D3DXCreateTeapot(Device, &g_pMesh[3], NULL);
	D3DXCreateTorus(Device, 0.1f, 1.0f, 20.0f, 20.0f, &g_pMesh[4], NULL);

	return S_OK;
}

VOID Cleanup()
{
    for (int i = 0; i < 5; i++)
    {
        if (g_pMesh[0] != NULL)
            g_pMesh[i]->Release();
    }
    Mesh->Release();
    Device->Release();
}

VOID SetupMatrices(int i)
{
    // Set up world matrix
    D3DXMatrixTranslation(&matWorld[0], 2, 0, 0);
    D3DXMatrixTranslation(&matWorld[1], -2, 0, 0);
    D3DXMatrixTranslation(&matWorld[2], 1, 0, 2);
    D3DXMatrixTranslation(&matWorld[3], -1, 0, 2);
    D3DXMatrixTranslation(&matWorld[4], 0, 0, 2);
    
    Device->SetTransform(D3DTS_WORLD, &matWorld[i]);

    D3DXVECTOR3 vEyePt(0.0f, 3.0f, -10.0f);
    D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Device->SetTransform(D3DTS_VIEW, &matView);

    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
    Device->SetTransform(D3DTS_PROJECTION, &matProj);
}

bool Display(float timeDelta)
{
	if (Device)
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
        if (SUCCEEDED(Device->BeginScene()))
        {
            SetupMatrices(0);
            g_pMesh[0]->DrawSubset(0);

            SetupMatrices(1);
            g_pMesh[1]->DrawSubset(0);

            SetupMatrices(2);
            g_pMesh[2]->DrawSubset(0);

            SetupMatrices(3);
            g_pMesh[3]->DrawSubset(0);

            SetupMatrices(4);
            g_pMesh[4]->DrawSubset(0);
            //SetupMatrices(0);
            //Mesh->DrawSubset(0);

            Device->EndScene();
        }

        Device->Present(0, 0, 0, 0);
	}
    
	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
        Cleanup();
		::PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			::DestroyWindow(hwnd);

        if (wParam == VK_NUMPAD1)
        {
            mati = 0;
        }
        if (wParam == VK_NUMPAD2)
        {
            mati = 0;
        }
        if (wParam == VK_NUMPAD3)
        {
            mati = 0;
        }
        if (wParam == VK_NUMPAD4)
        {
            mati = 0;
        }
        if (wParam == VK_NUMPAD5)
        {
            mati = 0;
        }
		break;
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	if (!d3d::InitD3D(hinstance, width, height, true, D3DDEVTYPE_HAL, &Device))
	{
		return 0;
	}
    InitGeometry();
	d3d::EnterMsgLoop(Display);

	return 0;
}