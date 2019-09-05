#include<iostream>
#include<cmath>
#include<string>
using namespace std;
class User
{
private:
	const char* name[100];
	const char* pass[100];
	int num;
public:
	void AddUser(char* a, char* b);
	User(const char* a, const char* b);
	int login(char* a, char* b);
	~User();
};
int main() {
	char name[11], name1[11], pass[11], pass1[11];
	cin >> name >> pass >> name1 >> pass1;
	User user("LiWei", "liwei101");
	user.AddUser(name, pass);
	if (user.login(name1, pass1) >= 0)
	{
		cout << "Success Login!" << endl;
	}
	else {
		cout << "Login failed!" << endl;
	}
	return 0;
}

void User::AddUser(char* a, char* b)
{
	num++;
	int x = strlen(a)+1;
	int y = strlen(b)+1;
	char* p = new char[x];
	char* q = new char[y];
	strcpy(p, a);
	strcpy(q, b);
	name[num] = p;
	pass[num] = q;
	
}

User::User(const char* a, const char* b)
{
	num = 1;
	name[num] = a;
	pass[num] = b;
}

int  User::login(char* a, char* b)
{
	for (int x = 1; x <= num; x++)
	{
		if (!strcmp(a, name[x]) && !strcmp(b, pass[x]))
			return x;
	}
	return -1;
}

User::~User()
{
	for (int i = 2; i <= num; i++)
	{
		delete name[i];
		delete pass[i];
	}
}

