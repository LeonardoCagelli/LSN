#include"function.h"

// Function to rename a file
void renameFile(const std::string& directory, const std::string& oldFilename, const std::string& newFilename) {
    std::filesystem::path oldFilePath = std::filesystem::path(directory) / oldFilename;
    std::filesystem::path newFilePath = std::filesystem::path(directory) / newFilename;

    try {
        // Check if the old file exists
        if (std::filesystem::exists(oldFilePath)) {
            // Rename the file
            std::filesystem::rename(oldFilePath, newFilePath);
        } else {
            std::cerr << "File " << oldFilename << " does not exist in directory " << directory << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error renaming file: " << e.what() << std::endl;
    }
}

// Modify a specific property value inside the input file
void modifyProperty(const std::string& filename, double newValue, const std::string& property, int index) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool modifiedFirstRow = false;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line); // split the line into elements
        std::string key;
        iss >> key;

        if (key == property && property == "SIMULATION_TYPE" && index >= 1 && index <= 3) {
            // Handle the first row with three values
            std::string part1, part2, part3;
            iss >> part1 >> part2 >> part3;
            std::ostringstream oss; // create a new line
            oss << key << " ";

            // Modify the specified value
            if (index == 1) {
                oss << newValue << " " << part2 << " " << part3;
            } else if (index == 2) {
                oss << part1 << " " << newValue << " " << part3;
            } else if (index == 3) {
                oss << part1 << " " << part2 << " " << newValue;
            }

            lines.push_back(oss.str());
            modifiedFirstRow = true;
        } else if (key == property) {
            std::ostringstream oss; // create a new line
            oss << property << " " << newValue;
            lines.push_back(oss.str());
        } else {
            lines.push_back(line);
        }
    }
    inputFile.close();

    // Ensure the first row modification is applied if specified
    if (property == "SIMULATION_TYPE" && index >= 1 && index <= 3 && !modifiedFirstRow) {
        std::cerr << "Failed to modify the first row value: invalid index or property not found." << std::endl;
        return;
    }

    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to write to file: " << filename << std::endl;
        return;
    }

    for (const std::string& line : lines) {
        outputFile << line << std::endl;
    }
    outputFile.close();
}

// Swap the names of two file
void swapFileNames(const std::string& file1, const std::string& file2) {
    std::string tempFile = "temp.dat";

    try {
        // Rename file1 to a temporary name
        std::filesystem::rename(file1, tempFile);

        // Rename file2 to file1
        std::filesystem::rename(file2, file1);

        // Rename temporary file to file2
        std::filesystem::rename(tempFile, file2);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error renaming files: " << e.what() << std::endl;
        // Restore original state in case of an error
        if (std::filesystem::exists(tempFile)) {
            try {
                std::filesystem::rename(tempFile, file1);
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Error restoring original file name: " << e.what() << std::endl;
            }
        }
    }
}