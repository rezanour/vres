#include "Precomp.h"
#include "Include/VRES.h"
#include "Graphics/VRES_Renderer.h"

std::unique_ptr<VRES::Renderer> TheRenderer;

bool VRES_Initialize(HWND hwnd)
{
    TheRenderer.reset(new VRES::Renderer);
    if (!TheRenderer->Initialize(hwnd))
    {
        assert(false);
        return false;
    }

    return true;
}

void VRES_Shutdown()
{
    TheRenderer.reset();
}
