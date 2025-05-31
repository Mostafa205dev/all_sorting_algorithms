#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Stack
{
private:
	struct Node
	{
		char *url;
		Node *next;
	};
	Node *top;

	char *copyString(const char *src);

public:
	Stack();
	~Stack();
	void push(const char *url);
	char *pop();
	const char *peek() const;
	bool isEmpty() const;
	void clear();
};

Stack::Stack() : top(nullptr) {}

Stack::~Stack()
{
	clear();
}

char *Stack::copyString(const char *src)
{
	size_t len = std::strlen(src) + 1;
	char *newStr = new char[len];
	std::strcpy(newStr, src);
	return newStr;
}

void Stack::push(const char *url)
{
	Node *newNode = new Node;
	newNode->url = copyString(url);
	newNode->next = top;
	top = newNode;
}

char *Stack::pop()
{
	if (isEmpty())
		return nullptr;
	Node *temp = top;
	char *url = temp->url;
	top = top->next;
	delete temp;
	return url;
}

const char *Stack::peek() const
{
	return isEmpty() ? nullptr : top->url;
}

bool Stack::isEmpty() const
{
	return top == nullptr;
}

void Stack::clear()
{
	while (!isEmpty())
	{
		char *tempUrl = pop();
		delete[] tempUrl;
	}
}

class BrowserHistory
{
private:
	Stack backStack;
	Stack forwardStack;
	char *currentUrl;

	char *copyString(const char *url);

public:
	BrowserHistory();
	~BrowserHistory();
	void visit(const char *url);
	const char *goBack();
	const char *goForward();
	const char *getCurrentUrl() const;
};

BrowserHistory::BrowserHistory() : currentUrl(nullptr) {}

BrowserHistory::~BrowserHistory()
{
	if (currentUrl)
		delete[] currentUrl;
}

char *BrowserHistory::copyString(const char *src)
{
	size_t len = std::strlen(src) + 1;
	char *newStr = new char[len];
	std::strcpy(newStr, src);
	return newStr;
}

void BrowserHistory::visit(const char *url)
{
	if (currentUrl)
	{
		backStack.push(currentUrl);
		delete[] currentUrl;
	}
	forwardStack.clear();
	currentUrl = copyString(url);
}

const char *BrowserHistory::goBack()
{
	if (backStack.isEmpty())
		return nullptr;
	forwardStack.push(currentUrl);
	delete[] currentUrl;
	currentUrl = backStack.pop();
	return currentUrl;
}

const char *BrowserHistory::goForward()
{
	if (forwardStack.isEmpty())
		return nullptr;
	backStack.push(currentUrl);
	delete[] currentUrl;
	currentUrl = forwardStack.pop();
	return currentUrl;
}

const char *BrowserHistory::getCurrentUrl() const
{
	return currentUrl;
}

int main()
{
	BrowserHistory browser;
	std::ifstream file("testp1.txt");
	char command[20], url[300];

	while (file >> command)
	{
		if (strcmp(command, "visit") == 0)
		{
			file >> url;
			browser.visit(url);
			std::cout << "Visited: " << browser.getCurrentUrl() << std::endl;
		}
		else if (strcmp(command, "back") == 0)
		{
			const char *res = browser.goBack();
			std::cout << (res ? res : "Cannot go back") << std::endl;
		}
		else if (strcmp(command, "forward") == 0)
		{
			const char *res = browser.goForward();
			std::cout << (res ? res : "Cannot go forward") << std::endl;
		}
	}

	file.close();
	return 0;
}
