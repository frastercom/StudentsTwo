#include "MyForm.h"
#using <system.drawing.dll>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

/*
* ���������� ���������� ����� �:
* http://blog.kislenko.net/show.php?id=1628
* 
* �������:
* Scan-line fill in C#:
* https://simpledevcode.wordpress.com/2015/12/29/flood-fill-algorithm-using-c-net/
*/

[STAThread]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	StudentsTwo::MyForm form;
	Application::Run(% form);
}

/*
* �������� ����� ����������� (� �������������� OpenDialog)
* 
*/
System::Void StudentsTwo::MyForm::�������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Image Files(*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|All files (*.*)|*.*";
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		fileName = ofd->FileName;
		pictureBox1->Image = Image::FromFile(fileName);
	}
	Form::Refresh();
	return System::Void();
}

/*
* ��������� ���, ����������� (� �������������� SaveDialog)
*
*/
System::Void StudentsTwo::MyForm::������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ sfd = gcnew SaveFileDialog();
	sfd->Filter = "Image Files(*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|All files (*.*)|*.*";
	//insert here the filter if you want
	//ofd->Filter..
	if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		fileName = sfd->FileName;
		pictureBox1->Image->Save(fileName);
	}
	return System::Void();
}

System::Void StudentsTwo::MyForm::pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	
	return System::Void();
}

/*
* ����� ������� ���� ������
*/
System::Void StudentsTwo::MyForm::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (isFloodFill) {
		//�������
		FloodFillLine(gcnew Bitmap(pictureBox1->Image), Point(e->X, e->Y), MyPen->Color);
		return System::Void();
	}
	else {
		p.X = e->X; p.Y = e->Y;
		isPaint = true;
	}
	
	return System::Void();
}

/*
* ����� ������� ���� ��������
*/
System::Void StudentsTwo::MyForm::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	isPaint = false;
	return System::Void();
}


/*
* ������ �������
*/
System::Void StudentsTwo::MyForm::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (!isPaint || !isEncircle) return;
	else if (p.X != e->X || p.Y != e->Y) {
		Graphics::FromImage(pictureBox1->Image)->DrawLine(MyPen, p.X, p.Y, e->X, e->Y);
		p.X = e->X; p.Y = e->Y;
		pictureBox1->Refresh();
	}
	return System::Void();
}

/*
* ��������� ������ ���� ��� �������� �����
*/
System::Void StudentsTwo::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	MyGraphics = pictureBox1->CreateGraphics();
	MyPen = gcnew Pen(Color::Red,2.5);
	isEncircle = false;
	isPaint = false;
	p.X = -1; p.Y = -1;
	fileName = nullptr;
	button2->Visible = isCircle;
	return System::Void();
}

/*
* bytton3 - button8 ����� �����
*/
System::Void StudentsTwo::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyPen = gcnew Pen(Color::Red, 2.5);
	return System::Void();
}

System::Void StudentsTwo::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyPen = gcnew Pen(Color::Yellow, 2.5);
	return System::Void();
}

System::Void StudentsTwo::MyForm::button5_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyPen = gcnew Pen(Color::Green, 2.5);
	return System::Void();
}

System::Void StudentsTwo::MyForm::button6_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyPen = gcnew Pen(Color::Blue, 2.5);
	return System::Void();
}

System::Void StudentsTwo::MyForm::button7_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyPen = gcnew Pen(Color::White, 2.5);
	return System::Void();
}

System::Void StudentsTwo::MyForm::button8_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyPen = gcnew Pen(Color::Black, 2.5);
	return System::Void();
}

/*
* ���������� ����� �������
*/
System::Void StudentsTwo::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	isEncircle = true;
	isFloodFill = false;
	return System::Void();
}


/*
* ���������, ����������� (� �������������� SaveDialog)
*
*/
System::Void StudentsTwo::MyForm::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (fileName == nullptr) {
		SaveFileDialog^ sfd = gcnew SaveFileDialog();
		sfd->Filter = "Image Files(*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|All files (*.*)|*.*";
		if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			fileName = sfd->FileName;
		}
	}
	if (fileName != nullptr) {
		pictureBox1->Image->Save(fileName);
	}
	return System::Void();
}


