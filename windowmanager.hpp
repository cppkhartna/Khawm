#include "architecture.hpp"
class windowmanager 
{
	//wheel<workspace> workspaces;
	Display* display;
public:
	windowmanager ();
	~windowmanager () {};
  int MainLoop();
};
