//Khartikova
#include <iostream>
#include "khawm.hpp"
#include "windowmanager.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  windowmanager wm;
	if (fork())
	{
		sleep(2);
		cout << wm.mainloop();
	}
	else
	{
		if (fork())
		execlp("xclock", "xclock", 0);
		else
		execlp("xclock", "xclock", 0);
	}
	return 0;
}

