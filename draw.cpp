#include "draw.h"


Window::Window(){
	/* TODO
	std::stringstream ss;
	ss << "mode " << 40 << "," << 20;
	const char* temp = ss.str().c_str();
	std::cout << temp;
	*/
	this->width = 50;
	this->height = 30;
	this->menu_selected_item = 0;
	this->menu_items.push_back("Level 1");
	this->menu_items.push_back("Level 2");
	this->menu_items.push_back("Level 3");
	this->menu_items.push_back("Quit");
	
	// Code taken and modified from: https://stackoverflow.com/questions/7552644/resize-cmd-window
	system("mode 50,30");   //Set mode to ensure window does not exceed buffer size
  	SMALL_RECT WinRect = {0, 0, 50, 30};   //New dimensions for window in 8x12 pixel chars
  	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &WinRect);   //Set new size for window
}

void Window::menu_down(){
	if(this->menu_selected_item == this->menu_items.size()-1)
		this->menu_selected_item = 0;
	else
		this->menu_selected_item++;
}

void Window::menu_up(){
	if(this->menu_selected_item == 0)
		this->menu_selected_item = this->menu_items.size()-1;
	else
		this->menu_selected_item--;
}

std::string Window::menu_get_name_selected(){
	return this->menu_items[this->menu_selected_item];
}

void Window::draw_title(){
	std::stringstream ss;
	std::string temp;
	
	ss << "\n\t\t \"Serious\" Maze\n\n";
	std::vector<std::string>::iterator it = this->menu_items.begin();
	while(it!=this->menu_items.end()){
		// If this item is selected, draw arrow
		if (it - this->menu_items.begin() == this->menu_selected_item)
			ss << "\t-->";
		else
			ss << "\t   ";
		ss << *it << "\n";
		it++;
	}
	// Fill screen with newline characters
	int margin_bot = this->height-3-this->menu_items.size();
	temp.append<int>(margin_bot, '\n');
	ss << temp;
	
	std::cout << ss.str();
}

void Window::draw_maze(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers){
	std::stringstream ss;
	std::string temp;
	
	// Margin top
	int top_margin = (this->width/2-width)/2;
	temp.append<int>(top_margin, '\n');
	ss << temp;
	
	// Calculate size of margin, result is rounded down because it's an integer
	int size_margin = (this->width/2 - width);
	temp.clear();
	temp.append<int>(size_margin, ' ');
	// Show the line of sight matrix of the player
	for (int i=0; i<losmatrix.size(); i++){
		if (i%width==0)
			ss << '\n' << temp;
		if (i == width*width/2)					// This is the location of the player.
			ss << (char) 218 << (char) 191;	
		else if (losmatrix[i]==-2)
			ss << (char) 177 << (char) 177;
		else if (losmatrix[i]==-1)
			ss << (char) 219 << (char) 219;
		else if (losmatrix[i]==0)
			ss << (char) 32 << (char) 32;
		else ss << (char) 32 << losmatrix[i];	// This copies the numbers that need to be collected.
	}
	
	temp.clear();
	temp.append<int>(top_margin, '\n');
	ss << temp;
	
	// Show collected numbers on the screen
	ss << "\n Numbers collected: \n ";
	std::vector<int>::iterator it;
	it = collected_numbers.begin();
	while (it !=collected_numbers.end()){	// Loop through collected_numbers
		ss << *it << " ";
		++it;
	}
	
	// Fill screen up with newlines
	int bot_margin = this->height-this->width/2  - 2;
	temp.clear();
	temp.append<int>(bot_margin, '\n');
	ss << temp;
	
	std::cout << ss.str();
}
