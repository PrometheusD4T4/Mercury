#include "csv.hpp"

/*
 * @brief: Open the file
 * @param filepath: The file to open
 */
void CSVReader::openFile(std::filesystem::path& filepath) {

    this->filePointer = std::ifstream(filepath);

    if (!this->filePointer.is_open()) {
        throw std::runtime_error("Could not open the specified file");
    }
}

/*
 * @brief: Read the next line of the file that was opened earlier
 * @param vec: The vector to which the next line is to be pushed
 */
void CSVReader::readLine(std::vector<std::string>& vec) {
    if (!this->filePointer.is_open()) {
        throw std::runtime_error("No files have been opened");
    }

    std::string line{};
    std::getline(this->filePointer, line);
    std::stringstream ss(line);

    while (ss.good()) {
        std::string substr;
        std::getline(ss, substr, ',');
        vec.push_back(substr);
    }
}

/*
 * @brief: destructor for CSVReader Class
 */
CSVReader::~CSVReader() {
    if (this->filePointer.is_open()) {
        this->filePointer.close();
    }
}