#include <TMM_Setup.h>
#include <TMM_Debugger.h>

//#include <TMM_UI_SFML.h>
#include "TMM_Thread.h"
#include "TMM_ThreadList.h"
#include "TMM_ThreadCast.h"
#include "TMM_ThreadLoop.h"

#include "TMM_Functional.h"

#pragma comment(lib, "Winmm.lib")

#define WAIT_FOR_A while (GetAsyncKeyState('A') == false) {}

int main(int argc, char* argv[]) 
{
#ifndef NDEBUG
	auto tmp = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmp |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmp);

	TMM::DEBUGGER_DESCRIPTOR dbg{};
	dbg.Flags |= TMM::DEBUGGER_FLAGS::ALL;
	dbg.Output |= TMM::DEBUGGER_OUTPUT::OUTPUT_CONSOLE;
	dbg.Output |= TMM::DEBUGGER_OUTPUT::OUTPUT_LOGS;
	DBG_INIT(dbg, true);
#else
	TMM::DEBUGGER_DESCRIPTOR dbg{};
	dbg.Flags |= TMM::DEBUGGER_FLAGS::ALL;
	dbg.Output |= TMM::DEBUGGER_OUTPUT::OUTPUT_CONSOLE;
	DBG_INIT(dbg, true);
#endif // !NDEBUG

	int a = 1;
	auto f = TMM::MakeLambdaMethodPtr([&a](int v) -> int { return a + v; });

	int b = f->Call(2);
	a = 2;
	int c = f->Call(2);

	LOG_INFO << "b = " << b << ENDL;
	LOG_INFO << "c = " << c << ENDL;

	delete f;

	/*sf::Font font{ "res/arial.ttf" };

	TMM::RenderWindowUISFML window;
	window.Init({ 960, 540 }, "Bonne nuit les petits");

	TMM::CanvasSFMLDescriptor overlayDesc{};
	overlayDesc.CanvasSize = { 100, 100 };
	overlayDesc.CanvasBackgroundColor = { 100, 100, 100, 255 };
	auto overlay = TMM::CreateRootWidget<TMM::CanvasSFML>(&overlayDesc);



	TMM::CanvasSFMLDescriptor rootDesc{};
	rootDesc.CanvasSize = window.GetSize();
	rootDesc.CanvasBackgroundColor = TMM::CONSTANT::COLOR_DEEP_BLUE;
	rootDesc.pCanvasOverlayRoot = overlay;
	rootDesc.CanvasOverlayVisibleByDefault = true;
	auto root = TMM::CreateRootWidget<TMM::CanvasSFML>(&rootDesc);

	root->GetEvents()->RegisterCallbackHover(
		new TMM::LambdaMethod<void, TMM::Vec2f>(
			[overlay](TMM::Vec2f mouse_position) -> void
			{
				auto dest = overlay->GetParent()->ToLocalPosition(mouse_position);
				overlay->Position() = dest - 0.5f * overlay->GetSize_ReadOnly();
			}
		)
	);

	TMM::TextBoxSFMLDescriptor txtDesc{};
	txtDesc.Text = "J'aime les patates";
	txtDesc.CanvasSize = { 200, 100 };
	txtDesc.CanvasOffset = { 50, 50 };
	txtDesc.CanvasAnchor = TMM::ANCHOR::TOP_LEFT;
	txtDesc.pFont = &font;
	TMM::AddChildToWidget<TMM::TextBoxSFML>(root, &txtDesc);

	window.AddRoot(root);
	while (window.IsOpen())
	{
		window.Update();
		window.Render();
	}

	window.Destroy();*/

	DBG_UNINIT();

	return 0;
}
