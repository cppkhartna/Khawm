//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"
class windowmanager 
{
	wheel workspaces;
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
  int Loop();
	void KeyEvents(XEvent *xev);
	//void gettree();
	void update_focus(Display* display, Window w);
};
