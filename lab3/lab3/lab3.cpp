//#include <iostream>
//#include <fstream>
//#include <sstream>
//using namespace std;
//
//int countVowels(const string& word) {
//    int count = 0;
//    string vowels = "aeiouAEIOU";
//    for (char c : word) {
//        if (vowels.find(c) != string::npos) {
//            count++;
//        }
//    }
//    return count;
//}
//
//int findMaxVowelWord(const string& line) {
//    istringstream iss(line);
//    string word;
//    int maxVowelCount = 0;
//    int maxVowelWordIndex = -1;
//    int currentIndex = 0;
//    while (iss >> word) {
//        int vowelCount = countVowels(word);
//        if (vowelCount > maxVowelCount) {
//            maxVowelCount = vowelCount;
//            maxVowelWordIndex = currentIndex + 1;
//        }
//        currentIndex++;
//    }
//    return maxVowelWordIndex;
//}
//
//int main() {
//    setlocale(LC_ALL, "rus");
//    ifstream inputFile("FILE1.txt");
//    ofstream outputFile("FILE2.txt");
//    if (!inputFile.is_open() || !outputFile.is_open()) {
//        cout << "Не удалось открыть файлы." << endl;
//        return 1;
//    }
//
//    string line;
//    while (getline(inputFile, line)) {
//        istringstream iss(line);
//        string word;
//        int wordCount = 0;
//        while (iss >> word) {
//            wordCount++;
//        }
//        if (wordCount > 2) {
//            int maxVowelWordIndex = findMaxVowelWord(line);
//            outputFile << line << " (Слово с наибольшим количеством гласных - " << maxVowelWordIndex << ")\n";
//        }
//    }
//
//    inputFile.close();
//    outputFile.close();
//
//    return 0;
//}