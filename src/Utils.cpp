#include "Utils.h"



void print_error_message(int error_type) {

	if (error_type == 0)
		std::cout << "Unexpected number of arguments" << std::endl << "Insuffucient or more arguments then expected..." << std::endl << "Application will be terminated." << std::endl;
	else if (error_type == 1)
		std::cout << "Unexpected argument type or incorrect argument order" << std::endl << "Execution has stopped." << std::endl << "Application will be terminated" << std::endl;
	else if (error_type == 2)
		std::cout << "Entered resolution is not suitable." << std::endl << "Resolution must be positive value." << std::endl << "Application will be terminated" << std::endl;

}

bool parse_args(int argc, _TCHAR** argv, int& resolution, _TCHAR*& heightfield_filename, _TCHAR*& color_filename, _TCHAR*& normal_filename) {

	if (argc == 9) {

		if (_tcscmp(argv[1], TEXT("-r")) != 0) {
			print_error_message(1);
			return false;
		}
		else {
			resolution = _tstoi(argv[2]);
			if (resolution <= 0) {
				print_error_message(2);
				return false;
			}
		}

		if (_tcscmp(argv[3], TEXT("-o_height")) != 0) {
			print_error_message(1);
			return false;
		}
		else {
			heightfield_filename = argv[4];
		}

		if (_tcscmp(argv[5], TEXT("-o_color")) != 0) {
			print_error_message(1);
			return false;
		}
		else {
			color_filename = argv[6];
		}

		if (_tcscmp(argv[7], TEXT("-o_normal")) != 0) {
			print_error_message(1);
			return false;
		}
		else {
			normal_filename = argv[8];
		}

	}
	else {
		print_error_message(0);
	}

	return true;

}