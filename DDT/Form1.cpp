#include <Windows.h>
#include <tchar.h>
#include "Form1.h"
#include "hacks.h"
#include <stdio.h>

using namespace DDT;

bool butt1Once = false;
bool butt2Once = false;
bool butt3Once = false;

void Main(void)		
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Form1);	
	Application::Exit();
}

void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	label1->Focus();

	if (!butt1Once)
	{
		GetAddress(1);
	}
	else
	{

	}
}

void Form1::button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	label1->Focus();

	if (!butt2Once)
	{

	}
	else
	{

	}
}

void Form1::button3_Click(System::Object^  sender, System::EventArgs^  e)
{
	label1->Focus();

	if (!butt3Once)
	{

	}
	else
	{

	}
}