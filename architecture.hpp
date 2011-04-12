//Khartikova

class wheel;

class filler 
{
public:
	filler () {};
	virtual ~filler () {};
	virtual wheel* windows() = 0;
	virtual void make_me_your_master(wheel* please) = 0;
  virtual	void tile(int layout, unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h) = 0;
	virtual void show() = 0;
	virtual void hide() = 0;
};

class wheel 
{
	struct arch
	{
		arch* next;
		arch* prev;
		filler* object;
		arch(filler* obj) 
		{
			next = this;
			prev = this;
			object = obj;			
		};
	};
    
	void move(int dir);
				
	int count;
  arch* master;
  arch* focus;

public:
	wheel ();
	virtual ~wheel ();
	void rotate(int dir); // сдвигает все окна
	wheel* operator+=(filler* obj); // добавляет объект в колесо
	//filler* operator-(unsigned int num); 
	// достаёт объект с определённым номером из колеса
	filler* operator-(); // достаёт объект фокуса из колеса
	
	void operator++(); //фокусирует дугу справа
	void operator--(); //фокусирует дугу слева
	filler* operator[](unsigned int i); // фокусирует конкретную дугу, считая от мастера
	filler* operator()(); // доступ к объекту фокуса
	operator int(); //возвращает номер фокуса
	
	void operator++(int); //меняет местами фокус и правую дугу
	void operator--(int); //меняет местами фокус и левую дугу

	void swap(unsigned int first, unsigned int second);//меняет местами две дуги
	virtual void tile(int layout, unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h);
	//void checktree(Window* row, int n);
};

class window : public filler 
{
  Window* w;
	char *name;
	bool shown;

public:
	window (Window* win) {};
	~window () {};
	
	void make_me_your_master(wheel* please);

	void show();
	void hide();

	virtual void tile(int layout, unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h);
private:
	virtual wheel* windows() {return wheel_of_windows;};
};

class group : public window
{
	wheel* wheel_of_windows;
public:
 	group ();
	~group ();
	virtual wheel* windows() {return wheel_of_windows;};

	void show() {};
	void hide() {};
	void tile(int layout, unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h);
};

class workspace : public filler
{
	char* name;
  wheel* wheel_of_windows;	
public:
	workspace ();
	~workspace ();
	
	virtual wheel* windows() {return wheel_of_windows;};

private:
	void show() {};
	void hide() {};
};
