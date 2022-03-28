#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
const size_t BUF_SIZE = 4096;

int reverse_file(string input_filename) {
    string output_filename = input_filename + ".rev";
    ifstream inFile(input_filename,ios::in|ios::binary); //二进制读方式打开
    ofstream outFile(output_filename, ios::out | ios::binary);
    char buffer[BUF_SIZE];
    if(!inFile) {
        cout << "error" <<endl;
        return 0;
    }
    cout << "xx" << endl;
    int readedBytes = 0;
    do {
        inFile.read(buffer, BUF_SIZE);  //一直读到文件结束
        readedBytes = inFile.gcount(); //看刚才读了多少字节
        if (!readedBytes) {
            break;
        }
        for (int i = 0; i < readedBytes; i++) {
            buffer[i] = ~buffer[i];
        }
        outFile.write(buffer, readedBytes);
    } while (readedBytes == BUF_SIZE);
    
    inFile.close();
    outFile.close();
    return 0;
}

int main(int argc, char** argv) {
    assert(argc >= 1);
    cout << "argc" << argc << endl;
    for (int i = 1; i < argc; i++) {
        string filename(argv[i]);
        cout << filename << endl;
        reverse_file(string(filename));
    }
}