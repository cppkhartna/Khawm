//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"
class windowmanager 
{
	wheel* workspaces;
	wheel* current;
	Display* display;
	int screen;
	int root;
	geom* coord;
public:
	windowmanager ();
	~windowmanager ();
  int Loop();
	void KeyEvents(XEvent *xev);
	void gettree();
	void update_focus();
	void change_focus_size(double x, double y);
	void move_focus(double x, double y);
};
