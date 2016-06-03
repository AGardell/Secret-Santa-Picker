//Simple program to match a list of people participating in Secret Santa. Those on the same line are family members and therefore
//should not be matched. Does not work if using name with last initial (ie. Nick and Nick M.)

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <time.h>
#include <vector>
#include <utility>


int getRandom(std::vector<std::pair<std::string, int>>& family) {
	return std::rand() % family.size();
}

void removePairs(std::vector<std::pair<std::string, int>>& family) {
	int x = 0;

	while (x < 2) { //scroll through twice, once for each user paired.
		for (int i = 0; i < family.size(); ++i) {
			if (family[i].first == "X") { //look for x and remove and the break from vector to start over.
				family.erase(family.begin() + i);
				break;
			}
		}
		++x;
	}
}

void matchPairs(std::vector<std::pair<std::string, int>>& family) {
	int first = 0;
	int second = 0;

	if (family.size() > 1) { //while family size if greater than one, fet two random people and pair them up if 
							 //not related.
		while (family[first].second == family[second].second) {
			second = getRandom(family);
		}

		std::cout << family[first].first << " => " << family[second].first << std::endl;
		family[first].first = "X"; //reassign the two members with "X"'s to show they've been picked.
		family[second].first = "X";
		removePairs(family);
		matchPairs(family); //recursively call until vector is empty or just 1.
	}

}

int main() {
	std::ifstream familyMembers;
	std::string str;
	std::string name;
	std::stringstream ss;
	std::pair<std::string, int> pair;
	std::vector<std::pair<std::string, int>> family;
	int familyFlag = 1;

	std::srand(time(NULL));

	familyMembers.open("Text.txt"); //open file containg list of particpants

	while (!familyMembers.eof()) { //loop through file and grab each line
		std::getline(familyMembers, str);
		ss << str; //put each line in a stringstream to parse through and see if there are related members

		while (ss >> name) { //pull out each name and add what family he/she belongs to
			pair = std::make_pair(std::string (name), familyFlag);
			family.push_back(pair);
		}

		familyFlag++; //increment family flag for next set of relatives and reset stringstream and members variable.
		ss.clear();
	}

	matchPairs(family);


	return 0;
}