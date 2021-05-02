// student_vaccination.cpp : Defines the entry point for the application.
//

#include "student_vaccination.h"
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <string>

using namespace std;

class Student {
	public:
		std::pair<int, int> name;
		bool vaccinated;

		void print() {
			cout << "---------------------------------" << endl;
			cout << "First name: " << name.first << endl;
			cout << "Last name: " << name.second << endl;
			cout << "Is Vaccinated: " << vaccinated << endl;
			cout << "---------------------------------" << endl;
		}
};
bool operator<(const Student& a, const Student& b) {
	if (a.name.first < b.name.first) return true;
	return false;
}
class Doctor {
public:
	vector<Student>* sl;
	Doctor(){}
	Doctor(vector<Student>& student_list) {
		sl = &student_list;
	}
	bool vaccinate(Student s) {
		int student_indx = find_student(s, *sl);
		if (student_indx < 0) {
			return true;
		}
		return !get_vaccinated((*sl)[student_indx]);
	}

	int find_student(Student s, vector<Student>& student_list) {
		int indx;
		int left_val;
		int right_val;

		indx = this->binary_search(s.name.first, student_list);
		if (indx < 0) {
			return -1;
		}

		// traverse left until first name is no longer repeated.
		left_val = indx;
		while (get_first_name(student_list[left_val]) == s.name.first && left_val > 0) {
			// check if last name equals full_name.last
			if (get_last_name(student_list[left_val]) == s.name.second) {
				// return indx if last name is found.
				return left_val;
			}
			left_val--;
		}

		// traverse right until first name is no longer repeated.
		right_val = indx;
		while (get_first_name(student_list[right_val]) == s.name.first && right_val < student_list.size()) {
			// check if last name equals full_name.last
			if (get_last_name(student_list[right_val]) == s.name.second) {
				// return indx if last name is found.
				return right_val;
			}
			right_val++;
		}
		// return -1 if student with first and last name does not exist.
		return -1;
	}

	int binary_search(int first_name, vector<Student>& student_list) {
		int first = 0;
		int last = student_list.size()-1;
		while (first != last) {
			int mid = (first + last) / 2;
			if (get_first_name(student_list[mid]) == first_name) return mid;
			if (first_name < get_first_name(student_list[mid])) last = mid;
			if (first_name > get_first_name(student_list[mid])) first = mid + 1;
		}
		return -1;
	}

	int get_first_name(Student& a) {
		return a.name.first;
	}
	int get_last_name(Student& a) {
		return a.name.second;
	}

	bool get_vaccinated(Student& a) {
		return a.vaccinated;
	}
	void set_student_list(vector<Student>& student_list) {
		sl = &student_list;
	}
};

bool sortByFirstName(const Student &a, const Student &b) { 
	if (a.name.first < b.name.first) return true;
	return false;
	/*
	if (a.name.first > b.name.first) return true;
	if (a.name.second < b.name.second) return false;
	*/
}

int main()
{	
	Doctor doc;
	Student s1, s2, s3, s4;
	s1.name = { 1, 3 };
	s2.name = { 2, 2 };
	s3.name = { 2, 3 };
	s4.name = { 5, 3 };

	s1.vaccinated = true;
	s2.vaccinated = false;
	s3.vaccinated = true;
	s4.vaccinated = false;

	vector<Student> student_list;
	student_list.push_back(s3);
	student_list.push_back(s2);
	student_list.push_back(s1);

	sort(student_list.begin(), student_list.end(), sortByFirstName);



	for (auto i : student_list) {
		i.print();
	}

	doc.set_student_list(student_list);
	cout << doc.vaccinate(s2) << endl;
	cout << doc.vaccinate(s3) << endl;
	cout << doc.vaccinate(s4) << endl;

	return 0;
}
