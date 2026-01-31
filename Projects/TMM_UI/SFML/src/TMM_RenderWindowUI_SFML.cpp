#include "TMM_RenderWindowUI_SFML.h"

namespace TMM
{



	RenderWindowUISFML::~RenderWindowUISFML()
	{
		Destroy();
	}

	void RenderWindowUISFML::Init(TMM::Vec2f size, const char* title, bool fullscreen)
	{
		mSize = size;
		mpWindow = new sf::RenderWindow(
			sf::VideoMode({ 
				static_cast<unsigned int>(size.x), 
				static_cast<unsigned int>(size.y) 
			}), 
			title, 
			fullscreen ? sf::State::Fullscreen : sf::State::Windowed
		);
		mpShape = new sf::RectangleShape();
	}

	void RenderWindowUISFML::AddRoot(WidgetSFML* pRoot)
	{
		mpRoots.Add((CanvasSFML*)pRoot);
	}

	void RenderWindowUISFML::Update()
	{
		auto mousePos = sf::Mouse::getPosition(*mpWindow);
		TMM::Vec2f new_mouse_pos = { static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) };
		mCtx.mouseDelta = new_mouse_pos - mCtx.mousePos;
		mCtx.mousePos = new_mouse_pos;

		TMM_ITER(i_button, 3)
		{
			bool down = sf::Mouse::isButtonPressed((sf::Mouse::Button)i_button);
			mCtx.mouseClicked[i_button] = mCtx.mouseDown[i_button] == false && down;
			mCtx.mouseDown[i_button] = down;
		}

		TMM_ITER(i_key, 101)
		{
			bool down = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i_key);
			mCtx.KeyPressed[i_key] = mCtx.KeyDown[i_key] == false && down;
			mCtx.KeyDown[i_key] = down;
		}

		while (std::optional<sf::Event> event = mpWindow->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				mpWindow->close();
				return;
			}
		}

		TMM_ITER(i_root, mpRoots.Size())
		{
			mpRoots[i_root]->Update(mCtx);
		}
	}

	void RenderWindowUISFML::Render()
	{
		mpWindow->clear();

		TMM_ITER(i_root, mpRoots.Size())
		{
			mpRoots[i_root]->Draw(mpWindow, *mpShape);
		}

		mpWindow->display();
	}

	void RenderWindowUISFML::Destroy()
	{
		if (mpWindow != nullptr)
		{
			delete mpWindow;
			mpWindow = nullptr;
		}
		if (mpShape != nullptr)
		{
			delete mpShape;
			mpShape = nullptr;
		}

		TMM_ITER(i_root, mpRoots.Size())
		{
			delete mpRoots[i_root];
		}
		mpRoots.Resize(0);
	}

}