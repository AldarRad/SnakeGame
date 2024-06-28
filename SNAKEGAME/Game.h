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
			for each (Point el in snake)
				g->FillRectangle(snakeBrush, el.X, el.Y, blockSize, blockSize);
		}

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;
		List<Point>^ snake;
		Point fruitPosition;
		const int blockSize = 20;

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

			snake = gcnew List<Point>();
			snake->Add(Point(200, 200));

			srand(time(NULL));
			PlaceFruit();

			this->Paint += gcnew PaintEventHandler(this, &GameForm::OnPaint);
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
	};
}
