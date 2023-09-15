#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


class DataFileReader {

public:

    DataFileReader(const std::string& filename) : filename_(filename) {}

    bool ReadData() {
        std::ifstream file(filename_);
        if (!file.is_open()) {

            std::cerr << "Error: Could not open file " << filename_ << std::endl;
            return false;

        }

        std::string line;
        while (std::getline(file, line)) {
            if (line == "PTS") {

                ReadPoints(file);

            } else if (line == "CON") {

                ReadConnections(file);
            }
        }

        file.close() ;
        return true ;
    }

    const std::vector<std::vector<double>>& GetPoints() const {
        return points_ ;
    }

    const std::vector<std::pair<int, int>>& GetConnections() const {
        return connections_ ;
    }

private:
    void ReadPoints(std::ifstream& file) {
        std::string line;
        while (std::getline(file, line) && !line.empty()) {

            std::istringstream iss(line);
            int id;
            double x, y;
            if (iss >> id >> x >> y) {

                points_.emplace_back(std::vector<double>{static_cast<double>(id), x, y});

            }
        }
    }

    void ReadConnections(std::ifstream& file) {
        std::string line;
        while (std::getline(file, line) && !line.empty()) {

            std::istringstream iss(line);
            int id1, id2;
            if (iss >> id1 >> id2) {

                connections_.emplace_back(std::make_pair(id1, id2));

            }
        }
    }

    std::string filename_;
    std::vector<std::vector<double>> points_;
    std::vector<std::pair<int, int>> connections_ ;
} ;

int main() {

    DataFileReader reader("data.txt");

    if (reader.ReadData()) {

        const std::vector<std::vector<double>>& points = reader.GetPoints();
        const std::vector<std::pair<int, int>>& connections = reader.GetConnections();

        std::cout << "Points:" << std::endl;
        for (const auto& point : points) {

            std::cout << "ID: " << point[0] << " X: " << point[1] << " Y: " << point[2] << std::endl ;

        }

        std::cout << "Connections:" << std::endl;
        for (const auto& connection : connections) {

            std::cout << "ID1: " << connection.first << " ID2: " << connection.second << std::endl;

        }
    }

    return 0;
}

