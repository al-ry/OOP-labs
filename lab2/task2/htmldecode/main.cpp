#include "stdafx.h"
#include "htmldecode.h"

int main()
{
	string htmlStr;
	cout << "Enter a html code with html entites or EOF for ending the program." << endl;
	cout << "For example: a &lg; b will be transformed a < b" << endl;
	cout << "Available entities for transforming:" << endl;
	cout << "1)&lt; -> <" << endl;
	cout << "2)&gt; -> >" << endl;
	cout << "3)&apos; -> \'" << endl;
	cout << "4)&amp;; -> &" << endl;
	cout << "5)&quot; -> \"" << endl << endl;
	while (getline(cin, htmlStr))
	{
		cout << HtmlDecode(htmlStr) << endl;
	}
	return 0;
}