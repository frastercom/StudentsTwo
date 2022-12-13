#include "MyForm.h"
#using <system.drawing.dll>
#include <iostream>
#include <string>
#include <vector>
#include "Unit.h"
#include "InfoProgram.h"
#include <stack>


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
	if (pictureBox1->Image == nullptr) return; //���� ����, ����� ����������� �� �������
	if (isFloodFill) {
		//�������
		FloodFillCheck(gcnew Bitmap(pictureBox1->Image), Point(e->X, e->Y), MyPen->Color);
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
* Fix ���� � ���������, ������ https://simpledevcode.wordpress.com/2015/12/29/flood-fill-algorithm-using-c-net/
*/
System::Void StudentsTwo::MyForm::FloodFill(Bitmap^ bmp, Point pt, Color replacementColor, Color old)
{
	if (old.ToArgb().Equals(replacementColor.ToArgb()) || old.ToArgb().Equals(replacementColor.ToArgb()))
	{
		return;
	}
	stack<int> pixelsX;
	stack<int> pixelsY;
	pixelsX.push(pt.X);
	pixelsY.push(pt.Y);
	while (pixelsX.size() > 0 && pixelsY.size() > 0)
	{
		int x = pixelsX.top();
		int y = pixelsY.top();
		pixelsX.pop();
		pixelsY.pop();
		if (x > 0 && x<pictureBox1->Width && y > 0 && y<pictureBox1->Height) {
			if (bmp->GetPixel(x, y) == old) {
				bmp->SetPixel(x, y, replacementColor);

				pixelsX.push(x-1);
				pixelsY.push(y);

				pixelsX.push(x+1);
				pixelsY.push(y);

				pixelsX.push(x);
				pixelsY.push(y-1);

				pixelsX.push(x);
				pixelsY.push(y+1);
			}
		}
	}

	return System::Void();
}


/*
* �������� �������� ������� ���� � ��������� ���������, ��������� �� gui c++
* ��������� �������, ���������� ���������� �������, ����� ������� point � �� int
* ������ https://russianblogs.com/article/57151279792/
*/
System::Void StudentsTwo::MyForm::FloodFillLine(Bitmap^ bmp, int xmain, int ymain, Color replacementColor, Color old)
{
	if (old.ToArgb().Equals(replacementColor.ToArgb()) || old.ToArgb().Equals(replacementColor.ToArgb()))
	{
		return;
	}


	stack<int> pixelsX;
	stack<int> pixelsY;
	pixelsX.push(xmain);
	pixelsY.push(ymain);
	if (replacementColor.ToArgb() == old.ToArgb()) return;
	while (pixelsX.size() > 0 && pixelsY.size() > 0)
	{
		int x = pixelsX.top();
		int y = pixelsY.top();
		pixelsX.pop();
		pixelsY.pop();
		if (bmp->GetPixel(x, y).ToArgb() != old.ToArgb()) continue;
		int y1 = y;
		while (y1 < bmp->Height && bmp->GetPixel(x, y1).ToArgb() == old.ToArgb())
		{
			bmp->SetPixel(x, y1, replacementColor);
			y1++;
		}
		y1 = y - 1;
		while (y1 >= 0 && bmp->GetPixel(x, y1).ToArgb() == old.ToArgb())
		{
			bmp->SetPixel(x, y1, replacementColor);
			y1--;
		}
		y1 = y;
		while (y1 < bmp->Height && bmp->GetPixel(x, y1).ToArgb() == replacementColor.ToArgb())
		{
			if (x > 0 && bmp->GetPixel(x - 1, y1) == old)
			{
				pixelsX.push(x - 1);
				pixelsY.push(y1);
			}
			y1++;
		}
		y1 = y - 1;
		while (y1 >= 0 && bmp->GetPixel(x, y1).ToArgb() == replacementColor.ToArgb())
		{
			if (x > 0 && bmp->GetPixel(x - 1, y1) == old)
			{
				pixelsX.push(x - 1);
				pixelsY.push(y1);
			}
			y1--;
		}

		y1 = y;
		while (y1 < bmp->Height && bmp->GetPixel(x, y1).ToArgb() == replacementColor.ToArgb())
		{
			if (x < bmp->Width - 1 && bmp->GetPixel(x + 1, y1) == old)
			{
				pixelsX.push(x + 1);
				pixelsY.push(y1);
			}
			y1++;
		}
		y1 = y - 1;
		while (y1 >= 0 && bmp->GetPixel(x, y1).ToArgb() == replacementColor.ToArgb())
		{
			if (x < bmp->Width - 1 && bmp->GetPixel(x + 1, y1) == old)
			{
				pixelsX.push(x + 1);
				pixelsY.push(y1);
			}
			y1--;
		}
	}
	return System::Void();
}

/*
* ����� ������� �������� ������������ CheckBox1
*/
System::Void StudentsTwo::MyForm::FloodFillCheck(Bitmap^ bmp1, Point pt, Color replacementColor)
{
	if (checkBox1->Checked == true) {
		//��������, ������� ��� bitmap, ���� ����������� � ��������, ������ ������������
		FloodFillLine(bmp1, pt.X, pt.Y, replacementColor, bmp1->GetPixel(pt.X, pt.Y));
	}
	else
	{
		//������� ��������
		FloodFill(bmp1, pt, replacementColor, bmp1->GetPixel(pt.X, pt.Y));
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
	this->Close();
	return System::Void();
}

/*
* ����������� ���� � ��������
*/
System::Void StudentsTwo::MyForm::�������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Unit^ unit = gcnew Unit();
	unit->Show();
	return System::Void();
}

/*
* ����������� �������� � ���������
*/
System::Void StudentsTwo::MyForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	InfoProgram^ inf = gcnew InfoProgram();
	inf->Show();
	return System::Void();
}
