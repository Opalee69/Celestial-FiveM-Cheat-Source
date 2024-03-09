#include <Includes.h>

typedef HRESULT( __stdcall* OriginalFnPresent )(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT( CALLBACK* WNDPROC )(HWND, UINT, WPARAM, LPARAM);

OriginalFnPresent oPresent{ 0 };
HWND hWnd{ 0 };
ID3D11Device* pDevice{ 0 };
ID3D11DeviceContext* pContext{ 0 };
ID3D11RenderTargetView* rendertarget{ 0 };
WNDPROC wnd_proc{ 0 };

extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT __stdcall WndHandling( const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

    if (true && ImGui_ImplWin32_WndProcHandler( hWnd, uMsg, wParam, lParam ))
        return true;

    return CallWindowProc( wnd_proc, hWnd, uMsg, wParam, lParam );
}

bool inits = true;
bool open = false;



HRESULT __stdcall Present( IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags )
{
    if (inits)
    {
        if (SUCCEEDED( pSwapChain->GetDevice( __uuidof(ID3D11Device), (void**)&pDevice ) ))
        {
            pDevice->GetImmediateContext( &pContext );
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc( &sd );
            hWnd = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer );
            pDevice->CreateRenderTargetView( pBackBuffer, NULL, &rendertarget );
            pBackBuffer->Release();
            wnd_proc = (WNDPROC)SetWindowLongPtr( hWnd, GWLP_WNDPROC, (LONG_PTR)WndHandling );
            ImGui::CreateContext(); 
            ui::styles();

            ImGuiIO& io = ImGui::GetIO();

            ImGui_ImplWin32_Init( hWnd );
            ImGui_ImplDX11_Init( pDevice, pContext );
            ui::colors();

            auto config = ImFontConfig();
            config.FontDataOwnedByAtlas = false;

            io.Fonts->AddFontFromMemoryCompressedTTF(fontb_compressed_data, fontb_compressed_size, 14.f);
            io.Fonts->AddFontFromMemoryCompressedTTF(glyphter_compressed_data, glyphter_compressed_size, 14.f);

            inits = 0;
        }
        else
            return oPresent( pSwapChain, SyncInterval, Flags );
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //AsyncKeys
    static bool open = false; 
    if (GetAsyncKeyState( VK_F8 ) & 1)
    {
        open = !open;
    }

    ImGui::GetIO().WantCaptureKeyboard = open;
    ImGui::GetIO().WantCaptureMouse = open;
    ImGui::GetIO().MouseDrawCursor = open;


    if (open) {

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
        ImGui::Begin("UI", 0, ImGuiWindowFlags_NoDecoration);
        {
            ImGui::PopStyleVar();

            ImGui::SetWindowSize(ui::size);

            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, GImGui->Style.WindowRounding);
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
            ImGui::BeginChild("header", { -1, 60 });
            {

                ui::tab(0);
                ImGui::SameLine(0, 0);

            }
            ImGui::EndChild();
            ImGui::PopStyleVar(2);

            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ui::content_anim);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 20, 20 });

            ui::add_page(0, []() {

                ImGui::BeginGroup();
                {
                    ui::begin_child("Aimbot");
                    {
                        ImGui::Checkbox("Enable Aimbot", &m_var->aimbot.enable);
                        ImGui::Checkbox("Visual Target", &m_var->esp.target, m_var->color.TargetArray);
                        ImGui::Checkbox("Visual Fov", &m_var->esp.fov, m_var->color.FovArray);
                        ImGui::SliderFloat("Fov", &m_var->aimbot.fovsize, 35, 200);
                        ImGui::SliderInt("Smooth", &m_var->aimbot.smooth, 1, 12);
                        ImGui::SliderInt("Distance", &m_var->aimbot.distance, 10, 1000);

                    }
                    ui::end_child();

                    ImGui::SameLine();

                    ui::begin_child("Visuals");
                    {
                        ImGui::Checkbox("Enable Visuals", &m_var->esp.enable);
                        ImGui::Checkbox("Visual Vitality", &m_var->esp.Vitality);
                        ImGui::Checkbox("Visual Box", &m_var->esp.Box, m_var->color.BoxArray);
                    }
                    ui::end_child();
                }
                ImGui::EndGroup();
            });

            ImGui::BeginChild("content", { -1, -1 }, 0, ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoBackground);
            {
                ImGui::PopStyleVar();

                ui::render_page();
            }
            ImGui::EndChild();

            ImGui::PopStyleVar();

        }
        ImGui::End();

    }

    ui::handle_alpha_anim();

    Aimhelper::Instance().Loop();
    Visuals::Instance().Loop();

    ImGui::Render();

    pContext->OMSetRenderTargets( 1, &rendertarget, NULL );
    ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );
    return oPresent( pSwapChain, SyncInterval, Flags );
}

DWORD WINAPI Hook_Thread(LPVOID lpReserved)
{
   bool init_hook = false;
    do{

     if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
                kiero::bind(8, (void**)&oPresent, Present);
                init_hook = true;
        }

    } while (!init_hook);

    return TRUE;
}

BOOL DllMain( HMODULE hmod, DWORD dwreason, LPVOID lpreversed )
{
    dwreason;
    lpreversed;
    if (dwreason == 1)
    {

        Init::Instance().Initialize();


        _beginthreadex( 0, 0, (_beginthreadex_proc_type)Hook_Thread, 0, 0, 0 );

    }
    return 1;
}