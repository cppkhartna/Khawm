//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"
class windowmanager 
{
	wheel<workspace>* workspaces;
	Display* display;
	int screen;
	int root;
  unsigned int x_coord;
  unsigned int y_coord;
	unsigned int h_size;
  unsigned int w_size;
public:
	windowmanager ();
	~windowmanager () {};
  int mainloop();
	void handleKeyEvents(XEvent *xev);
	//void gettree();

};
