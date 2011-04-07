#include "architecture.hpp"
class windowmanager 
{
	wheel<workspace>* workspaces;
	Display* display;
	int screen;
	int root;
public:
	windowmanager ();
	~windowmanager () {};
  int mainloop();
	void gettree();


};
