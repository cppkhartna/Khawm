//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"
class windowmanager 
{
	wheel* workspaces;
	Display* display;
	int screen;
	int root;
	geom* coord;
public:
	windowmanager ();
	~windowmanager ();
  int Loop();
	void KeyEvents(XEvent *xev);
	//void gettree();
	void update_focus(Display* display, Window w);
};
