#include <TMM_Setup.h>
#include <TMM_Debugger.h>

//#include <TMM_UI_SFML.h>
#include <TMM_Functional.h>
#include <TMM_Algorithm.h>

#pragma comment(lib, "Winmm.lib")

#include <chrono>

#define WAIT_FOR_A while (GetAsyncKeyState('A') == false) {}

void BenchMark(const char* name, void(*algo)(uint32_t * buffer, uint64_t size, bool(*compare)(uint32_t & before, uint32_t & after)), uint64_t size)
{
	uint64_t sum_duration = 0.0f;
	uint64_t max_duration = 0.0f;
	uint64_t min_duration = INT_MAX;
	float count = 1024.0f;
	for (int i = 0; i < 1024; ++i)
	{
		uint32_t* data_test = new uint32_t[size];
		for (int i = 0; i < size; ++i)
		{
			data_test[i] = rand() % 100;
		}

		auto t1 = std::chrono::high_resolution_clock::now();

		algo(data_test, size, +[](uint32_t& a, uint32_t& b) { return a < b; });

		auto duration = std::chrono::high_resolution_clock::now() - t1;

		TMM_ITER(i, size - 1)
		{
			if (data_test[i] > data_test[i + 1])
			{
				LOG_ERROR << "Algo Failed to Sort" << ENDL;
				return;
			}
		}

		auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
		sum_duration += ns;
		if (ns > max_duration) max_duration = ns;
		if (ns < min_duration) min_duration = ns;

		delete[] data_test;
	}

	uint64_t mean_ns = sum_duration / count;

	float mean_s = mean_ns * 0.000001f;
	float min_duration_s = min_duration * 0.000001f;
	float max_duration_s = max_duration * 0.000001f;

	LOG_INFO << "Benchmark pour l'algo : " << name << ENDL;
	LOG_INFO << "En moyenne prends : " << mean_s << " s" << ENDL;
	LOG_INFO << "Between " << min_duration_s << " s et " << max_duration_s << " s" << ENDL << ENDL;
}

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
	dbg.Flags |= TMM::DEBUGGER_FLAGS::NONE;
	dbg.Output |= TMM::DEBUGGER_OUTPUT::OUTPUT_CONSOLE;
	DBG_INIT(dbg, true);
#endif // !NDEBUG

	BenchMark("Quick Sort", TMM::SORTING::QuickSort, 4096); // Failed => to correct
	BenchMark("Randix (8 bits) Sort", TMM::SORTING::RandixSort<uint32_t, 8>, 4096);
	BenchMark("Randix (16 bits) Sort", TMM::SORTING::RandixSort<uint32_t, 16>, 4096);
	BenchMark("Insertion Sort", TMM::SORTING::InsertionSort, 4096);
	BenchMark("Selection Sort", TMM::SORTING::SelectionSort, 4096);
	BenchMark("Bubble Sort", TMM::SORTING::BubbleSort, 4096);

	//sf::Font font{ "res/arial.ttf" };

	//TMM::RenderWindowUISFML window;
	//window.Init({ 960, 540 }, "TMM_UI_SFML");

	//TMM::CanvasSFMLDescriptor overlayDesc{};
	//overlayDesc.CanvasSize = { 20, 20 };
	//overlayDesc.CanvasBackgroundColor = { 100, 100, 100, 255 };
	//auto overlay = TMM::CreateRootWidget<TMM::CanvasSFML>(&overlayDesc);


	//TMM::CanvasSFMLDescriptor rootDesc{};
	//rootDesc.CanvasSize = window.GetSize();
	//rootDesc.CanvasBackgroundColor = TMM::CONSTANT::COLOR_DEEP_BLUE;
	//rootDesc.pCanvasOverlayRoot = overlay;
	//rootDesc.CanvasOverlayVisibleByDefault = true;
	//auto root = TMM::CreateRootWidget<TMM::CanvasSFML>(&rootDesc);

	//root->GetEvents()->RegisterCallbackHover(
	//	new TMM::LambdaMethod<void, TMM::Vec2f>(
	//		[overlay](TMM::Vec2f mouse_position) -> void
	//		{
	//			auto dest = overlay->GetParent()->ToLocalPosition(mouse_position);
	//			overlay->SetPosition(dest - 0.5f * overlay->GetSize());
	//		}
	//	)
	//);

	//TMM::SliderSFMLDescriptor sliderDesc{};
	//sliderDesc.CanvasSize = { 200, 80 };
	//sliderDesc.CanvasOffset = { 600, 100 };
	//auto slider = TMM::AddChildToWidget<TMM::SliderSFML>(root, &sliderDesc);
	//((TMM::SliderEventsSFML*)slider->GetEvents())->RegisterCallbackValueChanged(
	//	TMM::MakeFunctionPtr(
	//		+[](float old, float v)
	//		{
	//			LOG_INFO << "New Slider Value : " << v << ENDL;
	//		}
	//	)
	//);

	//TMM::TextBoxSFMLDescriptor txtDesc{};
	//txtDesc.Text = "Place  Holder";
	//txtDesc.CanvasSize = { 200, 100 };
	//txtDesc.CanvasOffset = { 50, 50 };
	//txtDesc.CanvasAnchor = TMM::ANCHOR::TOP_LEFT;
	//txtDesc.MaxCharacterByLine = 7;
	//txtDesc.CharacterSize = 16;
	//txtDesc.pFont = &font;
	//TMM::AddChildToWidget<TMM::TextBoxSFML>(root, &txtDesc);

	//window.AddRoot(root);
	//while (window.IsOpen())
	//{
	//	window.Update();
	//	window.Render();
	//}

	//window.Destroy();

	DBG_UNINIT();

	return 0;
}
