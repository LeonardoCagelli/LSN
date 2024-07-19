#pragma once
#include <iostream>
#include<cstdio>
#include<string>
#include<filesystem>
#include <sstream>
#include<vector>
#include <fstream>
#include <stdexcept>

// Function to rename a file
void renameFile(const std::string& directory, const std::string& oldFilename, const std::string& newFilename);

// Modify a specific property value inside the input file
void modifyProperty(const std::string& filename, double newValue, const std::string& property, int index = -1);

// Swap the names of two file
void swapFileNames(const std::string& file1, const std::string& file2);