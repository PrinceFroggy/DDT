#include "Form1.h"
#include "functions.h"
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

	PatchHealth(GetAddress("\x8B\x45\xFF\x89\x46\xFF\xFF\xFF\x7D\xFF\xC7\x46\xFF\xFF\xFF\xFF\xFF\x8D", "xx?xx???x?xx?????x"));

	button1->Enabled = false;
}

void Form1::button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	label1->Focus();
	
	PatchMana(GetAddress("\x8B\x45\xFF\x89\x48\xFF\xFF\xFF\x00\xFF\x8B\xEC\xFF\xFF\xFF\xFF\xFF\xFF\x8B\x40\xFF\x83\xEC\xFF\x50", "xx?xx???x?xx??????xx?xx?x"));

	button2->Enabled = false;
}

void Form1::button3_Click(System::Object^  sender, System::EventArgs^  e)
{
	label1->Focus();
	
	PatchGold(GetAddress("\x39\x00\x89\x48\xFF\x8B\x47\xFF\x85\xFF\x7D\xFF", "xxxx?xx?x?x?"));

	button3->Enabled = false;
}