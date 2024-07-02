#pragma once
#include <time.h>
#include <stdlib.h> 
namespace SNAKEGAME {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� Game
	/// </summary>
	public ref class Game : public System::Windows::Forms::Form
	{
	public:
		Game(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~Game()
		{
			if (components)
			{
				delete components;
			}
		}
		virtual void OnPaint(System::Object^ lbj, PaintEventArgs^ e) override
		{
			Graphics^ g = e->Graphics;

			Brush^ fruitBrush = gcnew SolidBrush(Color::Red);
			g->FillRectangle(fruitBrush, fruitPosition.X, fruitPosition.Y, blockSize, blockSize);

			Brush^ snakeBrush = gcnew SolidBrush(Color::Green);
			g->FillRectangle(snakeBrush, snake.X, snake.Y, blockSize, blockSize);
		}

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;
		Point snake;
		Point fruitPosition;
		const int blockSize = 20;

		Timer^ timer;
		int moveX = 1, moveY = 0;	

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(400, 400);
			this->Text = L"Game"; 
			this->BackColor = Color::Black; 
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

			snake = Point(200, 200); 

			srand(time(NULL));
			PlaceFruit();

			timer = gcnew Timer();
			timer->Interval = 100;
			timer->Tick += gcnew EventHandler(this, &Game::OnTimerTick);
			timer->Start();

			this->Paint += gcnew PaintEventHandler(this, &Game::OnPaint);
		}
#pragma endregion
		void PlaceFruit()
		{
			int maxX = this->ClientSize.Width / blockSize;
			int maxY = this->ClientSize.Height / blockSize;
			fruitPosition = Point(rand() % maxX * blockSize, rand() % maxY * blockSize);
		}
		void OnTimerTick(Object^ lbj, EventArgs^ e)
		{
			snake.X += moveX;
			snake.Y += moveY;
			this->Invalidate();
		}
	};
}
