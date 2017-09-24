#include "draw.h"


Window::Window(){
	/* TODO
	std::stringstream ss;
	ss << "mode " << 40 << "," << 20;
	const char* temp = ss.str().c_str();
	std::cout << temp;
	*/
	this->width = 25;
	this->height = 30;
	this->menu_selected_item = 0;
	this->get_list_levelfiles();
	this->menu_items.push_back("Quit");
	this->calc_selected_item = 0;
	
	this->calc_items.push_back("+");
	this->calc_items.push_back("-");
	this->calc_items.push_back("*");
	this->calc_items.push_back("/");

	// Code taken and modified from: https://stackoverflow.com/questions/7552644/resize-cmd-window
	system("mode 50,30");   //Set mode to ensure window does not exceed buffer size
  	SMALL_RECT WinRect = {0, 0, 50, 30};   //New dimensions for window in 8x12 pixel chars
  	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &WinRect);   //Set new size for window
}

void Window::get_list_levelfiles(){
	// Check if directory exists
	char cCurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))){
		throw(std::invalid_argument("Cannot get current directory"));
	}
	
	// Loop over files with name "lvl*.txt"
	std::string temp (cCurrentPath);
	temp += "\\lvl*.txt";
	WIN32_FIND_DATAA ffd;
	HANDLE hFind = FindFirstFileA(temp.c_str(), &ffd);
	if(hFind== INVALID_HANDLE_VALUE){
		throw(std::invalid_argument("No level files found, add some levels with filename 'lvl#.txt'."));
	}
	do {
	    this->menu_items.push_back(ffd.cFileName);
	} while (FindNextFileA(hFind, &ffd) != 0);
}

std::string Window::menu_get_name_selected(){
	return this->menu_items[this->menu_selected_item];
}

void Window::draw_title(){
	system("cls");
	std::stringstream ss;
	std::string temp;
	
	ss << "\n\t\t\"Serious\" Maze\n\n";
	std::vector<std::string>::iterator it = this->menu_items.begin();
	while(it!=this->menu_items.end()){
		// If this item is selected, draw arrow
		if (it - this->menu_items.begin() == this->menu_selected_item)
			ss << "\t-->";
		else
			ss << "\t   ";
		
		if (*it=="Quit")
			ss << *it << "\n";
		else
			ss << "Level " << std::string(*it).substr(3,1) << "\n";
		it++;
	}
	// Fill screen with newline characters
	int margin_bot = this->height-3-this->menu_items.size();
	temp.append<int>(margin_bot, '\n');
	ss << temp;
	
	std::cout << ss.str();
}
// Maze screen function:
void Window::draw_maze(int width, std::vector<int> &losmatrix, std::vector<int> &collected_numbers, float target){
	system("cls");
	std::stringstream ss;
	std::string temp;
	
	// Margin top
	int top_margin = (this->width-width)/2;

	// Appends an integer (top_margin) times the character given.
	temp.append<int>(top_margin, '\n');
	ss << temp;
	
	// Calculate size of margin
	int size_margin = this->width - width;
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
	
	// Fill below los_grid until text
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
	int bot_margin = this->height - this->width  - 2;
	temp.clear();
	temp.append<int>(bot_margin, '\n');
	ss << temp;
	ss << "Target is: " << (int)target;
	std::cout << ss.str();
}

// Calculation screen functions:
int Window::calc_get_char(std::vector<int> &collected_numbers){
	return collected_numbers[this->calc_selected_item];
}

void Window::calculator(std::vector<std::string> &chosen_numb_ops){
	std::stringstream ss;
	std::string temp;
	if (chosen_numb_ops[1]=="+")
		ss << std::stof(chosen_numb_ops[0])+std::stof(chosen_numb_ops[2]);
	else if(chosen_numb_ops[1]=="-")
		ss << std::stof(chosen_numb_ops[0])-std::stof(chosen_numb_ops[2]);
	else if(chosen_numb_ops[1]=="*")
		ss << std::stof(chosen_numb_ops[0])*std::stof(chosen_numb_ops[2]);
	else if(chosen_numb_ops[1]=="/")
		ss << std::stof(chosen_numb_ops[0])/std::stof(chosen_numb_ops[2]);
	ss >> temp;
	chosen_numb_ops.clear();
	chosen_numb_ops.push_back(temp.substr(0,5));
}

void Window::draw_calc_screen(std::vector<int> collected_numbers, int pick_order,std::vector<std::string> chosen_numb_ops, float target){
	system("cls");
	// The switch decides what is being chosen (numer or operator)
	//int pick_order = 0;
	std::stringstream ss;
	std::string temp;
	std::vector<int>::iterator it = collected_numbers.begin();
	std::vector<std::string>::iterator it2 = calc_items.begin();
	ss << "\nCalculation screen \n\n";
	ss <<"You must use your collected numbers to \ncalculate your way out of the maze. \nIf you succeed to create " << (int) target << " with the \nnumbers you found, you will escape.\n\n";
	ss<< "Collected numbers: \n";
	switch (pick_order){
		case 1:{
			while(it!=collected_numbers.end()){
				// If this item is selected, draw arrow
				if (it - collected_numbers.begin() == this->calc_selected_item)
					ss << " -->";
				else
					ss << "    ";
				ss << *it;
				it++;
			}
			ss << "\nPossible operators: \n";
			while(it2!=calc_items.end()){
			ss << "    " << *it2;
				it2++;
			}
		}
		break;
		case 2:{
			while(it!=collected_numbers.end()){
				ss << "    "<< *it;
				it++;
			}
			ss << "\nPossible operators: \n";
			while(it2!=calc_items.end()){
				if (it2 - calc_items.begin() == this->calc_selected_item)
				// If this item is selected, draw arrow
					ss << " -->";
				else
					ss << "    ";
				ss << *it2;
				it2++;
			}

		}
		break;	
	}
	// Draw the chosen numbers
	ss << "\n\n Calculation \n";
	it2 = chosen_numb_ops.begin();
	while (it2!=chosen_numb_ops.end()){
		ss << "   " << *it2;
		it2++;
	}
		
	// Fill screen with newline characters
	int margin_bot = this->height-14;
	temp.append<int>(margin_bot, '\n');
	ss << temp;
	
	std::cout << ss.str();
}



