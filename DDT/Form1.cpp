#include "Form1.h"
#include "hacks.h"

using namespace DDT;

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

	GetAddress("\x8B\x45\xFF\x89\x46\xFF\xFF\xFF\x7D\xFF\xC7\x46\xFF\xFF\xFF\xFF\xFF\x8D", "xx?xx???x?xx?????x");

	button1->Enabled = false;
}

void Form1::button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	label1->Focus();
	
	//GetAddress();

	button2->Enabled = false;
}

void Form1::button3_Click(System::Object^  sender, System::EventArgs^  e)
{
	label1->Focus();
	
	//GetAddress();

	button3->Enabled = false;
}