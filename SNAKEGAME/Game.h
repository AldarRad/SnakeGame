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
	using namespace System::Collections::Generic;

	/// <summary>
	/// —водка дл€ Game
	/// </summary>
	public ref class Game : public System::Windows::Forms::Form
	{
	public:
		Game(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
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
			for each (Point el in snake)
				g->FillRectangle(snakeBrush, el.X, el.Y, blockSize, blockSize);
		}

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
		List<Point>^ snake;
		Point fruitPosition;
		const int blockSize = 20;

		Timer^ timer;
		int moveX = 1, moveY = 0;	

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(400, 400);
			this->Text = L"Game"; 
			this->BackColor = Color::Black; 
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

			snake = gcnew List<Point>();
			snake->Add(Point(200, 200));

			srand(time(NULL));
			PlaceFruit();

			timer = gcnew Timer();
			timer->Interval = 200;
			timer->Tick += gcnew EventHandler(this, &Game::OnTimerTick);
			timer->Start();

			this->Paint += gcnew PaintEventHandler(this, &Game::OnPaint);
			this->KeyDown += gcnew KeyEventHandler(this, &Game::OnKeyDown);
		}
#pragma endregion
		void PlaceFruit()
		{
			int maxX = this->ClientSize.Width / blockSize;
			int maxY = this->ClientSize.Height / blockSize;
			do
			{
				fruitPosition = Point(rand() % maxX * blockSize, rand() % maxY * blockSize);
			} while (snake->Contains(fruitPosition));
		}
		void OnTimerTick(Object^ lbj, EventArgs^ e)
		{
			MoveSnake();
			
			if (snake[0] == fruitPosition)
			{
				GrowthSnake();
				PlaceFruit();
				
				if (timer->Interval > 60)
					timer->Interval -= 20;// 5		
			}
			this->Invalidate();
		}
		void GrowthSnake()
		{
			Point newHead = snake[0];

			newHead.X += moveX * blockSize;
			newHead.Y += moveY * blockSize;
			snake->Insert(0, newHead);
		}
		void MoveSnake()
		{
			Point newHead = snake[0];

			newHead.X += moveX * blockSize;
			newHead.Y += moveY * blockSize;
			snake->Insert(0, newHead);
			snake->RemoveAt(snake->Count - 1);
		}
		void OnKeyDown(Object^ obj, KeyEventArgs^ e)
		{
			switch (e->KeyCode)
			{
			case Keys::Up:
				moveX = 0;
				moveY = -1;
				break;
			case Keys::Down:
				moveX = 0;
				moveY = 1;
				break;
			case Keys::Left:
				moveX = -1;
				moveY = 0;
				break;
			case Keys::Right:
				moveX = 1;
				moveY = 0;
				break;
			}
		}
	};
}
