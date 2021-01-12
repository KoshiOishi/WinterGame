#include <Windows.h>
#include <wrl.h>
#include "Input.h"
#include "Object3D.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Sound.h"
#include "DX12Util.h"
#include "SceneManager.h"
#include "FPSManager.h"
#include "Title.h"
#include "Explain.h"
#include "GamePlay.h"
#include "GameOver.h"
#include "GlobalFormat.h"

using namespace DirectX;
using namespace Microsoft::WRL;

HRESULT result;

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ComPtr < ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif

	DX12Util::Initialize();
	Input::Initialize(DX12Util::GetHwnd());
	Sound::Initialize();
	Object3D::FirstInit();
	Sprite::FirstInit();

	GlobalFormat::Initialize();

	//デバッグテキスト初期化
	DebugText::Initialize(0, "Resources/debugfont.png");
	SceneManager::AddScene(new Title());
	SceneManager::AddScene(new Explain());
	SceneManager::AddScene(new GamePlay());
	SceneManager::AddScene(new GameOver());
	SceneManager::SetScene("Title");

	MSG msg{}; // メッセージ
	while (true)
	{
		FPSManager::Initialize(60);
		Input::Update();
		// メッセージがある?
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg); // キー入力メッセージの処理
			DispatchMessage(&msg); // プロシージャにメッセージを送る
		}
		// 終了メッセージが来たらループを抜ける
		if (msg.message == WM_QUIT) {
			break;
		}

		SceneManager::Update();
		SceneManager::Draw();
		FPSManager::AdjustFPS();

	}
	// ウィンドウクラスを登録解除
	GlobalFormat::Clear();
	SceneManager::DeleteScene();
	DX12Util::End();
}

