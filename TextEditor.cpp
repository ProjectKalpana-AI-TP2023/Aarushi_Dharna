#include <iostream>
using namespace std;

class TextEditor
{
	public:
	char letter; 
	TextEditor* right; 
	TextEditor* left; 

	TextEditor()
	{
		letter = '\0'; 
		left = NULL;
		right = NULL; 
	}

	TextEditor(char c)
	{
		letter = c; 
		left = NULL;
		right = NULL; 
	}

	void addText(string text)
	{
		TextEditor* temp = NULL; 
		for(int i = 0; i < text.size(); i++)
		{
			TextEditor* n = new TextEditor(text[i]);
			if(i == 0 && this -> left == NULL)
			{
				temp = n; 
				temp -> right = this; 
			}
			else if(i == 0 && left != NULL)
			{
				temp = left; 
				temp -> right = n; 
				temp = temp -> right;
				temp -> left = left; 
			}
			else 
			{
				temp -> right = n; 
				n -> left = temp; 
				temp = temp -> right; 
			}
		}
		temp -> right = this; 
		left = temp; 
	}

	string fullText()
	{
		string ret = ""; 
		TextEditor* temp = this; 
		while(temp -> left != NULL)
		{
			temp = temp -> left; 
		}
		while(temp -> right != NULL)
		{
			ret = ret + (temp -> letter);
			temp = temp -> right; 
		}
		return ret + temp -> letter;
	}

	void deleteText(int k)
	{
		if(left == NULL || k == 0)
			return; 
		if((this -> left) -> left != NULL)
		{
		left = left -> left; 
		left -> right = this; 
		deleteText(k - 1); 
		return;
		}
		left = NULL; 
	}

	void backspace()
	{
		if(left == NULL)
			return; 
		if(left -> left == NULL)
		{
			left = NULL; 
			return; 
		}
		(left -> left) -> right = this;
		left = left -> left; 
	}

	int findCursor()
	{
		int index = 0; 
		TextEditor* temp = this; 
		while(temp -> left != NULL)
		{
			temp = temp -> left; 
			index++;
		}
		return index - 1;  
	}

	void cursorLeft(int k) 
	{
		if(left == NULL || k == 0)	
			return; 
		if(left -> left == NULL)
		{
			if(right == NULL)
			{
				left -> right = this; 
				right = left; 
				left = NULL;
				return; 
			}
			left -> right = right; 
			left -> left = this; 
			right -> left = left; 
			right = left; 
			left = NULL; 
			return; 
		}
		(left -> left) -> right = this; 
		if(right != NULL)
		{
			right -> left = left; 
			left -> right = right; 
		}
		else 
			left -> right = NULL; 
		right = left; 
		left = left -> left; 
		right -> left = this;
		cursorLeft(k - 1); 
	}

	void cursorRight(int k)
	{
		if(right == NULL || k == 0)	
			return; 
		if(right -> right == NULL)
		{
			if(left == NULL)
			{
				right -> left = this; 
				left = right; 
				right = NULL;
				return; 
			}
			right -> left = left; 
			right -> right = this; 
			left -> right = right; 
			left = right; 
			right = NULL; 
			return;
		}
		(right -> right) -> left = this; 
		if(left != NULL)
		{
			left -> right = right; 
			right -> left = left; 
		}
		else 
			right -> left = NULL; 
		left = right; 
		right = right -> right; 
		left -> right = this;
		cursorRight(k - 1); 

	}

	string showText(int k)
	{
		if(right == NULL || k == 0)
			return ""; 
		string ret = "";
		TextEditor* temp = right; 
		while(k != 0 && temp -> right != NULL)
		{
			ret = ret + temp -> letter; 
			temp = temp -> right; 
			k--; 
		}
		if(k == 1)
			return ret +  temp -> letter; 
		return ret; 
	}

};

	int main()
	{
		//initialize cursor 
		TextEditor start('^');
		cout << start.fullText() << endl;

		//adds Hello
		start.addText("Hello"); 
		cout << start.fullText() << endl;

		//backspace
		start.backspace();
		cout << start.fullText() << endl;

		//moves cursor left twice
		start.cursorLeft(2);
		cout << start.fullText() << endl;

		//deletes 3 characters (but only deletes two)
		start.deleteText(3);
		cout << start.fullText() << endl;

		//add text "fa"
		start.addText("fa"); 
		cout << start.fullText() << endl;

		//moves cursor right thrice (but it's only twice)
		start.cursorRight(3);
		cout << start.fullText() << endl;

		return 0;
	}