/*
* ������ �������� ���� � ��������� ��������� ��� MS Studio C#, ��������� �� gui c++
* ��������� �������, ���������� ���������� �������, ����� ������� point � �� int
*/
System::Void StudentsTwo::MyForm::FloodFill(Bitmap^ bmp, Point pt, Color replacementColor)
{
	Color targetColor = bmp->GetPixel(pt.X, pt.Y);
	if (targetColor.ToArgb().Equals(replacementColor.ToArgb()))
	{
		return;
	}

	vector <int> pixelsx;
	vector <int> pixelsy;

	//pixels.push_back(pt);
	pixelsx.emplace_back(pt.X);
	pixelsy.emplace_back(pt.Y);
	while (pixelsx.size() != 0)
	{
		Point temp = Point(pixelsx.back(), pixelsy.back());
		pixelsx.pop_back(); pixelsy.pop_back();
		int y1 = temp.Y;
		while (y1 >= 0 && bmp->GetPixel(temp.X, y1) == targetColor)
		{
			y1--;
		}
		y1++;
		bool spanLeft = false;
		bool spanRight = false;
		while (y1 < bmp->Height && bmp->GetPixel(temp.X, y1) == targetColor)
		{
			bmp->SetPixel(temp.X, y1, replacementColor);

			if (!spanLeft && temp.X > 0 && bmp->GetPixel(temp.X - 1, y1) == targetColor)
			{
				//pixels.push_back(Point(temp.X - 1, y1));
				pixelsx.emplace_back(temp.X - 1);
				pixelsy.emplace_back(y1);
				spanLeft = true;
			}
			else if (spanLeft && temp.X - 1 == 0 && bmp->GetPixel(temp.X - 1, y1) != targetColor)
			{
				spanLeft = false;
			}
			if (!spanRight && temp.X < bmp->Width - 1 && bmp->GetPixel(temp.X + 1, y1) == targetColor)
			{
				//pixels.push_back(Point(temp.X + 1, y1));
				pixelsx.emplace_back(temp.X + 1);
				pixelsy.emplace_back(y1);
				spanRight = true;
			}
			else if (spanRight && temp.X < bmp->Width - 1 && bmp->GetPixel(temp.X + 1, y1) != targetColor)
			{
				spanRight = false;
			}
			y1++;
		}

	}

	return System::Void();
}

/*
* ����� ������� �������� ������������ CheckBox1
*/
System::Void StudentsTwo::MyForm::FloodFillLine(Bitmap^ bmp1, Point pt, Color replacementColor)
{
	if (checkBox1->Checked == true) {
		//��������, ������� ��� bitmap, ���� ����������� � ��������, ������ ������������
		Bitmap^ bmp = gcnew Bitmap(pictureBox1->Image);

		FloodFill(bmp, pt, replacementColor);

		//��������� bitmap -�, ����� ���������� �������� ��������
		for (int x = 1; x < bmp->Width; x++)
		{
			for (int y = 1; y < bmp->Height; y++)
			{
				if (bmp->GetPixel(x, y) != bmp1->GetPixel(x, y) && y % 30 < 15) { //������� �������� ��������
					bmp1->SetPixel(x, y, replacementColor);
				}
			}
		}
	}
	else
	{
		//������� ��������
		FloodFill(bmp1, pt, replacementColor);
	}
	pictureBox1->Image = bmp1;// �������������� bitmap
	pictureBox1->Refresh();//��������� pictureBox
	return System::Void();
}

/*
* ���������� ����� �������
*/
System::Void StudentsTwo::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	isFloodFill = true;
	isEncircle = false;
	return System::Void();
}

/*
* ����� �� ���������
*/
System::Void StudentsTwo::MyForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

/*
* ����������� ���� � ��������
*/
System::Void StudentsTwo::MyForm::�������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

/*
* ����������� �������� � ���������
*/
System::Void StudentsTwo::MyForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}
